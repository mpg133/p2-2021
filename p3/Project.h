
#ifndef _PROJECT__H_
#define _PROJECT__H_
#include <iostream>
#include <string.h>
#include <vector>
#include "Util.h"
#include "List.h"

using namespace std;


class Project {
	friend ostream& operator << (ostream&,const Project &project);
protected:
	void showPriority() const;
	int Oldest(List list) const;
	void showMainMenu();
	string AskName(string name, bool ask);
	int id;
	string name;
	string description;
	vector<List> lists;
public:
	Project(string name,string description= "");
	int getId()const;
	string getName()const;
	string getDescription() const;
	int getPosList(string name) const;
	bool setId(int id);
	bool setName(string name = "");
	void setDescription(string name = "");
	void edit(string name = "", string description="");
	void addList(string name = "");
	void deleteList(string name="");
	void addTaskToList(string name = "");
	void deleteTaskFromList(string name = "");
	void toggleTaskFromList(string name = "");
	void menu();
	string summary() const;



};
#endif