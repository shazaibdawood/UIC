#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Student_struct {
    char name[15];
    int credits;
    int points;
    double gpa;
    bool active;
} Student;

void readStudentInfo(Student* aStud) {
    printf("Reading in Student Info:");
    printf("\n  Name: ");
    scanf("%s",(*aStud).name);
    printf("\n  Total Number of Credits: ");
    scanf("%d",&((*aStud).credits));
    printf("\n  Total GPA points earned: ");
    scanf("%d", &(aStud->points));
    printf("\n  Is Student Active (1 = Yes, 0 = No): ");
    int temp;
    scanf("%d",&temp);
    if (temp == 0) {
        aStud->active = 0;
    } else {
        aStud->active = 1;
    }
    printf("\n");
}

void calcGPAs(Student* theStuds, int n) {
    for (int i = 0; i < n; ++i) {
        theStuds[i].gpa = (double)theStuds[i].points / theStuds[i].credits;
    }
}

int printDeansList(Student* theStuds, int n) {
    int count = 0;
    printf("Dean's List:\n");
    for (int i = 0; i < n; ++i) {
        if (theStuds[i].active && theStuds[i].gpa >= 3.0) {
            printf("  %s earned %0.2lf gpa\n",theStuds[i].name,theStuds[i].gpa);
            count++;
        }
    }
    return count;
}

int main(void) {

    int numStudents;
    printf("Enter number of Students: ");
    scanf("%d", &numStudents);
    printf("\n");

    Student* studs = (Student*)malloc(numStudents*sizeof(Student));
    for (int i = 0; i < numStudents; i++) {
        readStudentInfo(&studs[i]);
    }

    calcGPAs(studs, numStudents);

    int szDL = printDeansList(studs, numStudents);
    printf("Number of Students on Dean's List = %d\n",szDL);
    free(studs);


    return 0;
}
