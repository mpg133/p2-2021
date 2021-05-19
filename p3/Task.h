#ifndef __TASK__
#define __TASK__
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
//#include "Date.h"

struct Date {
	int day;
	int month;
	int year;
};
class Task {
	friend ostream& operator << (ostream & ,const Task &task);
protected:
	string name;
	Date deadline;
	bool isDone;
	int time;
	bool CheckDate(int day, int month, int year);
	vector<string> getDeadline(string date);
public:
	Task(string name);
	string getName() const;
	Date getDeadline() const;
	bool getIsDone() const;
	int getTime() const;
	void setName(string name);
	bool setDeadline(string deadline);
	bool setTime(int time);
	void toggle();
	
	
};
#endif