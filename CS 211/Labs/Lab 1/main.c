#include <stdio.h>
#include <math.h>

const double RADIUS_EARTH = 6368.0; //in km

typedef struct Location_struct {
    char name[50];    //city name
    double latitude;
    double longitude;
    double elevation;
} Location;

typedef struct WorldTour_struct {
    Location locs[5];
    double distances[5];
} WorldTour;

double calcDist(double lat1, double long1, double lat2, double long2){
    return RADIUS_EARTH*acos(cos(lat1*M_PI/180.0)*cos(lat2*M_PI/180.0)*cos((long2-long1)*M_PI/180.0) + sin(lat1*M_PI/180.0)*sin(lat2*M_PI/180.0));
}

WorldTour setDists(WorldTour aTrip) {
    for(int i = 0; i < 5; i++){
        double lat1 = aTrip.locs[i].latitude;
        double long1 = aTrip.locs[i].longitude;
        double lat2 = aTrip.locs[i + 1].latitude;
        double long2 = aTrip.locs[i + 1].longitude;

        if(i + 1 == 5){
            lat2 = aTrip.locs[0].latitude;
            long2 = aTrip.locs[0].longitude;
        }

        aTrip.distances[i] = calcDist(lat1, long1, lat2, long2);
    }

    return aTrip; //modify this return statement
}

int main() {

    WorldTour myTrip;

    for (int i=0;i<5;i++) {
        printf("City %d:\n",i+1);
        printf("Enter the city name:\n");
        Location newLocation;
        scanf("%s", newLocation.name);

        printf("Enter the city coordinates (lat long elev):\n");
        
        scanf("%lf%lf%lf", &newLocation.latitude, &newLocation.longitude, &newLocation.elevation);
        myTrip.locs[i] = newLocation;
    }
    
    //set the distances array subitem of myTrip
    myTrip = setDists(myTrip);

    for(int i = 0; i < 5; i++){
        printf("Leg %d - %s to ", i + 1, myTrip.locs[i].name);
        if(i + 1 == 5){
            printf("%s: %.2lf km", myTrip.locs[0].name, myTrip.distances[i]);
        }
        else{
            printf("%s: %.2lf km", myTrip.locs[i + 1].name, myTrip.distances[i]);
        }

        printf("\n");
    } 

    return 0;
}
