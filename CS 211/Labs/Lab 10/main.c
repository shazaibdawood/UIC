#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

const int NUM_CITIES = 30050;
const double RADIUS_EARTH = 6368.0; //in km

typedef struct City_struct {
    char name[50];
    char stateID[3];
    double lat;
    double lon;
} City;

typedef struct TripNode_struct {
    City* data;
    struct TripNode_struct* next;
} TripNode;

// builds an array of City structs from the data in uscities.csv
//  data format: <city name>,<state code>,<latitude>,<longitude>
void buildCityArray(City* usCities) {
    FILE* myFile = fopen("uscities.csv","r");

    char str[100];

    for (int i = 0; i < NUM_CITIES; ++i) {
        fgets(str, 100, myFile);
        if (str[strlen(str)-1] == '\n') {
            str[strlen(str)-1] = '\0';
        }
        
        char* tkn;

        tkn = strtok(str, ",");
        strcpy(usCities[i].name,tkn);
        
        tkn = strtok(NULL, ",");
        strcpy(usCities[i].stateID,tkn);

        tkn = strtok(NULL, ",");
        sscanf(tkn,"%lf",&(usCities[i].lat));

        tkn = strtok(NULL, ",");
        sscanf(tkn,"%lf",&(usCities[i].lon));

    }

    fclose(myFile);
    return;
}

// calculates the great-circle-distance (in km) between 
//  two (latitude, logitude) coordinate pairs on the surface of EARTH
double calcDist(double lat1, double long1, double lat2, double long2){
    return RADIUS_EARTH*acos(cos(lat1*M_PI/180.0)*cos(lat2*M_PI/180.0)*cos((long2-long1)*M_PI/180.0) + sin(lat1*M_PI/180.0)*sin(lat2*M_PI/180.0));
}

// display all details for a City on a single output line
void printCity(City myCity) {
    printf("   %s, %s (%0.4f,%0.4f)\n",myCity.name, myCity.stateID, myCity.lat, myCity.lon);
}

// traverse a TripNode list and print all City struct details
void printTrip(TripNode* myTrip) {
    TripNode* curr = myTrip;
    while (curr != NULL) {
        printCity(*(curr->data));
        curr = curr->next;
    }
}

// set <filename> to write the road Trip data to, which uses
//  the head node, *myTrip, as the start city, and direction
//  set by dir; general format: <start_city_name><ID><Dir>.csv
//      Exs:    roadTrips/ChicagoILSouth.csv
//              roadTrips/New_York_CityNYWest.csv
//              roadTrips/Los_AngelesCAEast.csv
//              roadTrips/HoustonTXNorth.csv
void setFilename(char* filename, TripNode* myTrip, int dir) {
    char dirStr[10];
    if (dir == 'N') {
        strcpy(dirStr,"North");
    } else if (dir == 'E') {
        strcpy(dirStr,"East");
    } else if (dir == 'S') {
        strcpy(dirStr,"South");
    } else {
        strcpy(dirStr,"West");
    }

    sprintf(filename,"roadTrips/%s%s%s%s",myTrip->data->name,myTrip->data->stateID,dirStr,".csv");

    char* sptr = filename;
    while (*sptr != '\0') {
        if isspace(*sptr) {
            *sptr = '_';
        }
        sptr++;
    }
}

// writing <myTrip> road trip data to file
void saveTrip(TripNode* myTrip, char dir) {
    char filename[100];
    setFilename(filename, myTrip, dir);

    FILE* myFile = fopen(filename,"w");
    
    TripNode* curr = myTrip;
    while (curr != NULL) {
        fprintf(myFile,"%s,%s,%0.4f,%0.4f\n",curr->data->name, curr->data->stateID, curr->data->lat, curr->data->lon);
        curr = curr->next;
    }
    fclose(myFile);
}

int findClosestCity(City* usCities, City curr, char dir) {
    //-------------------------------------------------------------------
    // TODO - find and return the index of the City in <usCities> that is
    //          the "closest" to <curr> in the direction set by <dir>:
    //              dir     direction   limitation for next City
    //               N        North       increasing latitude
    //               E        East        increasing longitude
    //               S        South       decreasing latitude
    //               W        West        decreasing longitude
    //          Additionally, ignore cities more than 150 km away.
    //          Return -1 if there is no City in <usCities> in the <dir>
    //          direction that is within 150 km of <curr>; note: in this
    //          case, the final destination city has been reached. 
    //          Note: find the distance (in km) bewteen two Citys by  
    //          using calcDist(lat1,lon1,lat2,lon2), which returns the 
    //          great-distance-distance between two (lat,lon) coordinates
    //-------------------------------------------------------------------
    int smallestNumber = -1;
    double previousCalc =150.0;
    double calculation =0.0;
    for (int i=0; i<NUM_CITIES; i++){
        if((dir=='N' && usCities[i].lat <= curr.lat)||(dir=='E' && usCities[i].lon <= curr.lon) || (dir=='W' && usCities[i].lon >= curr.lon) || (dir=='S' && usCities[i].lat >= curr.lat)){
            continue;
        }
        calculation=calcDist(curr.lat,curr.lon, usCities[i].lat,usCities[i].lon);
        if(calculation > 150.0){
            continue;
        }
        if(calculation < previousCalc){
        smallestNumber=i;
        previousCalc=calculation;
        }
    }
    return smallestNumber;
}

