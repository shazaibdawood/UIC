#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Course.h"
#include "OfferedCourse.h"

using namespace std;


// int findCourseInCatalog(vector<Course> allCourses, int courseNum)
//      search [allCourses] for a Course with courseNumber equal to [courseNum];
//      if not found, then return -1;
//      otherwise, return the index of [allCourses] where the courseNumber match 
//          to [courseNum] is found
//      note: allCourses.size() returns number of Course objects in the vector;
int findCourseInCatalog(vector<Course> allCourses, int courseNum) {
    
    //--------------------------
    // TODO: write this function
    //--------------------------
    for(int i  = 0; i < allCourses.size(); i++){
        if(allCourses.at(i).GetCourseNumber() == courseNum){
            return i;
        }
    }
    return -1;
}


// OfferedCourse transferDetails(vector<Course> allCourses, int courseNum)
//      search [allCourses] for a Course with courseNumber equal to [courseNum];
//      if not found, then return an OfferedCourse object with
//          - courseNumber = 0
//          - courseTitle = "ERROR: Not a real course"   
//          - numCredits = -1
//      otherwise, return a partially initialized OfferedCourse object, where
//          - courseNumber is a copy from the Course object in [allCourses]
//          - courseTitle is a copy from the Course object in [allCourses]
//          - numCredits is a copy from the Course object in [allCourses]
//      note: this function should include a call to findCourseInCatalog() 
//      note: allCourses.size() returns number of Course objects in the vector;
OfferedCourse transferDetails(vector<Course> allCourses, int courseNum) {
    OfferedCourse myOffCourse;

    //--------------------------
    // TODO: write this function
    //--------------------------
    int index = findCourseInCatalog(allCourses, courseNum);
    if(index == -1){
        myOffCourse.SetCourseNumber(0);
        myOffCourse.SetCourseTitle("ERROR: Not a real course");
        myOffCourse.SetNumCredits(-1);
    }
    else {
        myOffCourse.SetCourseNumber(allCourses.at(index).GetCourseNumber());
        myOffCourse.SetCourseTitle(allCourses.at(index).GetCourseTitle());
        myOffCourse.SetNumCredits(allCourses.at(index).GetNumCredits());
    }

    return myOffCourse;
}


// vector<int> findCourseSections()
//      search [courseSections] to find all OfferedCourse objects with 
//      courseNumber equal to [courseNum], representing the offered 
//          sections of that course;
//      if none found, then return an empty integer (i.e. size_t) vector;
//      otherwise, return a vector of indices for the offered sections;
//      note: courseSections.size() returns the number of OfferedCourse 
//            objects in the vector;
//      note: mySectionInds.push_back(5) appends 5 to the back of the vector
vector<size_t> findCourseSections(vector<OfferedCourse> courseSections, int courseNum) {
    vector<size_t> mySectionInds;

    //--------------------------
    // TODO: write this function
    //--------------------------

    for(int i = 0; i < courseSections.size(); i++){
        if(courseSections.at(i).GetCourseNumber() == courseNum){
            mySectionInds.push_back(i);
        }
    }

    return mySectionInds;
}


// vector<Course> buildCourseCatalog(string filename) 
//    builds a vector of Course object, one for each line in the file;
//    format of courses listed in the catalog .txt file:
//      CS <courseNumber>. <Course Title Goes Here>. <numCredits> hours.
//  Ex: CS 211. Programming Practicum. 3 hours.
//  Ex: CS 341. Programming Language Design and Implementation. 3 hours.
vector<Course> buildCourseCatalog(string filename) {
    vector<Course> allCourses; // Course vector to be returned

    ifstream inFS; // input file stream
    inFS.open(filename); // opening catalog .txt file
    while (!inFS.eof()) {
        Course myCourse; // Course being built for this line from catalog
        string curr; 
        getline(inFS, curr); // read in a line from the catalog

        istringstream inSS(curr);
        string temp;
        inSS >> temp; // read in "CS" and do nothing with it
        inSS >> temp; // read in courseNumber
        temp.pop_back(); // remove '.' from back of courseNumber
        int courseNum = stoi(temp); // convert courseNumber to integer
        myCourse.SetCourseNumber(courseNum);

        inSS >> temp; // read in first word of course title
        // repeatedly concatenate words to the course title 
        // until the word ends in '.'
        while (temp.back() != '.') {
            string temp2; 
            inSS >> temp2;
            temp = temp + " " + temp2;
        }
        temp.pop_back(); // remove '.' from back of courseTitle
        myCourse.SetCourseTitle(temp);
        
        inSS >> temp; // read in numCredits
        int numCreds = stoi(temp); // convert numCredits to integer
        myCourse.SetNumCredits(numCreds);

        allCourses.push_back(myCourse); // add current Course to vector
    }

    inFS.close();
    return allCourses;
}


