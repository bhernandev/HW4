#include <iostream>
#include <fstream>
#include <cmath>
#include "aperture.h"
using namespace std;

void readSmoke(string sFile, vector<stamp> &smoke){
 ifstream fin;
 fin.open(sFile);
 int n;
 fin >> n;
 smoke.resize(n);
 for(int i = 0; i < n; i++){
  fin >> smoke[i].time;
  fin >> smoke[i].loc;
 }
}

void readEmployee(string eFile, vector<employee> &employees){
 ifstream fin;
 fin.open(eFile);
 int n;
 int id;
 string f;
 string l;
 int off;
 fin >> n;
 for(int i = 0; i < n; i++){
  fin >> id;
  fin >> f;
  fin >> l;
  fin  >> off;
  employees.push_back(employee(id,f,l,off));
 }
}

void readTracking(string tFile, vector<employee> &employees, int &min, int &max){
 ifstream fin;
 fin.open(tFile);
 int n;
 int ts;
 int eid;
 int loc;
 fin >> n;
 fin >> ts;
 min = ts;
 for(int i = 0; i < n; i++){
  fin >> eid;
  fin >> loc;
  for(int j = 0; j < employees.size(); j++){
   if(employees[j].getID() == eid){
    employees[j].addStamp(ts, loc);
   }
  }
  fin >> ts;
 }
 max = ts;
}

void reportSlackers(vector<employee> employees){
 for(int i = 0; i < employees.size(); i++){
  if(employees[i].slacks()){
   cout << employees[i].getFName() << " slacks." << endl; 
  }
 }
}

void reportSmokers(vector<employee> employees, vector<stamp> smoke){
 for(int i = 0; i < employees.size(); i++){
  if(employees[i].smokes(smoke)){
   cout << employees[i].getFName() << " smokes." << endl;
  }
 }
}

void reportFriends(employee e, vector<employee> employees){
 for(int i = 0; i < 10; i++){
  int highest = 0;
  int bff = 0;
  int count = 0;
  for(int j = 0; j < employees.size(); j++){
   if(!(e.getOffice() == employees[j].getOffice())){
    for(int k = 0; k < e.getLocSize(); k++){
     if(e.getLoc(k) == employees[j].getLoc(k) && e.getTime(k) == employees[j].getTime(k)){
      count += 1;
     }
    }
   }
   if(count > highest){ 
    bff = j;
    highest = count;
   }
   count = 0;
  }
  cout << "Friend # " << i + 1 << " " << employees[bff].getFName() << endl; 
  employees.erase(employees.begin() + bff);
 }
}

void reportBroken(vector<employee> employees, int min, int max){
 for(int i = 0; i < employees.size(); i++){
  bool malfunction = true;
  double malfunctions = 0.0;
  for(int j = min; j <= max; j++){
   for(int k = 0; k < employees[i].getLocSize(); k++){
    if(employees[i].getLoc(k) == j){
     malfunction = false;
     break;
    }
   }
   if(malfunction == true){
    malfunctions += 1;
   }
  }
  if( (malfunctions/employees[i].getLocSize()) < 0.95){
   cout << employees[i].getFName() << " has a malfunctioning tracking device. " << endl;
  }
 }
}

bool finTest(string file){
 ifstream fin;
 fin.open(file);
 if(fin.fail()){
  return true;
 }
 else{
  return false;
 }
}

void mainMenu(vector<employee> employees, vector<stamp> smoke, int min, int max){
 bool exit = false;
 char input;
 while(!exit){
  cout << endl << ":Main Menu: " << endl;
  cout << "a - Report slackers" << endl;
  cout << "b - Report suspected smokers" << endl;
  cout << "c - Report employee's friends" << endl;
  cout << "d - Identify broken tracking devices" << endl;
  cout << "e - Exit" << endl;
  cin >> input;
  if(input == 'a'){
   reportSlackers(employees);
  }
  if(input == 'b'){
   reportSmokers(employees, smoke);
  }
  if(input == 'c'){
   string fName;
   string lName;
   cout << "Please enter first name of desired employee." << endl;
   cin >> fName;
   cout << "Please enter last name of desired employee." << endl;
   cin >> lName;
   bool exists = false;
   for(int i = 0; i < employees.size(); i++){
    if(employees[i].getFName() == fName && employees[i].getLName() == lName){
     exists = true;
     reportFriends(employees[i], employees);
    }
   }
   if(exists == false){
   cout << "Error: Specified employee cannot be found." << endl;
   }
  }
  if(input == 'd'){
   reportBroken(employees, min, max);
  }
  if(input == 'e'){
   exit = true;
  }
 }
}

int main(int argc,char* argv[]){
 int min;
 int max;
 vector<stamp> smoke;
 vector<employee> employees;
 if(argc != 4){
 }
 string emp = argv[1];
 string tra = argv[2];
 string smo = argv[3];
 if(finTest(emp)){
  cout << "Error : Could not open employee file" << endl;
  return 1;
 }
 if(finTest(tra)){
  cout << "Error : Could not open tracking file" << endl;
  return 1;
 }
 if(finTest(smo)){
  cout << "Error : Could not open smoke file" << endl;
  return 1;
 }
 readEmployee(emp, employees);
 readTracking(tra, employees, min, max);
 readSmoke(smo, smoke);
 mainMenu(employees, smoke, min, max);
 return 0;
}
