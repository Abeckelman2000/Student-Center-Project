//
// Created by austi on 8/16/2022.
//
// FUNCTIONS
#include "funcs.h"




// function used to add courses to database and possibly other admin tasks
void csusAdmin(vector<course>& courseCatalog){
    // variables
    int menuOpt;

    cout << "Welcome to the CSUS administrator dashboard" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "1. Add a class to the database" << endl;
    cout << "Please select an option from the menu: ";
    cin >> menuOpt;

    // input validation
    while(menuOpt != 1){
        cout << "Error! Please select a valid option from the menu: ";
        cin >> menuOpt;
    }

    switch(menuOpt){
        case 1:
        {
            // add a new course to the courseCatalog - create a course constructor
            courseCatalog.push_back(course());

            // test - print out the entire course catalog
            cout << "Entire Catalog" << endl;
            cout << "--------------" << endl;
            for(int i = 0; i < courseCatalog.size(); i++){
                cout << i + 1 << ". " << courseCatalog[i].getCourseName() << endl;
            }
        }

        default:
        {

        }
            break;
    }
}



// menu driver
void studentCenter(student*& loggedStudent, vector<course>& courseCatalog, vector<student>& studentList){
    // variables
    int menuInput;

    do{
        cout << "Welcome to the CSUS Student center!" << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Academics" << endl;
        cout << "2. Finances" << endl;
        cout << "3. My Account" << endl;
        cout << "4. Log out" << endl;
        cout << "Select an option from the menu: ";
        cin >> menuInput;

        // input validation
        while(menuInput < 1 || menuInput > 4){
            cout << "Invalid menu option entered. Please select a valid option from the menu: ";
            cin >> menuInput;
        }

        switch(menuInput){
            case 1:
            {
                academicsMenu(loggedStudent, courseCatalog, studentList);

            }
                break;
            case 2:
            {
                financesMenu(loggedStudent);
            }
                break;
            case 3:
            {
                myAccount(loggedStudent);
            }
                break;
            case 4:
            {
                cout << "Logging out..." << endl;
                return;
            }
                break;
            default:
            {
                cout << "MENU ERROR" << endl;
            }
                break;
        }
    } while(menuInput != 4);
}



// pushes login menu
void csusStu(string userID, string& password, vector<student>& studentList, student*& loggedStudent, vector<course>& courseCatalog) {
    // variables
    int menuInput;
    bool flag = false;
    // Display input prompts for login
    do {
        cout << "Login menu" << endl;
        cout << "-----------" << endl;
        cout << "Sac state ID: ";
        if(!flag){
            cin.ignore();
        }
        getline(cin, userID);

        cout << endl << "Password: ";
        getline(cin, password);
    }
        // validate the login information
    while (!isValidLogin(userID, password, studentList, loggedStudent, flag)); // logged student now contains the student



    // Student Center
    studentCenter(loggedStudent, courseCatalog, studentList);

}


// search a vector of students for an studentID match
bool isValidLogin(string userID, string password, vector<student>& studentList, student*& loggedStudent, bool& flag){
    // iterate through the studentList
    for(int i = 0; i < studentList.size(); i++){
        // check if the userID matches
        if(userID == studentList[i].getStudentID()){
            // check if the password is also a match
            if(password == studentList[i].getPassword()){
                // prompt a successful login and return true
                cout << endl << "Login Successful!" << endl;
                loggedStudent = &studentList[i];               // used to be able to access the student in future
                return true;
            }
        }

    }
    // if no student in the list has a matching ID, prompt user to try again and return true
    cout << endl << "Either the studentID or password does not match. Please try again" << endl;
    flag = true;
    return false;
}

// prints entire course catalog
void printCourseCatalog(vector<course>& courseCatalog){
    cout << "Entire Course Catalog" << endl;
    cout << "---------------------" << endl;

    // iterate through class list
    for (int i = 0; i < courseCatalog.size(); i++) {
        cout << i + 1 << ". " << courseCatalog[i].getCourseType() << "- "
             << courseCatalog[i].getCourseName() << endl;
        cout << "Professor: " << courseCatalog[i].getProfessor() << endl;
        cout << "Description: " << courseCatalog[i].getCourseDesc() << endl;
        cout << "Units: " << courseCatalog[i].getNumUnits() << endl << endl;
    }
}

