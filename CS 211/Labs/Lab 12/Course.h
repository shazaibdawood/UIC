#ifndef COURSEH
#define COURSEH

#include <iostream>
#include <string>

using namespace std;

class Course {

    private:
        int courseNumber;
        string courseTitle;
        int numCredits;

    public:
        void SetCourseNumber(int userCourseNumber);
        void SetCourseTitle(string userCourseTitle);
        void SetNumCredits(int userNumCredits);
        int GetCourseNumber();
        string GetCourseTitle();
        int GetNumCredits();
        void PrintInfo();

};

#endif