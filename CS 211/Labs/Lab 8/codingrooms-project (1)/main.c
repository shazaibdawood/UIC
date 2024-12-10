#include <stdio.h>
#include <string.h>
   
typedef struct Country_struct {
   char code[4];
   char name[40];
   double ghg; //total greenhouse gas emissions, averaged over 2012-2016; units: million-tonnes of CO2
   double co2; //total carbon dioxide gas emissions, averaged over 2012-2016; units: million-tonnes of CO2
   double ch4; //total methane gas emissions, averaged over 2012-2016; units: million-tonnes of CO2
   double n2o; //total nitrous oxide gas emissions, averaged over 2012-2016; units: million-tonnes of CO2
   double pop; //total population, averaged over 2012-2016
   double gdp; //gross domestic product, averaged over 2012-2016
   double consumption; //total primary energy consumption, averaged over 2012-2016; units: terawatt-hours
   double generation; //total electricity generation, from 2016; units: gigawatt-hours
   double renewable; //electricity generation from renewable sources, from 2016; units: gigawatt-hours
   double hydro; //electricity generation from hydropower, from 2016; units: gigawatt-hours
   double wind; //electricity generation from wind, from 2016; units: gigawatt-hours
   double biomass; //electricity generation from biomass, from 2016; units: gigawatt-hours
   double solar; //electricity generation from solar, from 2016; units: gigawatt-hours
   double geothermal; //electricity generation from geothermal, from 2016; units: gigawatt-hours
} Country;

void printDetails(Country me) {
   printf("Country: %s\n",me.name);
   printf("  Population: %.0lf\n",me.pop);
   printf("  Gross Domestic Product: %.0lf USD\n",me.gdp);   
   printf("  Greenhouse Gas Emissions [in million-tonnes of C02 equivalent]\n");
   printf("    Total: %.2lf\n", me.ghg);
   printf("    Carbon Dioxide: %.2lf\n", me.co2);
   printf("    Methane: %.2lf\n", me.ch4);
   printf("    Nitrous Oxide: %.2lf\n", me.n2o);
   printf("  Total Energy Consumption: %.2lf terawatt-hours\n",me.consumption);
   printf("  Electricity Generation [in gigawatt-hours]\n");
   printf("    Total: %.2lf\n", me.generation);
   printf("    Renewable Sources: %.2lf\n", me.renewable);
   printf("    Hydropower: %.2lf\n", me.hydro);
   printf("    Wind Power: %.2lf\n", me.wind);
   printf("    Biomass: %.2lf\n", me.biomass);
   printf("    Solar Power: %.2lf\n", me.solar);
   printf("    Geothermal: %.2lf\n", me.geothermal);
}

int findCountry(Country all[], int size, char* myCode) {
   for (int i = 0; i < size; ++i) {
      if (strcmp(myCode,all[i].code) == 0) {
         return i;
      }
   }
   return -1; //code not found
}

//insertion sort - decreasing numeric order
void sortData(double data[], int size) {
    int i;
    int j;
    double temp; // Temporary variable for swap
    for (i = 1; i < size; ++i) {
        j = i;
        // Insert data[i] into sorted part
        // stopping once data[i] in correct position
        while (j > 0 && data[j] > data[j - 1]) {
            // Swap data[j] and data[j - 1]
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}

void sortCountriesByPop(Country data[], int size){
   // TODO: SORT THE COUNTRIES BY POPULATION
    int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].pop > data[j - 1].pop) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}

void sortCountriesByGDP(Country data[], int size){
   // TODO: SORT THE COUNTRIES BY GDP
   int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].gdp > data[j - 1].gdp) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}

void sortCountriesByGDPperCap(Country data[], int size){
   // TODO: SORT THE COUNTRIES BY GDP PER CAPITA
   int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].gdp/data[j].pop > data[j - 1].gdp/data[j-1].pop) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}


