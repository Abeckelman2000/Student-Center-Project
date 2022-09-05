//
// Created by austi on 6/22/2022.
//

#ifndef UNTITLED_COURSE_H
#define UNTITLED_COURSE_H
#include <iostream>
#include <vector>
#include <deque>
using namespace std;


class course {
private:
    string courseName;
    string courseDesc;
    string courseType;
    string professor;
    int numUnits;
    int numStudents;
    int classSize;
    int numWaitlisted;
    int numReserved;
    deque<string> waitlist;
public:
    // Setters and getters
    void setCourseName(string courseName)        {this->courseName = courseName;}
    string getCourseName() const                 {return this->courseName;}

    void setCourseDesc(string courseDesc)        {this->courseDesc = courseDesc;}
    string getCourseDesc() const                 {return this->courseDesc;}

    void setCourseType(string courseType)        {this->courseType = courseType;}
    string getCourseType() const                 {return this->courseType;}

    void setProfessor(string professor)          {this->professor = professor;}
    string getProfessor() const                  {return this->professor;}

    void setNumUnits(int numUnits)               {this->numUnits = numUnits;}
    int getNumUnits() const                      {return this->numUnits;}

    void setNumStudents(int numStudents)         {this->numStudents = numStudents;}
    int getNumStudents() const                   {return this->numStudents;}

    void setClassSize(int classSize)             {this->classSize = classSize;}
    int getClassSize()  const                    {return this->classSize;}

    void setNumWaitlisted(int numWaitlisted)     {this->numWaitlisted = numWaitlisted;}
    int getNumWaitlisted() const                 {return this->numWaitlisted;}

    void setNumReserved(int numReserved)         {this->numReserved = numReserved;}
    int getNumReserved() const                   {return this->numReserved;}

    deque<string> getWaitlist()                 {return this->waitlist;}




    // Constructors
    course();
    course(string, string, string, string, int, int, int, int, int);

    // funcs
    void addToWaitlist(string id);
    void waitlist_pop_front();
    void getCourseInfo();
};


#endif //UNTITLED_COURSE_H
