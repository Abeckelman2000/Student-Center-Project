//
// Created by austi on 6/22/2022.
//

#ifndef UNTITLED_STUDENT_H
#define UNTITLED_STUDENT_H
#include "course.h"
#include <iostream>
#include <vector>
using namespace std;

class student{
private:
    string firstName;
    string lastName;
    string password;
    string email;
    string address;
    string studentID;
    string phoneNumber;
    int fees;
    vector<string> holds;
    string major;
    int numUnits;
    vector<course> listCourses;

public:
    // setters and getters
    string getFirstName()                   {return firstName;}
    void setFirstName(string fName)         {this->firstName = fName;}

    string getLastName()                    {return lastName;}
    void  setLastName(string lName)         {this->lastName = lName;}

    string getPassword()                    {return password;}
    void setPassword(string password)       {this->password = password;}

    string getMajor()                       {return major;}
    void setMajor(string major)             {this->major = major;}

    int getNumUnits()                       {return numUnits;}
    void setNumUnits(int num)               {this->numUnits = num;}

    string getAddress()                     {return address;}
    void setAddress(string addy)            {this->address = addy;}

    string getPhoneNumber()                 {return phoneNumber;}
    void setPhoneNumber(string phoneNumber) {this->phoneNumber = phoneNumber;}

    int getFees()                           {return fees;}
    void setFees(int fees)                  {this->fees = fees;}


    string getEmail()                       {return email;}
    void setEmail(string email)             {this->email = email;}

    string getStudentID()                   {return this->studentID;}
    void setStudentID(string studentID)     {this->studentID = studentID;}

    vector<course> getListCourses()         {return listCourses;}


    // constructors
    student();
    student(string,string, string, string, string, string, string, string, int, int,  vector<course>&, vector<string>&);





    // funcs

    void addCourse(course& newCourse);
    void printCourses();
    void viewPersonal(){
            cout << this->getFirstName() << " " << this->getLastName() << "'s Info" << endl;
            cout << "-----------------------" << endl;
            cout << "Name: " << this->getLastName() << ", " << this->getFirstName() << endl;
            cout << "Email: " << this->getEmail() << endl;
            cout << "Address: " << this->getAddress() << endl;
            cout << "Phone #: " << this->getPhoneNumber() << endl;
            cout << "Student ID: " << this->getStudentID() << endl;
            cout << "Password: " << this->getPassword() << endl;
            cout << "Major: " << this->getMajor() << endl;
            cout << "Units Enrolled: " << this->getNumUnits() << endl;
    }
    void printFees(){
        cout << this->getFirstName() << " " << this->getLastName() << "'s balance: " << this->getFees() << endl;
    }
    void clearListCourses()                 {this->listCourses.clear();}
    void removeCourse(int& index);

};


#endif //UNTITLED_STUDENT_H
