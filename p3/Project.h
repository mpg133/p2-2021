#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#ifndef _PROJECT_H_
#define _PROJECT__H

class Project {
	friend ostream& operator << (ostream&,const Project &project);
protected:
	int id;
	string name;
	string description;
	vector<List> lists;
public:
	Project(string name,description= "");
	int getId()const;
	string getName()const;
	string getDescription() const;
	int getPostList(string name) const;
	bool setId(int id);
	bool setName(string name = "");
	void setDescription(string name = "");
	void edit(string name = "", string description="");
	void addList(string name = "");
	void deleteList(string name="");
	void addTaskToList(string name = "");
	void deleteTaskFromList(string name = "");
	void toogleTaskFromList(string name = "");
	void menu();
	string summary() const;



};
#endif