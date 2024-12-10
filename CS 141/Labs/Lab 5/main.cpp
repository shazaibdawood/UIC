#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

int main() {

   string fileName;
   ifstream inFS;
   ofstream oFS;
   vector<string> lName(16);
   vector<string> fName(16);
   vector<int> m1Scores(16);
   vector<int> m2Scores(16);
   vector<int> fScores(16);
   int count = 0;
   double average;
   double totalM1 = 0;
   double totalM2 = 0;
   double totalF = 0;
   char grade;


   cin >> fileName;
   inFS.open(fileName);

   if(!inFS.is_open())
   {
      cout << "File not opened" << endl;
    return -1;
   }

   while(!inFS.eof())
   {
      if(!inFS.fail())
      {
         inFS >> lName.at(count) >> fName.at(count) >> m1Scores.at(count) >> m2Scores.at(count) >> fScores.at(count);
         count++;
      }
      else
      {
         cout << "File input failed" << endl;
         return -1;
      }
   }

   inFS.close();

   oFS.open("report.txt");
   if(!oFS.is_open())
   {
      cout << "file not opened" << endl;
      return -1;
   }

   for(int i = 0; i < count - 1; i++)
   {
      average = (m1Scores.at(i) + m2Scores.at(i) + fScores.at(i)) / 3.0;
      totalM1 += m1Scores.at(i);
      totalM2 += m2Scores.at(i);
      totalF += fScores.at(i);

      if(average >= 90)
      {
         grade = 'A';
      }
      else if(average >= 80)
      {
         grade = 'B';
      }
      else if(average >= 70)
      {
         grade = 'C';
      }
      else if(average >= 60)
      {
         grade = 'D';
      }
      else
      {
         grade = 'F';
      }

      oFS << lName.at(i) << '\t' << fName.at(i) << '\t' << m1Scores.at(i) << '\t' << m2Scores.at(i) << '\t' << fScores.at(i) << '\t' << grade << endl;
   }

    totalM1 /= count - 1;
    totalM2 /= count - 1;
    totalF /= count - 1;

    oFS << endl;
    oFS << "Averages: ";
    oFS << fixed << setprecision(2);
    oFS << "midterm1 " << totalM1 << ", midterm2 " << totalM2 << ", final " << totalF;
    oFS << endl;

    oFS.close();

   return 0;
}
