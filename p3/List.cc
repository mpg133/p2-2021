#include <iostream>
#include <string.h>
#include<sstream>
#include <vector>
#include <stdio.h>
#include "List.h"
using namespace std;

List::List(string name2){ //throw error(ERR_EMPTY){
    if(name2.empty()){
 	throw ERR_EMPTY;
       
    }else{
        name=name2;
    }
}
string List::getName() const{
    return name;
}
vector<Task> List::getTasks() const{
    return tasks;
}
unsigned List::getNumTasks() const{
    return tasks.size();
}
unsigned List::getNumDone() const{
    unsigned done=0;
    for(unsigned i=0;i<getNumTasks();i++){
        if(tasks[i].getIsDone()){
            done++;
        }
    }
    return done;
}
int List::getTimeTasks() const{
    int time=0;
    for(unsigned i=0;i<getNumTasks();i++){
        time+=tasks[i].getTime();
    }
    return time;
}
int List::getTimeDone() const{
    int timeDone=0;
    for(unsigned i=0;i<getNumTasks();i++){
        if(tasks[i].getIsDone()){
            timeDone+=tasks[i].getTime();
        }
    }

    return timeDone;
}
int List::getPosTask(string name) const{
    for(unsigned i=0;i<getNumTasks();i++){
        if(tasks[i].getName()==name){
            return i;
        }
    }
    return -1;
}
bool List::setName(string name2){
    if(name2.empty()){
        Util::error(ERR_EMPTY);
        return false;
    }else{
        name=name2;
        return true;
    }
    
}
void List::addTask(const Task &task){
    tasks.push_back(task);
}
bool List::deleteTask(string name2){
    unsigned sameName=0;
    for(unsigned i=0;i<getNumTasks();i++){
        if(tasks[i].getName()==name2){
            sameName++;
        }
    }
    if(sameName==0){
        Util::error(ERR_TASK_NAME);
        return false;
    }else{
        for(unsigned i=0;i<sameName;i++){
            for(unsigned j=0;j<getNumTasks();j++){
                if(tasks[j].getName()==name2){
                    tasks.erase(tasks.begin()+j);
                    j--;
                }
            }
        }
        return true;
    }
    
    
}
bool List::toggleTask(string name2){
    unsigned sameName=0;
   
    
       
    for(unsigned j=0;j<getNumTasks();j++){
        if(tasks[j].getName()==name2){
            sameName++;
            tasks[j].toggle();
        }
    }
        

    if(sameName==0){
        Util::error(ERR_TASK_NAME);
        return false;
    }
    return true;
    
}
ostream& operator << (ostream &os,const List &list){
    os<<list.getName()<<endl;
    for(unsigned i=0;i<list.getNumTasks();i++){
        if(!list.tasks[i].getIsDone()){
            os<<list.tasks[i];
        }    
        
    }
    for(unsigned i=0;i<list.getNumTasks();i++){
        if(list.tasks[i].getIsDone()){
            os<<list.tasks[i];
        }    
        
    }

    return os;
}
