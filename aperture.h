#ifndef APERTURE_H
#define APERTURE_H
#include <string>
#include <vector>
using namespace std;

struct stamp{
 int time;
 int loc;
};

class employee{
public:
 employee(int id, string f, string l, int off);
 void addStamp(int t, int l);
 bool slacks();
 bool smokes(vector<stamp> smokes);
 int getID();
 string getFName();
 string getLName();
 int getOffice();
 int getTime(int i);
 int getLoc(int i);
 int getLocSize();
private:
 int ID;
 string fName;
 string lName;
 int office;
 vector<stamp> locations;
};

#endif