// enrolls student in course and updates course member variables
void enroll(vector<course>& courseCatalog, student*& loggedStudent, int& menuOption){
    // variables
    int index = menuOption - 1;

    // Check if the student is already enrolled in the course
    for(auto it: loggedStudent->getListCourses()){
        if(it.getCourseName() == courseCatalog[index].getCourseName()){
            cout << "Error! Student Already enrolled in this course. Returning to Academics menu..." << endl;
            return;                                                               // exit function
        }
    }


    // UPDATE STUDENT, UPDATE COURSE

    //COURSE
    // update numStudents
    // if the course is full add student to the waitlist otherwise enroll
    if(courseCatalog[index].getNumStudents() >= courseCatalog[index].getClassSize()){
        // add student ID to waitlist
        courseCatalog[menuOption - 1].addToWaitlist(loggedStudent->getStudentID());

    }

        // enroll
        courseCatalog[index].setNumStudents(courseCatalog[index].getNumStudents() + 1);


    // STUDENT
    // add the class to the students course list
    loggedStudent->addCourse(courseCatalog[index]);
    cout << "Successfully added " << courseCatalog[index].getCourseName() << " to "
         << loggedStudent->getFirstName() << " " << loggedStudent->getLastName() << "'s courses." << endl;

    // update fees
    loggedStudent->setFees( loggedStudent->getFees() + loggedStudent->getNumUnits() * 150);

    // update enrolled units
    loggedStudent->setNumUnits(loggedStudent->getNumUnits() + courseCatalog[index].getNumUnits());


}

// removes student id from waitlist and adds the student to the course
// updates student/course info
void remFromWaitlist(vector<student>& studentList, course& course){
    // identify the student at the front of the waitlist

    for(auto it: studentList){
        if(course.getWaitlist().front() == it.getStudentID()){
            // UPDATE STUDENT DATA
            // add the course to this students course list
            it.addCourse(course);
            // increase their units
            it.setNumUnits(it.getNumUnits() + course.getNumUnits());
            // increase their balance
            it.setFees(it.getNumUnits() * 150);

            // UPDATE COURSE DATA
            // remove the student id from the course waitlist
            course.waitlist_pop_front();
            // decrease numWaitlisted
            course.setNumWaitlisted(course.getNumWaitlisted() - 1);
            // increase numStudents
            course.setNumStudents(course.getNumStudents() + 1);
            return;

        }
    }

}

// shows student list of enrolled courses and unenrolls them
void unenroll(student*& loggedStudent, vector<student>& studentList, int& menuOpt){
    // variables
    int index = menuOpt - 1;
    auto ueCourse = loggedStudent->getListCourses()[index];


    // UPDATE STUDENT AND COURSE MEMBER VARIABLE
    // Student
    // remove course from student's courseList
    loggedStudent->removeCourse(menuOpt);
    // lower student's balance
    loggedStudent->setFees(loggedStudent->getFees() - (ueCourse.getNumUnits() * 150));
    // remove units from total
    loggedStudent->setNumUnits(loggedStudent->getNumUnits() - ueCourse.getNumUnits());

    // Course
    // drop a student from numStudents
    ueCourse.setNumStudents(ueCourse.getNumStudents() - 1);

    // if there are students waitlisted, enroll a student
    remFromWaitlist(studentList, ueCourse);

}

