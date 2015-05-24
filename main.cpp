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

void readTracking(string tFile, vector<employee> &employees){
 ifstream fin;
 fin.open(tFile);
 int n;
 int ts;
 int eid;
 int loc;
 fin >> n;
 for(int i = 0; i < n; i++){
  fin >> ts;
  fin >> eid;
  fin >> loc;
  for(int j = 0; j < employees.size(); j++){
   if(employees[j].getID() == eid){
    employees[j].addStamp(ts, loc);
   }
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

int main(int argc,char* argv[]){
 vector<stamp> smoke;
 vector<employee> employees;
 readSmoke("smoke.dat", smoke);
 readEmployee("employee.dat", employees);
 readTracking("tracking.dat", employees);
 reportFriends(employees[25], employees);
 return 0;
}
