#include <fstream>
#include <sstream>
#include <algorithm>
#include "course.h"
#include "student.h"


void firstTimeLogin(string&, string&);
bool isValidLogin(string, string, vector<student>&, student*&, bool&);
void academicsMenu(student*&, vector<course>&, vector<student>&);
void financesMenu(student*&);
void csusAdmin(vector<course>&);
void csusStu(string, string&, vector<student>&, student*&, vector<course>&);
void studentCenter(student*&, vector<course>&, vector<student>&);
void myAccount(student*&);
void newPass(student*&);
void viewPersonal(student*&);
bool isEmpty(fstream&);
void readStudentData(vector<student>&, vector<course>&, fstream&, string&);
void writeStudentData(vector<student>&, fstream&, string&);
void readCourseData(vector<course>&, fstream&, string&);
void writeCourseData(vector<course>&, fstream&, string&);
void printCourseCatalog(vector<course>&);
void enroll(vector<course>&, student*&, int&);
void unenroll(student*&, vector<student>&, int&);
void remFromWaitlist(vector<student>&, course&);