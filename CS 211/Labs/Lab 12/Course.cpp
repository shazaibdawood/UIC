#include "Course.h"

using namespace std;

void Course::SetCourseNumber(int userCourseNumber) {    
    courseNumber = userCourseNumber;
}

void Course::SetCourseTitle(string userCourseTitle) {
    courseTitle = userCourseTitle;
}

void Course::SetNumCredits(int userNumCredits){
    numCredits = userNumCredits;
}

int Course::GetCourseNumber() {
    return courseNumber;
}

string Course::GetCourseTitle() {
    return courseTitle;
}

int Course::GetNumCredits() {
    return numCredits;
}

void Course::PrintInfo() {
    cout << "CS " << courseNumber << ": " << courseTitle;
    cout  << " (" << numCredits << " credits)" << endl;
}