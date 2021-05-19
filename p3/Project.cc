#include <iostream>
#include <string.h>
#include<sstream>
#include <vector>
#include <stdio.h>
#include "Project.h"
using namespace std;
//----------------------------------funciones auxiliares-------------------------------------


void Project::showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}
int Project::Oldest(List list){

int oldPos=0;// the position of the oldest

  for(unsigned int i=0; i<list.getNumTasks();i++){

    if(!list.getTasks()[i].getIsDone()){
      if(list.getTasks()[i].getDeadline().year<list.getTasks()[oldPos].getDeadline().year){ oldPos=i; }

      else if(  list.getTasks()[i].getDeadline().year==list.getTasks()[oldPos].getDeadline().year
            &&  list.getTasks()[i].getDeadline().month<list.getTasks()[oldPos].getDeadline().month){ oldPos=i; }

      else if(  list.getTasks()[i].getDeadline().year==list.getTasks()[oldPos].getDeadline().year
                && list.getTasks()[i].getDeadline().month==list.getTasks()[oldPos].getDeadline().month
                && list.getTasks()[i].getDeadline().day<list.getTasks()[oldPos].getDeadline().day){ oldPos=i; }
    }

  }

return oldPos;
}

void Project::showPriority(){
  Task prioTask();
  int oldPos=0;
  List AuxList();
  for(unsigned i=0;i<lists.size();i++){
    if(lists[i].getNumTasks()>0){
      for(unsigned int j=0;j<lists[i].getNumTasks();j++){
        if(!lists[i].getTasks()[j].getIsDone()){
          AuxList.getTasks().push_back(lists[i].getTasks()[j]);
        }
      }
    }
  }
  if(AuxList.getNumTasks()>0){
    oldPos=Oldest(AuxList);
    prioTask=AuxList.getTasks()[oldPos];
    cout<<prioTask.getName()<<" ("<<prioTask.getDeadline().year<<"-"<<prioTask.getDeadline().month<<"-"<<prioTask.getDeadline().day<<")";
  }

}
string Project::AskName (string name2, bool askProject){
  do{
    if(askProject){//if is true ask for project name
        cout<<"Enter project name: ";
    }else{
       cout<<"Enter list name: ";
    }
    getline(cin,name2);
    if(name.empty()){
      Util::error(ERR_EMPTY);
    }
  }while(name2.empty());
  return name2;
}


