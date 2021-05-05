#include <iostream>
#include <String.h>
//#include "Date.h"
#ifndef "_TASK_"
#define "_TASK_"

class Task {
	friend ostream& operator << (ostream&);
protected:
	string name;
	Date deadline;
	bool isDone;
	int time;
public:
	Task(string name);
	string getName() const;
	Date getDeadline() const;
	bool getIsDone() const;
	int getTime() const;
	void setName(string name);
	bool setDeadline(string deadline);
	bool setTime(int time);
	void toogle();
	
	
};
#endif