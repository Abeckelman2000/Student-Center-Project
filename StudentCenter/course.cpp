//
// Created by austi on 7/1/2022.
//
#include "student.h"
#include "course.h"


course::course() {
    // variables
    string temp;
    int temp2;

    // prompts and input
    cout << "Welcome to the course creation tool! Please answer a few questions about the course" << endl;
    cout << "Course name: ";
    cin.ignore();
    getline(cin, temp);
    this->setCourseName(temp);

    cout << "Course description: ";
    getline(cin, temp);
    this->setCourseDesc(temp);

    cout << "Course Type: ";
    getline(cin, temp);
    this->setCourseType(temp);

    cout << "Professor: ";
    getline(cin, temp);
    this->setProfessor(temp);

    cout << "# of units: ";
    cin >> temp2;
    this->setNumUnits(temp2);

    cout << "Number of seats: ";
    cin >> temp2;
    // clear buffer
    cin.ignore();
    this->setClassSize(temp2);


    // all 0 by default
    this->setNumStudents(0);
    this->setNumWaitlisted(0);
    this->setNumReserved(0);
}

course::course(string courseName, string courseDesc, string courseType, string professor, int numUnits, int numStudents, int classSize, int numWaitlisted, int numReserved) {
    this->courseName = courseName;
    this->courseDesc = courseDesc;
    this->courseType = courseType;
    this->professor = professor;
    this->numUnits = numUnits;
    this->numStudents = numStudents;
    this->classSize = classSize;
    this->numWaitlisted = numWaitlisted;
    this->numReserved = numReserved;
}

// adds student id to waitlist and increases the number of students waitlisted
void course::addToWaitlist(string id) {
    // add student ID to waitlist
    waitlist.push_back(id);

    // update num waitlisted
    this->numWaitlisted = this->waitlist.size();

}

void course::waitlist_pop_front() {
    this->waitlist.pop_front();
}

/*// prints all information on a course
void course::getCourseInfo() {

}*/