// pushes academics menu
void academicsMenu(student*& loggedStudent, vector<course>& courseCatalog, vector<student>& studentList){
    // variables
    int menuOption;

    // menu loop
    do {
        cout << "Academics" << endl;
        cout << "---------" << endl;
        cout << "1. Current semester classes" << endl;
        cout << "2. Enroll in a course" << endl;
        cout << "3. Unenroll from a course" << endl;
        cout << "4. Return to Student Center" << endl;


        cout << "Please select an option from the menu: ";
        cin >> menuOption;

        // input validation
        while(menuOption < 1 or menuOption > 4){
            cout << "Error! Please select a option from the menu: ";
            cin >> menuOption;
        }

        switch (menuOption) {
            case 1: {
                cout << "Currently Enrolled courses" << endl
                     << "---------------------------" << endl;
                // iterate through student obj classlist
                for (int i = 0; i < loggedStudent->getListCourses().size(); i++) {
                    cout << i + 1 << ". " << loggedStudent->getListCourses()[i].getCourseName() << endl;

                }

            }
                break;
            case 2: {
                printCourseCatalog(courseCatalog);
                cout << "Please select an option from the menu: ";
                cin >> menuOption;

                // input validation
                while(menuOption < 1 || menuOption >= (courseCatalog.size() + 1)){
                    cout << "Error! Please select a valid course option from the menu";
                    cin >> menuOption;
                }

                enroll(courseCatalog, loggedStudent, menuOption);

            }
                break;
            case 3:{
                if(loggedStudent->getListCourses().empty()){
                    cout << "Student is not enrolled in any courses. Returning to Academic menu..." << endl;
                    break;
                }
                loggedStudent->printCourses();
                cout << "Select a course to unenroll:";
                cin >> menuOption;

                // input validation
                while(menuOption < 1 or menuOption >= (loggedStudent->getListCourses().size() + 1)){
                    cout << "Error! Please select a valid option from the menu:";
                    cin >> menuOption;
                }

                unenroll(loggedStudent, studentList, menuOption);

                // print updated course
                cout << "Updated course list:" << endl;
                loggedStudent->printCourses();
            }
                break;
            case 4: {
                return; // exit function
            }
            default: {

            }
                break;
        }
    } while(menuOption != 3);

}



// pushes finances menu
void financesMenu(student*& loggedStudent){
    // variables
    int menuOpt;
    do{
        cout << "Finances" << endl;
        cout << "--------" << endl;

        cout << "1. Outstanding Balance" << endl;
        cout << "2. Pay fees" << endl;
        cout << "3. Return to Student Center" << endl;
        cout << "Please select an option from the menu: ";
        cin >> menuOpt;

        // input validation
        while (menuOpt < 1 or menuOpt > 3){
            cout << "Error! Please select a valid option from the menu: ";
            cin >> menuOpt;
        }

        switch(menuOpt){
            case 1:{
                loggedStudent->printFees();
            }
                break;
            case 2:{
                // reset fees to 0
                loggedStudent->setFees(0);
                cout << "Fees payed!" << endl;
            }
                break;

            case 3:{
                return;
            }
                break;
            default:
            {}
                break;
        }
    } while(menuOpt != 3);



}



// pushes myAccount menu
void myAccount(student*& loggedStudent){
    // variables
    int menuOpt;
    string tempInput;
    do{
        cout << "Account" << endl;
        cout << "-------" << endl;
        cout << "1. View personal info" << endl;
        cout << "2. Change password" << endl;
        cout << "3. Return to Student Center" << endl;
        cout << "Select an option from the menu:";
        cin >> menuOpt;


        switch(menuOpt){
            case 1:{
                loggedStudent->viewPersonal();
            }
                break;
            case 2:{
                newPass(loggedStudent);
            }
                break;
            case 3:{
                return;
            }
                break;
            default:{
                cout << "myAccount menu error" << endl;
            }
                break;
        }
    } while(menuOpt != 3);
}



// allows a student to change their password
void newPass(student*& loggedStudent){
    // variables
    int menuOpt;
    string tempInput;

    cout << "Please enter your current password: ";
    // clear buffer
    cin.ignore();
    getline(cin, tempInput);

    // input validation
    while(tempInput != loggedStudent->getPassword()){
        cout << "Error! Please enter your current password: ";
        getline(cin, tempInput);
    }

    // enter new password
    cout << "Please enter a new password: ";
    getline(cin, tempInput);

    // cant be the same as old password
    while(tempInput == loggedStudent->getPassword()){
        cout << "New Password cannot be identical to previous, please enter a new password: ";
        getline(cin, tempInput);
    }

    // change the password
    loggedStudent->setPassword(tempInput);
}

