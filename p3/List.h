#include <iostream>
#include <String.h>

#ifndef "_LIST_H_"
#define "_LIST__H"

class List {
	friend ostream& operator << (ostream&);
	protected:
		string name;
public:
	List(string name);
	string getName() const;
	vector<Task> getTasks() const;
	unsigned getNumTasks()const;
	unsigned getNumDone()const;
	int getTimeTasks() const;
	int getTimeDone() const;
	int getPosTask(string name) const;
	bool setName(string name);
	void addTask(const Task& task);
	bool deleteTAsk(string name);
	bool toggleTask(string name);


};
#endif