Project::Project(string name2,string description2){

    if(!name2.empty()){
        name=name2;
        description=description2;
        id=0;
    }else{
        throw ERR_EMPTY;
    }
}
int Project::getId() const{
    return id;
}
string Project::getName() const {
    return name;
}
string Project::getDescription() const {
    return description;
}
int Project::getPosList(string nameList) const{
    for(unsigned i=0;i<lists.size();i++){
        if(lists[i].getName()==nameList){
            return i;
        }
    }
    return -1;
}
bool Project::setId(int id2){
    if(id2>=0){
        id=id2;
        return true;
    }else{
        Util::error(ERR_ID);
        return false;
    }
}
bool Project::setName(string name2){
    if(!name2.empty()){
        name=name2;
        return true;
    }else{
        Util::error(ERR_EMPTY);
        return false;
    }
}
void Project::setDescription(string description2){
    description=description2;
}
void Project::edit(string name2,string description2){
    cin.clear();
    string usuName;
    string usuDesc;
    if(name2.empty()){
        usuName=AskName("",true);
        setName(usuName);
            
    }else{
        setName(name2);
    }
    if(description2.empty()){
        cout<<"Enter project description: ";
        getline(cin,usuDesc);
        setDescription(usuDesc);
    }else{
        setDescription(description2);
    }

}   
void Project::addList(string nameList){
 cin.clear();
 string usuName;
 try{   
    if(nameList.empty()){
        usuName=AskName("",false); 
        List list(usuName);
        lists[getPosList(usuName)].getTasks().clear();
        lists.push_back(list);
    }else{
        List list(nameList);
        lists[getPosList(usuName)].getTasks().clear();
        lists.push_back(list);
    }
  }catch(Error ERR_LIST_NAME){
    Util::error(ERR_LIST_NAME);
    return;
  }
   
}
void Project::deleteList(string name2){
    cin.clear();
 string usuName; 
    if(name2 == ""){
        usuName = AskName("",false);
    }else{
        usuName=name2;
    }
    if(getPosList(name2)!=-1){
        lists.erase(lists.begin()+getPosList(name2));
    }else{           
        Util::error(ERR_LIST_NAME);
    }
   

}
void Project::addTaskToList(string name2){
   cin.clear();
   string taskName,deadline;   
   int time=0;
    string usuName; 
    if(name2 == ""){
        usuName = AskName("",false);
    }else{
        usuName=name2;
    }
    if(getPosList(usuName)!=-1){
        cout<<"Enter task name: ";
        getline(cin,taskName);
        Task task(taskName);
        cout<<"Enter deadline: ";
        getline(cin,deadline);
        task.setDeadline(deadline);
        cout<<"Enter expected time: ";
        cin>>time;
        task.setTime(time);
        lists[getPosList(usuName)].getTasks().push_back(task);
    }else{
        Util::error(ERR_LIST_NAME);
    }
   
}
void Project::deleteTaskFromList(string name2){

    string usuName,taskName;
    int SameName=0;
     cin.clear();
     if(name2 == ""){
        usuName = AskName("",false);
    }else{
        usuName=name2;
    }
    int listPos=getPosList(usuName);
    if(listPos!=-1){
        cout<<"Enter task name: ";
        getline(cin,taskName);
        for(unsigned int i=0;i<lists[listPos].getTasks().size();i++){
            if(lists[listPos].getTasks()[i].getName()==taskName){
                 SameName++;
            }
        }
        if(SameName!=0){
        for(int j=0;j<SameName;j++){ //borra la tareas con el mismo nombre
          for(unsigned int i=0;i<lists[listPos].getTasks().size();i++){
                if(lists[listPos].getTasks()[i].getName()==taskName){
                  //delete the tasks at vector lists
                  lists[listPos].getTasks().erase(lists[listPos].getTasks().begin()+i);
                  i--;
                    
                }
            }   
        }
        }else{
            Util::error(ERR_TASK_NAME);
        }

    }else{
        Util::error(ERR_LIST_NAME);
    }


}
void Project::toggleTaskFromList(string name2){
      cin.clear();
      string usuName; 
      bool tasknameErr=true;

    if(name2 == ""){
        usuName = AskName("",false);
    }else{
        usuName=name2;
    }
    int listPos=getPosList(usuName);
    if(listPos!=-1){
        string taskName;
        cout<<"Enter task name: ";
        getline(cin,taskName);
        
        int taskSize=lists[listPos].getTasks().size();

        if(lists[listPos].getTasks().size()==0){
            Util::error(ERR_TASK_NAME);
        }else{
            
        for(int i=0;i<taskSize;i++){
            if(lists[listPos].getTasks()[i].getName()==taskName){
                tasknameErr=false;
                lists[listPos].getTasks()[i].toggle();
            }

        }   
            if(tasknameErr){
                 Util::error(ERR_TASK_NAME);
            }
        }
    }else{
        Util::error(ERR_LIST_NAME);
    }
}
void Project::menu(){


    char option;

  do{
    showMainMenu();
    cin >> option;
    cin.get();

    switch(option){
      case '1': edit();
                break;
      case '2': addList();
                break;
      case '3': deleteList();
                break;
      case '4': addTaskToList();
                break;
      case '5': deleteTaskFromList();
                break;
      case '6': toggleTaskFromList();
                break;
      case '7': cout<<*this<<endl;
                break;
      case 'q': break;
      default: Util::error(ERR_OPTION);
    }
  }while(option!='q');

}
string Project::summary() const{


}
ostream& operator << (ostream &os,const Project &project){
    os<<"Name: "<<project.getName()<<endl;
    int numTasks = 0;
    int numDone = 0;
    int timeTotal = 0;
    int timeDone = 0;
    os<<"Description: "<<project.getDescription()<<endl;
    for(unsigned i=0;i<project.lists.size();i++){
        os<<project.lists[i];
        numTasks += project.lists[i].getNumTasks();
        numDone += project.lists[i].getNumDone(); 
        timeTotal += project.lists[i].getTimeTasks();
        timeDone += project.lists[i].getTimeDone();

    }
    
    os<<"Total left: "<<numTasks - numDone<<" ("<<timeTotal - timeDone<<")"<<endl;
    os<<"Total done: "<<numDone<<" ("<<timeDone<<")"<<endl;
    os<<"Highest priority";
    showPriority();
    os<<endl;
    return os;
}    