// determines if a file is empty
bool isEmpty(fstream& fin){
    // variables
    string tempString;

    // if the first line we grab has length 0, file empty
    getline(fin, tempString);

    // regardless, return the instruction pointer back to the beginning of the file
    fin.clear();
    fin.seekg(0);

    return tempString.empty();
}

// reads students from database
void readStudentData(vector<student>& studentList, vector<course>& courseCatalog, fstream& fin, string& studentDatabasePath){   // void readStudentData(vector<student>&,student&, string, string, ifstream&)
    // variables
    string line;
    string tempString;
    vector<course> listCourses;
    vector<string> emptyHolds;
    student temp("", "", "", "", "", "", "", "", 0, 0, listCourses, emptyHolds);
    course tempC("", "", "", "", 0, 0, 0, 0, 0);


    // open file for read
    fin.open(studentDatabasePath);


    // verify the file opens correctly
    if(!fin){
        cout << "ERROR FILE FAILED TO OPEN";
        exit(1);
    }

    // if the file is empty, dont attempt to read
    if(isEmpty(fin)){
        // exit function
        cout << "STUDENT DATABASE EMPTY. Closing file and returning..." << endl;
        fin.close();
        return;
    }

    while(getline(fin, line)){
        // fixes bug where blank line gets parsed out
        if(line.length() == 0){
            break;
        }

        // store the line into a string stream variable
        stringstream inputString(line);

        // parse out the string using , as the delimiter

        // first name
        getline(inputString, tempString, ',');
        temp.setFirstName(tempString);

        // last name
        getline(inputString, tempString, ',');
        temp.setLastName(tempString);

        // password
        getline(inputString, tempString, ',');
        temp.setPassword(tempString);

        // email
        getline(inputString, tempString, ',');
        temp.setEmail(tempString);

        // address
        getline(inputString, tempString, ',');
        temp.setAddress(tempString);

        // ID
        getline(inputString, tempString, ',');
        temp.setStudentID(tempString);

        // phone num
        getline(inputString, tempString, ',');
        temp.setPhoneNumber(tempString);

        // Major
        getline(inputString, tempString, ',');
        temp.setMajor(tempString);

        // number units
        getline(inputString, tempString, ',');
        temp.setNumUnits(stoi(tempString));

        // fees
        getline(inputString, tempString, ',');
        temp.setFees(stoi(tempString));

        // class list
        getline(inputString, tempString, ',');
        stringstream classes(tempString);
        // parse the classes out
        while(getline(classes, tempString, '.')){

            // iterate through the course catalog to find a match
            auto it = find_if(courseCatalog.begin(), courseCatalog.end(), [&tempString](const course& obj) {return obj.getCourseName() == tempString;});

            // if iterator not pointing to end of vector, course match was found. add to student's courseList
            if(it != courseCatalog.end()){
                temp.addCourse(*it);
            }

        }
        // add courses to student's courselist

        studentList.push_back(temp);
        // clear temp student's course list
        temp.clearListCourses();

    }

    fin.close();
}


// writes new students to the database
void writeStudentData(vector<student>& studentList, fstream& fout, string& studentDatabasePath){
    // open outputfile
    fout.open(studentDatabasePath);

    // verify file opened
    if(!fout){
        cout << "ERROR. OUTPUT FILE FAILED TO OPEN... Ending Program\n";
        exit(1);
    }

    // iterate through the student list, appending each new student to the output file
    for(int i = 0; i < studentList.size(); i++){
        fout << studentList[i].getFirstName() << ",";
        fout << studentList[i].getLastName() << ",";
        fout << studentList[i].getPassword() << ",";
        fout << studentList[i].getEmail() << ",";
        fout << studentList[i].getAddress() << ",";
        fout << studentList[i].getStudentID() << ",";
        fout << studentList[i].getPhoneNumber() << ",";
        fout << studentList[i].getMajor() << ",";
        fout << studentList[i].getNumUnits() << ",";
        fout << studentList[i].getFees() << ",";
        // print classes
        if(studentList[i].getListCourses().empty()){
            fout << ".";
        }
        else{
            for(const auto& it: studentList[i].getListCourses()){
                fout << it.getCourseName() << ".";
            }
        }

        fout << endl;
    }

    // close student database
    fout.close();

}


