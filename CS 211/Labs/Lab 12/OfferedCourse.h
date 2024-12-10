#ifndef OFFERED_COURSEH
#define OFFERED_COURSEH

#include "Course.h"

class OfferedCourse : public Course {

	// TODO: Declare private data members
    //      integer CRN & strings for schedule and location

	// TODO: Declare mutator functions -
	//      SetCRN(), SetSchedule(), SetLocation()

	// TODO: Declare accessor functions -
	//      GetCRN(), GetSchedule(), GetLocation()

    // TODO: Declare PrintInfo() to override the base class function
    //      PrintInfo()

    private:
        int CRN;
        string schedule;
        string location;
    
    public:
        void SetCRN(int CRN);
        void SetSchedule(string schedule);
        void SetLocation(string location);

        int GetCRN();
        string GetSchedule();
        string GetLocation();

        void PrintInfo();
    
};

#endif