#include "funcs.h"

// known bugs
// 1.
//
// problems
// 1. be able to identify the path of the databses to work on any system(https://stackoverflow.com/questions/8518743/get-directory-from-file-path-c), (https://www.boost.org/doc/libs/1_80_0/more/getting_started/index.html)
// 2. watch this (https://www.youtube.com/watch?v=pLy69V2F_8M)


int main(){
    // variables
    student* loggedStudent = nullptr;
    string userID;
    string password;
    string studentDatabasePath;
    string courseDatabasePath;
    int menuInput;
    int parse;
    fstream f;


    // accessing databases
    vector<student> studentList;
    vector<course> courseCatalog;

    // Designate paths
    firstTimeLogin(studentDatabasePath, courseDatabasePath);


        // Load COURSE DATABASE
    readCourseData(courseCatalog, f, courseDatabasePath);

        // Load STUDENT DATABASE
    readStudentData(studentList, courseCatalog, f, studentDatabasePath);



    // login into the site
    int login = 0;
    do{
        cout << "Welcome to mySacState. Please Enter your login information or create an account[press -1 to create new account, 1 to continue, 2 to continue as a CSUS administrator, 3 to end program]: ";
        cin >> login;

        switch(login){
            // create a new student account
            case -1:
            {
                studentList.push_back(student());
            }
            break;
            // continue to login to site
            case 1:
            {
                csusStu(userID, password, studentList, loggedStudent, courseCatalog);
            }
            break;
            // continue to site as admin
            case 2:
            {
                csusAdmin(courseCatalog);
            }
            break;
            // log out of site
            case 3:
            {
                // UPDATE STUDENT AND COURSE DATABASE
                    // write any new students to the database
                writeStudentData(studentList, f, studentDatabasePath);
                    // write any new courses to the database
                writeCourseData(courseCatalog, f, courseDatabasePath);

                // end program
                cout << "Logging out of site. Goodbye!";
                return 0;
            }
            break;
            default:
            {
                cout << "LOGIN ERROR" << endl;
            }
            break;
        }
} while(login != 3);

    return 0;
}