void sortCountriesByGHG(Country data[], int size){
   // TODO: SORT THE COUNTRIES BY GREENHOUSE GAS EMISSIONS
   int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].ghg > data[j - 1].ghg) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}
   

void sortCountriesByGHGperCap(Country data[], int size){
    // TODO: SORT THE COUNTRIES BY GREENHOUSE GAS EMISSIONS PER CAPITA
    int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].ghg/data[j].pop > data[j - 1].ghg/data[j-1].pop) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}

void sortCountriesByRE(Country data[], int size){
    // TODO: SORT THE COUNTRIES BY ELECTRICITY GENERATED BY RENEWABLE SOURCES
    int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].renewable > data[j - 1].renewable) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}

void sortCountriesByREperCap(Country data[], int size){
    // TODO: SORT THE COUNTRIES BY ELECTRICITY GENERATED BY RENEWABLE SOURCES PER CAPITA
    int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0 && data[j].renewable/data[j].pop > data[j - 1].renewable/data[j-1].pop) {
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            --j;
        }
    }
    return;
}


void sortCountriesByCode(Country data[], int size){
    // TODO: SORT THE COUNTRIES BY CODE
    // HINT: strcmp(str1, str2) returns:
    //          <0 if str1 is alphabetically BEFORE str2
    //          =0 if str1 is alphabetically IDENTICAL TO str2
    //          >0 if str1 is alphabetically AFTER str2
    int i;
    int j;
    Country temp;
    for (i = 1; i < size; ++i) {
        j = i;
        while (j > 0) {
            int comparison = strcmp(data[j].code, data[j - 1].code);
            if (comparison>0){
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            }
            if (comparison){
            temp = data[j-1];
            data[j-1] = data[j];
            data[j] = temp;
            }
            else{
            temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            }
            --j;
        }
    }
    return;

}

