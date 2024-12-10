#include "OfferedCourse.h"

// TODO: define all functions declared in OfferedCourse.h
using namespace std;

void OfferedCourse::SetCRN(int CRN) {    
    this->CRN = CRN;
}

void OfferedCourse::SetSchedule(string schedule) {
    this->schedule = schedule;
}

void OfferedCourse::SetLocation(string location){
    this->location = location;
}

int OfferedCourse::GetCRN() {
    return CRN;
}

string OfferedCourse::GetSchedule() {
    return schedule;
}

string OfferedCourse::GetLocation() {
    return location;
}

// CS 211: Programming Practicum
//    CRN: 47009
//    Schedule: WF, 4:00 PM - 4:50 PM
//    Location: LC A1
//    Credits: 3
void OfferedCourse::PrintInfo() {
    cout << "CS " << GetCourseNumber() << ": " << GetCourseTitle() << endl;
    cout << "\tCRN: " << CRN << endl;
    cout << "\tSchedule: " << schedule << endl;
    cout << "\tLocation: " << location << endl;
    cout  << "\tCredits: " << GetNumCredits() << endl;
}