void appendCity(TripNode** myTrip, City* aCity) {
    //-------------------------------------------------------------------
    // DONE - construct a new TripNode with <data> set by <aCity>;
    //          navigate to the end of the list with head node **myTrip &
    //          append the new node to the back; the head node pointer 
    //          is passed-by-pointer to handle the empty list edge case.
    //-------------------------------------------------------------------
    TripNode* newNode = (TripNode*)malloc(sizeof(TripNode));
    newNode->data=aCity;
    newNode->next=NULL;
    if (*myTrip == NULL) { 
      *myTrip = newNode;
      return;
    }
   else{
    TripNode* last=*myTrip;
    while(last->next != NULL){
    last=last->next;
   }
    last->next=newNode;
   }
    
    return;
}

int countCities(TripNode* myTrip) {
    //-------------------------------------------------------------------
    // DONE - calculate and return the number of cities in the road trip,
    //          i.e. the length of the list with head node *myTrip.
    //-------------------------------------------------------------------
    int i=0;
    while(myTrip!=NULL){
        myTrip=myTrip->next;
        i++;
    }

    return i;
}

double totalDist(TripNode* myTrip) {
    //-------------------------------------------------------------------
    // DONE - calculate and return the total distance for the list with
    //          head node *myTrip; return 0.0 for lists with <2 nodes. 
    //          Note: find the distance (in km) bewteen two TripNodes by
    //          using calcDist(lat1,lon1,lat2,lon2), which returns the 
    //          great-distance-distance between two (lat,lon) coordinates
    //-------------------------------------------------------------------
    int i=0;
    double calculation=0.0;
    TripNode* traversing=myTrip;
    while(traversing->next!=NULL){
        traversing=traversing->next;
        i++;
    }
    if(i<2){
        return 0.0;
    }
    while(myTrip->next!=NULL){
        calculation+=calcDist(myTrip->data->lat,myTrip->data->lon, myTrip->next->data->lat,myTrip->next->data->lon);
        myTrip=myTrip->next;
    }
    return calculation;
}

TripNode* getTail(TripNode* myTrip) {
    //-------------------------------------------------------------------
    // DONE - find and return a pointer to the tail node, 
    //          i.e. the last node in the list with head node *myTrip
    //-------------------------------------------------------------------
    TripNode* tail=myTrip;
    if(tail==NULL){
        return NULL;
    }
    while(tail->next!=NULL){
        tail=tail->next;
    }

    return tail;
}

void freeTrip(TripNode* myTrip) {
    //-------------------------------------------------------------------
    // DONE - free all heap-allocated memory for node in list *myTrip
    //-------------------------------------------------------------------
    TripNode* freeing;
    while(myTrip!=NULL){
        freeing=myTrip;
        myTrip=myTrip->next;
        free(freeing);
    }
    
}


int main() {

    City* usCities = (City*)malloc(NUM_CITIES*sizeof(City));

    buildCityArray(usCities);

    int currInd = -1;
    
    printf("Choose a City array index where you would like to start: \n");
    while (currInd < 0 || currInd > NUM_CITIES-1 ) {
        printf("  Enter a value 0-%d: ", NUM_CITIES-1);
        scanf("%d",&currInd);
        printf("\n");
    }
    printf("Starting from:\n");
    printCity(usCities[currInd]);
    printf("\n");
    
    char dir = 'A';

    printf("What direction would you like to travel?\n");
    printf("   N = North\n");
    printf("   E = East\n");
    printf("   S = South\n");
    printf("   W = West\n");
    while (dir != 'N' && dir != 'E' && dir != 'S' && dir != 'W') {
        printf("Enter a direction (N, E, S, or W): ");
        scanf(" %c",&dir);
        printf("\n");
    }

    int count = 0;
    TripNode* myTrip = NULL;
    while (currInd > -1) {
        count++;
        appendCity(&myTrip, &(usCities[currInd]));
        currInd = findClosestCity(usCities, usCities[currInd], dir);
    }
    
    if (myTrip == NULL) {
        printf("No road trip was generated by this program...\n");
        return -1;
    }
    
    printf("Your Trip:\n");
    printf("   Start City: ");
    printCity(*(myTrip->data));
    printf("   Final City: ");
    printCity(*(getTail(myTrip)->data));
    //printTrip(myTrip); uncomment this for debugging ONLY; comment this out when submitting
    printf("Total number of cities on the road trip: %d\n",countCities(myTrip));
    printf("Total distance traveled on the road trip: %0.2lf km\n",totalDist(myTrip));
    saveTrip(myTrip,dir);

    free(usCities);
    freeTrip(myTrip);

    return 0;
}