// reads all courses from the database into a vector
void readCourseData(vector<course>& courseList, fstream& fin, string&){
    // variables
    course temp("", "", "", "", 0, 0, 0, 0, 0);
    string line;
    string tempString;

    // open course file
    fin.open("C:\\Users\\austi\\CLionProjects\\StudentCenter\\courseDatabase.txt");

    // verify it opened succesfully
    if(!fin){
        cout << "ERROR! Course Database failed to open\n";
        // end program
        exit(1);
    }

    // if the file is empty, dont attempt to read
    if(isEmpty(fin)){
        // exit function
        cout << "COURSE DATABASE EMPTY. Closing file and returning...." << endl;
        fin.close();
        return;
    }

    // parse the course database
    while(getline(fin, line)){
        // fixes bug where blank line gets parsed out
        if(line.length() == 0){
            break;
        }


        // put line in sstream object for parsing
        stringstream inputString(line);



        //  get and store parsed information into course object
        // course title
        getline(inputString, tempString, ',');
        temp.setCourseName(tempString);

        // course desc
        getline(inputString, tempString, ',');
        temp.setCourseDesc(tempString);

        // courseType
        getline(inputString, tempString, ',');
        temp.setCourseType(tempString);

        // professor
        getline(inputString, tempString, ',');
        temp.setProfessor(tempString);

        // numUnits
        getline(inputString, tempString, ',');
        temp.setNumUnits(stoi(tempString));

        // numStudents
        getline(inputString, tempString, ',');
        temp.setNumStudents(stoi(tempString));

        // classSize
        getline(inputString, tempString, ',');
        temp.setNumStudents(stoi(tempString));

        // numWaitlisted
        getline(inputString, tempString, ',');
        temp.setNumWaitlisted(stoi(tempString));

        // numReserved
        getline(inputString, tempString, ',');
        temp.setNumReserved(stoi(tempString));

        // add course to courseList
        courseList.push_back(temp);

    }

    // close the file
    fin.close();

}


// writes all new courses to the database
void writeCourseData(vector<course>& courseCatalog, fstream& fout, string& studentDatabasePath){
    // open course database
    fout.open(studentDatabasePath);


    // verify the file opened
    if(!fout){
        cout << "ERROR! Course Database failed to open.... Ending Program";
        // end program

        exit(1);
    }

    // iterate through each new course and print it to database
    for(int i = 0; i < courseCatalog.size(); i++){
        // print each attribute of the course onto the line
        fout << courseCatalog[i].getCourseName() << ",";
        fout << courseCatalog[i].getCourseDesc() << ",";
        fout << courseCatalog[i].getCourseType() << ",";
        fout << courseCatalog[i].getProfessor() << ",";
        fout << courseCatalog[i].getNumUnits() << ",";
        fout << courseCatalog[i].getNumStudents() << ",";
        fout << courseCatalog[i].getClassSize() << ",";
        fout << courseCatalog[i].getNumWaitlisted() << ",";
        fout << courseCatalog[i].getNumReserved() << ",";

        fout << endl;
    }

    // close course database
    fout.close();
}

//first time setup, set up database directories
void firstTimeLogin(string& studentDatabasePath, string& courseDatabasePath){
    cout << "Welcome to CSUS Student Center Program. Please create two .txt files: (1) Student Database, (2) Course Database." << endl;
    cout << "Please enter the entire file path for each file when prompted:" << endl;

    cout << "Student Database: ";
    getline(cin, studentDatabasePath);
    cout << "\nCourse Database: ";
    getline(cin, courseDatabasePath);

}
