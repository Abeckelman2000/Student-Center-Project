#include "student.h"
#include <ctime>

// functions

void student::printCourses() {
    //prompt

    cout << endl << this->getFirstName() << " " << this->getLastName() << "'s course list:" << endl;
    cout << "--------------------------" << endl;

    // iterate through the vector and print the title of each course
    for(int i = 0; i < this->listCourses.size(); i++){
        cout << i+1 << ". " << this->listCourses[i].getCourseName() << endl;
    }

}



// constructors
student::student() {
// initialize input buffers
    string temp = "";
    int temp2 = 0;
    // ask for basic student info information
    cout
            << "Welcome to the new student creation window. Please answer the following questions regarding the new student...\n";

    // First name
    cout << "First name: ";
    cin.ignore();
    getline(cin, temp);
    while (temp.size() < 1) {
        cout << "Error! Please enter a valid first name for the student:";
        getline(cin, temp);
    }
    this->setFirstName(temp);

    // Last name
    cout << "Last name: ";
    getline(cin, temp);
    while (temp.size() < 1) {
        cout << "Error! Please enter a valid last name for the student: ";
        getline(cin, temp);
    }
    this->setLastName(temp);

    // Email
    cout << "Email address: ";
    getline(cin, temp);
    // The email address must be greater than 0 characters and contain "@" and ".com"
    while (temp.empty() || !(temp.find('@') and temp.find(".com"))) {
        cout << "Error! Please enter a valid email for the student: ";
        getline(cin, temp);
    }
    this->setEmail(temp);

    // Address
    // address in the following format. Ex. (3580 West Grant Line Road, Tracy, CA 95304)
    cout << "Address: ";
    getline(cin, temp);
    // Address must be greater than 0 characters
    while (temp.empty()) {
        cout << "Error! Please enter a valid address for the student: ";
        getline(cin, temp);
    }
    this->setAddress(temp);

    // Phone number
    cout << "Phone number: ";
    getline(cin, temp);
    // Phone number must be equal to 7 digits in length
    while (temp.size() != 10) {
        cout << "Error! Please enter a valid phone number for the student: ";
        getline(cin, temp);

    }
    this->setPhoneNumber(temp);

    // password
    cout << "New Password: ";
    getline(cin, temp);
    this->setPassword(temp);

    // major
    cout << "Major: ";
    getline(cin, temp);
    this->setMajor(temp);

    // number of units enrolled
    cout << "How many units enrolled? (max of 17): ";
    cin >> temp2;

    // max of 17 units
    while (temp2 > 17 || temp2 < 0) {
        cout << "Invalid # of units. Please re-enter the number of units enrolled: ";
        cin >> temp2;
    }
    // clear buffer
    cin.ignore();
    this->numUnits = temp2;

    // constants
    // fee balance
    this->fees = 0;

    // Generating a random student id
    srand(time(0));
    const char arrayChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 0; i < 9; i++) {
        this->studentID.push_back(arrayChars[rand() % 16]);
    }

    cout << "New student ID: " << this->studentID << endl;
}

student::student(string fName, string lName, string pWord, string email, string address, string studID, string phoneNumber, string major, int numUnits, int fees, vector<course> & listCourses,
                 vector<string> & holds) {

    this->firstName = fName;
    this->lastName = lName;
    this->password = pWord;
    this->email = email;
    this->address = address;
    this->studentID = studID;
    this->phoneNumber = phoneNumber;
    this->major = major;
    this->numUnits = numUnits;
    this->fees = fees;
    // copying the contents of the list given list of courses
    for(int i = 0; i < listCourses.size(); i++){
        this->listCourses[i] = listCourses[i];
    }

    // copying the contents of holds into the object
    for(int i = 0; i < holds.size(); i++){
        this->holds[i] = holds[i];
    }

}

void student::removeCourse(int& menuindex) {
        // list courses
        this->listCourses.erase(listCourses.begin() + (menuindex - 1));

}

void student::addCourse(course& newCourse) {
    this->listCourses.push_back(newCourse);
}




