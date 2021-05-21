#include <iostream>
#include <string.h>
#include<sstream>
#include <vector>
#include <stdio.h>
#include "ToDo.h"
#include "Util.h"
using namespace std;

 int ToDo::nextId =1;
ToDo::ToDo(string name){
    if(!name.empty()){
        this->name=name;
    }else{
        throw ERR_EMPTY;
    }
    
}
string ToDo::getName() const {
    return name;
}
int ToDo::getPosProject(string name) const {
    for(unsigned i=0;i<projects.size();i++){
        if(projects[i]->getName()==name){
            return i;
        }
    }
    return -1;
}
int ToDo::getPosProject(int id) const {
    for(unsigned i=0;i<projects.size();i++){
        if(projects[i]->getId()==id){
            return i;
        }
    }
    return -1;
}
bool ToDo::setName(string name){
    if(!name.empty()){
        this->name=name;
        return true;
    }else{
        Util::error(ERR_EMPTY);
        return false;
    }
}
void ToDo::addProject(Project *project){
    if(getPosProject(project->getName())==-1){
        project->setId(nextId);
        //ToDo::nextId++;
        nextId++;
        projects.push_back(project);
    }else{
        throw ERR_PROJECT_NAME;
    }
}
void ToDo::deleteProject(int id){
int idUsu;
    if(id!=0){
        idUsu=id;
    }else{
        cout<<"Enter project id: "<<endl;
        cin>>idUsu;
    }

    if(getPosProject(idUsu)!=-1){
        projects.erase(projects.begin() + getPosProject(idUsu));
    }else{
        Util::error(ERR_ID);
    }
}
void ToDo::setProjectDescription(string name,string description){
    bool exist=false;
    for(unsigned i=0;i<projects.size();i++){
        if(projects[i]->getName()==name){
            projects[i]->setDescription(description);
            exist=true;
        }
    }
    if(!exist){
        Util::error(ERR_PROJECT_NAME);
    }
}
void ToDo::projectMenu(int id){
    int usuId=0;
    if(id==0){
        cout<<"Enter project id: ";
        cin>>usuId;
    }else{
        usuId=id;
    }
    
    if(getPosProject(usuId)!=-1){
        projects[getPosProject(usuId)]->menu();
    }
    
}
ostream& operator << (ostream &os,const ToDo &toDo){

    for(unsigned i=0;i<toDo.projects.size();i++){
       os<<toDo.projects[i]->summary()<<endl;
    }

return os;
}