// vector<OfferedCourse> buildCourseSections() {
//    builds a vector of OfferredCourse objects, one for each line in the file;
//    OfferedCourse is a derived class of the Course base class; 
//    the courseTitle and numCredits for each OfferedCourse object should be
//    copied from the associate Course object in the allCourses vector;
//    format of offered courses listed in the course list .txt file:
//      CS <courseNumber>. <CRN>. <Schedule days & time>. <location>.
//  Ex: CS 211. 47009. WF, 4:00 PM - 4:50 PM. LC A1.
//  Ex: CS 341. 34723. TR, 9:30 AM - 10:45 AM. LC E1.
vector<OfferedCourse> buildCourseSections(string filename, vector<Course> allCourses) {
    vector<OfferedCourse> allOffCourses; 

    ifstream inCS;
    inCS.open(filename);
    while (!inCS.eof()) {
        string curr;
        getline(inCS, curr); // get current line from file
 
        istringstream inSS(curr);
        string temp;
        inSS >> temp; // read in "CS" and do nothing with it
        inSS >> temp; // read in courseNumber
        temp.pop_back(); // remove '.' from back of courseNumber
        int courseNum = stoi(temp); // convert courseNumber to integer
 
        // transfer courseTitle and numCredits from the Course in allCourses 
        // to a new OfferedCourse
        OfferedCourse myOffCourse = transferDetails(allCourses, courseNum);
        
        inSS >> temp; // Read in CRN
        temp.pop_back(); // remove '.' from back
        int myCRN = stoi(temp); // convert CRN to integer
        myOffCourse.SetCRN(myCRN);

        inSS >> temp; // Read in first "word" for course schedule
        // repeatedly concatenate "words" to the course schedule 
        // until the "word" ends in '.'
        while (temp.back() != '.') {
            string temp2;
            inSS >> temp2;
            temp = temp + " " + temp2;
        }
        temp.pop_back(); // remove '.' from the back
        myOffCourse.SetSchedule(temp);

        inSS >> temp; // Read in first "word" for location
        // repeatedly concatenate "words" to the location 
        // until the "word" ends in '.'
        while (temp.back() != '.') {
            string temp2;
            inSS >> temp2;
            temp = temp + " " + temp2;
        }
        temp.pop_back(); // remove '.' from the back
        myOffCourse.SetLocation(temp);

        allOffCourses.push_back(myOffCourse); // add current OfferedCourse to vector
    }
    inCS.close();
    return allOffCourses;
}


int main() {

    vector<Course> courseCatalog = buildCourseCatalog("CourseCatalog.txt");  
    
    cout << "Sample courses from the course catalog:";
    cout  << endl << "   ";
    courseCatalog[10].PrintInfo();
    cout  << "   ";
    courseCatalog[11].PrintInfo();
    cout  << "   ";
    courseCatalog[12].PrintInfo();
    cout  << endl;

    OfferedCourse sample;
    sample.SetCourseNumber(211);
    sample.SetCourseTitle("Programming Practicum");
    sample.SetNumCredits(3);
    sample.SetCRN(47009);
    sample.SetSchedule("WF, 4:00 PM - 4:50 PM");
    sample.SetLocation("LC A1");    
    cout << "Sample offered course:" << endl;
    sample.PrintInfo();
    cout  << endl;


    vector<OfferedCourse> courseSections = buildCourseSections("Spring2024Courses.txt",courseCatalog);

    int courseNum;
    cout << "Enter the course number you would like to register for:" << endl;
    cout << "   CS ";
    cin >> courseNum;

    cout << endl;
    cout << "Your selected course is: " << endl << "   ";
    int courseInd = findCourseInCatalog(courseCatalog,courseNum);
    if (courseInd == -1) {
        cout << "NOT listed in the course catalog." << endl;
        cout << "Terminating program..." << endl;
        return 0;
    }
    courseCatalog[findCourseInCatalog(courseCatalog,courseNum)].PrintInfo();
    cout << endl;

    cout << "The registration options are as follows:" << endl;
    vector<size_t> sectionInds = findCourseSections(courseSections,courseNum);
    if (sectionInds.size() == 0) {
        cout << "   NO OPTIONS: this course is not offered" << endl;
    } else {
        for (size_t i = 0; i < sectionInds.size(); ++i) {
            courseSections[sectionInds[i]].PrintInfo();
        }
    }

    return 0;
}
