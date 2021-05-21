#ifndef _TODO_H_
#define _TODO_H_
#include <iostream>
#include <vector>
#include<string.h>
#include "Project.h"
#include "Util.h"
using namespace std;


class ToDo {
	protected:
		vector<Project*> projects ;	//vector<Project> *projects;
	
		static int nextId;
		string name;
	public:
		ToDo(string name);
		string getName() const;
		int getPosProject(string name)const;
		int getPosProject(int id)const;
		bool setName(string name);
		void addProject(Project* project);
		void deleteProject(int id = 0);
		void setProjectDescription(string name, string description);
		void projectMenu(int id = 0);
	friend
		ostream& operator << (ostream&, const ToDo& toDo);



};

#endif