int main() {
    
    const int NUM_COUNTRIES = 186;
    
    Country allData[NUM_COUNTRIES];
   
    FILE* myFile = fopen("countryData.txt","r");
    char titles[30];
    fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
    fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
    fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
    fscanf(myFile, "%s %s %s %s", titles, titles, titles, titles);
   
    for (int i = 0; i < NUM_COUNTRIES; ++i) {
        fscanf(myFile,"%s %s %lf %lf", allData[i].code, allData[i].name, &allData[i].ghg, &allData[i].co2);
        fscanf(myFile,"%lf %lf %lf %lf", &allData[i].ch4, &allData[i].n2o, &allData[i].pop, &allData[i].gdp);
        fscanf(myFile,"%lf %lf %lf %lf", &allData[i].consumption, &allData[i].generation, &allData[i].renewable, &allData[i].hydro);
        fscanf(myFile,"%lf %lf %lf %lf", &allData[i].wind, &allData[i].biomass, &allData[i].solar, &allData[i].geothermal);
    }
   
    int inp;
    printf("View country list by name [enter 1],\n");
    printf("                  by code [enter 2],\n");
    printf("               OR no list [enter 0]: ");
    scanf("%d",&inp);
    printf("\n");

    int listSize = 10;
    printf("Desired length of list(s): ");
    scanf("%d",&listSize);
    printf("\n");

    int opt = 8;
    printf("Variable to sort by: \n");
    printf("   [1 = population]\n");
    printf("   [2 = GDP]\n");
    printf("   [3 = GDP per capita]\n");
    printf("   [4 = GHG emissions]\n");
    printf("   [5 = GHG emissions per capita]\n");
    printf("   [6 = renewable energy production]\n");
    printf("   [7 = renewable energy production per capita]\n");
    printf("   [8 = ALL of the above]\n");
    scanf("%d",&opt);
    printf("\n");

    if (inp != 0) {
        if (inp == 1) {
            printf("Countries (alphabetical by name):\n");
        } else {
            sortCountriesByCode(allData, NUM_COUNTRIES);
            printf("Countries (alphabetical by code):\n");
        }
        printf("   CODE   COUNTRY_NAME\n");
        for (int i = 0; i < NUM_COUNTRIES; ++i) {
            printf("   %s    %s\n",allData[i].code, allData[i].name);  
        }
    }
    
    
   
    printf("\n");

    //FIRST, SORT BY POPULATION & REPORT THE TOP 10
    if (opt == 1 || opt == 8) {
        sortCountriesByPop(allData, NUM_COUNTRIES);
        printf("The %d countries with the largest\n",listSize);
        printf(" population (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.0lf \n",i+1,allData[i].name,allData[i].pop);
        }
        printf("\n");
    }
   
    //THEN, SORT BY GDP & REPORT THE TOP 10
    if (opt == 2 || opt == 8) {
        sortCountriesByGDP(allData, NUM_COUNTRIES);
        printf("The %d countries with the highest\n",listSize);
        printf(" GDP (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.0lf USD\n",i+1,allData[i].name,allData[i].gdp);
        }
        printf("\n");
    }
   
    //NEXT, SORT BY GDP PER CAPITA & REPORT THE TOP 10
    if (opt == 3 || opt == 8) {
        sortCountriesByGDPperCap(allData, NUM_COUNTRIES);
        printf("The %d countries with the highest\n",listSize);
        printf(" GDP per capita (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.2lf USD\n",i+1,allData[i].name,allData[i].gdp/allData[i].pop);
        }
        printf("\n");
    }
   
    //NOW, SORT THE COUNTRY DATA BY GREENHOUSE GAS EMISSIONS & REPORT THE TOP 10
    if (opt == 4 || opt == 8) {
        sortCountriesByGHG(allData, NUM_COUNTRIES);
        printf("The %d countries with the most greenhouse\n",listSize);
        printf(" gas emissions (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.2lf million-tonnes-of-CO2\n",i+1,allData[i].name,allData[i].ghg);
        }
        printf("\n");
    }
   
    //NEXT, SORT BY GREENHOUSE GAS EMISSIONS PER CAPITA & REPORT THE TOP 10
    if (opt == 5 || opt == 8) {
        sortCountriesByGHGperCap(allData, NUM_COUNTRIES);
        printf("The %d countries with the most greenhouse\n",listSize);
        printf(" gas emissions per capita (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.2lf tonnes-of-C02/person\n",i+1,allData[i].name,allData[i].ghg/allData[i].pop*1000000);
        }
        printf("\n");
    }

    //THEN, SORT BY ELECTRICITY GENERATED BY RENEWABLE SOURCES & REPORT THE TOP 10
    if (opt == 6 || opt == 8) {
        sortCountriesByRE(allData, NUM_COUNTRIES);
        printf("The %d countries with the most electricity generation\n",listSize);
        printf(" from renewable sources (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.2lf GWh\n",i+1,allData[i].name,allData[i].renewable);
        }
        printf("\n");
    }

    //LAST, SORT BY ELECTRICITY GENERATED BY RENEWABLE SOURCES PER CAPITA & REPORT THE TOP 10
    if (opt == 7 || opt == 8) {
        sortCountriesByREperCap(allData, NUM_COUNTRIES);
        printf("The %d countries with the most electricity generation\n",listSize);
        printf(" from renewable sources per capita (2012-2016 avg.) are:\n");
        for (int i = 0; i<listSize;  i++) {
            printf("   #%d %s: %.2lf MWh/person\n",i+1,allData[i].name,allData[i].renewable/allData[i].pop*1000);
        }
        printf("\n");
    }

    char mycode[4] = "USA";
    while (strcmp(mycode, "END") != 0) {
        printf("Enter a country CODE to view its full \n");
        printf(" energy details [enter END to exit]...");
        printf("\n");
        scanf("%s",mycode);
        printf("\n");
        if (strcmp(mycode, "END") != 0) {
            int ind = findCountry(allData,NUM_COUNTRIES,mycode);
            if (ind >= 0) {
                printDetails(allData[ind]);
            }
        }
        printf("\n");
    }

   return 0;
}