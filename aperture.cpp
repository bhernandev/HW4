#include "aperture.h"

employee::employee(int id, string f, string l, int off){
 ID = id;
 fName = f;
 lName = l;
 office = off;
}

void employee::addStamp(int t, int l){
 stamp s = {t,l};
 locations.push_back(s);
}

bool employee::slacks(){
 double p = 0;
 for(int i = 0; i <(locations.size()); i++){
  if(locations[i].loc == office){
   p+=1;
  }
 }
 if((p/locations.size()) <= 0.75){
  return true;
 }
 else{
  return false;
 }
}

bool employee::smokes(vector<stamp> smokes){
 double p;
 for(int i = 0; i < smokes.size(); i++){
  for(int j = 0; j < locations.size(); j++){
   if(smokes[i].loc == locations[j].loc){
    p+=1;
   }
  }
 }
 if( (p/locations.size()) >= 0.01 ){
  return true;
 }
 else{
  return false;
 }
}

int employee::getID(){
 return ID;
}

string employee::getFName(){
 return fName;
}

string employee::getLName(){
 return lName; 
}

int employee::getOffice(){
 return office;
}

int employee::getTime(int i){
 return locations[i].time;
}

int employee::getLoc(int i){
 return locations[i].loc;
}

int employee::getLocSize(){
 return locations.size();
}
