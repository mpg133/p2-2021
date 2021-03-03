//DNI 74395666G Pérez Giménez, Miguel

#include <cstdlib>
#include <iostream>
#include<sstream>
#include <vector>
#include <stdio.h>
#include<string.h>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};
struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};


struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};
enum Cad{
  PROJ_NAME,
  LIST_NAME,
  TASK_NAME,



}
void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}
//function that have the couts, like error
void show(Cad a){
  switch(a){
    case PROJ_NAME:
      cout<<"Enter project name: ";
      break;
    case LIST_NAME:
      cout<<"Enter list name: ";
      break;
    case TASK_NAME:
      cout<<"Enter task name: ";
      break;
    case ENTER_DESC:
      cout<< "Enter project description: ";
      break;
    case ENTER_DEADLINE:
      cout<<"Enter task name: ";
      break;
    case ENTER_TIME:
      cout<<"Enter expected time: ";
      break;
    case TOTAL_0:
      cout<<"Total left: 0 (0 minutes)"<<endl;
      cout<<"Total done: 0 (0 minutes)"<<endl;
  }




}
void showMainMenu(){
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
//-------------------------------------------------------------------------------------
//function that ask for List name or Project Name until is not empty
//the variable askProject controls the cout
string AskName (string name, bool askProject){
  do{
    if(askProject){//if is true ask for project name
      show(PROJ_NAME);
    }else{
      show(LIST_NAME);
    }
    getline(cin,name);
    if(name.empty()){
      error(ERR_EMPTY);
    }
  }while(name.empty());
  return name;
}

void editProject(Project &toDoList){
  cin.clear();//clean buffer
  string newName=AskName("",true);// new Project name
  string newDescription="";

  show(ENTER_DESC);
  getline(cin,newDescription);// new Project Description
  toDoList.name=newName;
  toDoList.description=newDescription;
}

//search at list what pos have the name
//if name don't exist-> return -1;
//else return pos of name;
int SearchList(const string &list_name,const Project &toDoList){
int ret=-1;//variable that return the function
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(toDoList.lists[i].name==list_name){
      ret= i;
    }
}
  return ret;
}

void addList(Project &toDoList){
  cin.clear();
  string name=AskName("",false);//name of the list

  if(SearchList(name ,toDoList)==-1){ //if the name don't exist
    List list; //new List at Project
    list.name=name;
    list.tasks.clear();
    toDoList.lists.push_back(list);//put list at end of vector Project.lists
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteList(Project &toDoList){
  cin.clear();
  string name=AskName("",false);//name of the list
  if(SearchList(name,toDoList)!=-1){
    toDoList.lists.erase(toDoList.lists.begin()+SearchList(name,toDoList));
  }else{
    error(ERR_LIST_NAME);
  }
}
//function that return true if date is correct
bool CheckDate(int day,int month,int year){
  bool ret=false;//variable that return if date is correct or not
  bool leap=false;//variable to look if year is leap

  //check if is leap(bisiesto)
  if(year%4==0){
    if(year%100 && year%400) {leap=true;}
    else if(year%100){leap=false;}
    else{leap=true;}
  }

  //check the date
  if(0<month && month<13 && 0<day && day<32 && year>=1900 && year<=2100){
      //Months 4,6,9,11 have 30 days
      if((month==4 || month==6 || month == 9 || month ==11) && day<=30){
          ret=true;
      }
      else{
        if(month==2 && leap && day<=29) {ret=true;}
        else if(month==2 && day<=28) {ret=true;}
        else if(month!=2) {ret=true;}
      }
  }
  return ret;
}

//Class that creates a Task with (!isDone) / (copy constructor)
Task CreateTask(string name,int day,int month,int year,int dead){
  Task task;
  task.name=name;
  task.deadline.day=day;
  task.deadline.month=month;
  task.deadline.year=year;
  task.time=dead;
  task.isDone=false;
  return task;
}
//function that get string and return a vector with the date
vector <string> getDeadline(string date){
  //split String in day, month and year
  char delimiter ='/';
  vector <string> datevector{};//vector that we return
  stringstream sstream(date);
  string StringToVector; //the string that we push to vector
  //read until delimeter
  while(getline(sstream,StringToVector,delimiter)){
  datevector.push_back(StringToVector);
  }
  return datevector;
}

void addTask(Project &toDoList){

  cin.clear();
  string name=AskName("",false);

  if(SearchList(name ,toDoList)!=-1){ //if the list exist...
    string taskName,deadline;
    show(TASK_NAME);
    getline(cin,taskName);
    show(ENTER_DEADLINE);
    getline(cin,deadline);
    vector <string> vec=getDeadline(deadline);
    if(!CheckDate(stoi(vec[0]),stoi(vec[1]),stoi(vec[2]))){
        error(ERR_DATE);
      }else{
        int time=0;
        show(ENTER_TIME);
        cin>>time;
          if(0<time && time<181){
            Task task=CreateTask(taskName,stoi(vec[0]),stoi(vec[1]),stoi(vec[2]),time);
            toDoList.lists[SearchList(name,toDoList)].tasks.push_back(task);
          }else{
            error(ERR_TIME);
          }
      }
  //for see if date is wrong and throw error, GoodFormatDate return day==-1
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteTask(Project &toDoList){
  cin.clear();
  string name=AskName("",false);//List name

  if(SearchList(name ,toDoList)!=-1){
    show(TASK_NAME);
    string taskName;
    getline(cin,taskName);
    int size=toDoList.lists[SearchList(name,toDoList)].tasks.size();//the size of vector tasks at list
    if(size!=0){
      int SameName=0; //the number of tasks with the same name
      for(int i=0;i<size;i++){
        if(toDoList.lists[SearchList(name,toDoList)].tasks[i].name==taskName){
          SameName++;
        }
      }
      if(SameName==0){ // no task with the name that user give
        error(ERR_TASK_NAME);
      }else{

        for(int j=0;j<SameName;j++){ //delete the tasks at vector lists
          for(int i=0;i<size;i++){
            if(toDoList.lists[SearchList(name,toDoList)].tasks[i].name==taskName){
                  toDoList.lists[SearchList(name,toDoList)].tasks.erase(toDoList.lists[SearchList(name,toDoList)].tasks.begin()+i);
              }
            }
        }
      }
    }else{
      error(ERR_TASK_NAME);

    }
  }
}


void toggleTask(Project &toDoList){
  cin.clear();
  string ListName=AskName("",false);
  if(SearchList(ListName,toDoList)!=-1){
      show(TASK_NAME);
      string TaskName;
      getline(cin,TaskName);
      int listpos=SearchList(ListName,toDoList);
      int taskSize=toDoList.lists[listpos].tasks.size();

      if(toDoList.lists[listpos].tasks.size()==0){
        error(ERR_TASK_NAME);
      }else{
        for(int i=0;i<taskSize;i++){
          if(toDoList.lists[listpos].tasks[i].name==TaskName){
            if(toDoList.lists[listpos].tasks[i].isDone==false){
              toDoList.lists[listpos].tasks[i].isDone=true;
            }else{
              toDoList.lists[listpos].tasks[i].isDone=false;
            }
          }
        }
  }
}
}

//fuction that print one task
void printTask(const Task &task){
  cout<<"[";
  if(!task.isDone) {
    cout<<" ";
  }
  else{
    cout<<"X";
  }
  cout<<"] ("<<task.time<<") "
      <<task.deadline.year<<"-"<<task.deadline.month<<"-"<<task.deadline.day
      <<" : "<<task.name<<endl;

}


//function that print Total Done and Total left
void showTotal(const Project &toDoList){
int left=0;
int leftTime=0;
int doneTime=0;
int done=0;
bool noTask=true;
    for(unsigned int i=0;i<toDoList.lists.size();i++){
      for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
        noTask=false;
        if(toDoList.lists[i].tasks[j].isDone==false){
          left++;
          leftTime+=toDoList.lists[i].tasks[j].time;
        }else{
          done++;
          doneTime+=toDoList.lists[i].tasks[j].time;
        }
    }
  }
if(noTask==false){
  cout<<"Total left: "<<left<<" ("<<leftTime<<" minutes)"<<endl;
  cout<<"Total done: "<<done<<" ("<<doneTime<<" minutes)"<<endl;
}else{
  show(TOTAL_0);
}

}
//function that show list.name and call showTasks to print the task of a list
void showLists(const Project &toDoList){
    for(unsigned int i=0;i<toDoList.lists.size();i++){
      cout<<toDoList.lists[i].name<<endl;
      if(toDoList.lists[i].tasks.size()>0){
        //show Tasks
        for(unsigned int j=0; j<toDoList.lists[i].tasks.size();j++){
              if(toDoList.lists[i].tasks[j].isDone==false){
                printTask(toDoList.lists[i].tasks[j]);
              }else{
                  printTask(toDoList.lists[i].tasks[j]);
              }
       }
      }
    }

}

//function that return the position of oldest task in a list
int Oldest(List list){

int pos=0;
if(list.tasks.size()==1){
  pos=0;
}else{
  Task old=list.tasks[0];
    for(unsigned int i=0; i<list.tasks.size();i++){

      if(!list.tasks[i].isDone){

        if(list.tasks[i].deadline.year<old.deadline.year){ pos=i; }
        else if(  list.tasks[i].deadline.year==old.deadline.year && list.tasks[i].deadline.month<old.deadline.month){ pos=i; }
              else if(list.tasks[i].deadline.year==old.deadline.year
                  && list.tasks[i].deadline.month==old.deadline.month
                  && list.tasks[i].deadline.day<old.deadline.day){ pos=i; }

      }else{ pos=i; }

    }
}


return pos;
}
void showPriority(const Project toDoList){
  Task task;
  int pos=0;

  List AuxList;

      for(unsigned i=0;i<toDoList.lists.size();i++){

        if(toDoList.lists[i].tasks.size()>0){

          for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
            if(!toDoList.lists[i].tasks[j].isDone){
              AuxList.tasks.push_back(toDoList.lists[i].tasks[j]);
              }
          }
        }
      }
      if(AuxList.tasks.size()>0){
          pos=Oldest(AuxList);
          task=AuxList.tasks[pos];
            cout<<"Highest priority: "<<task.name<<" ("<<task.deadline.year<<"-"<<task.deadline.month<<"-"<<task.deadline.day<<")"<<endl;
      }

}
void report(const Project &toDoList){

  cout<<"Name: "<<toDoList.name<<endl;
  if(toDoList.description.size()!=0){
    cout<<"Description: "<<toDoList.description<<endl;
  }
  if(toDoList.lists.size()>0){
    showLists(toDoList);
  }
  showTotal(toDoList);
  showPriority(toDoList);
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;

  do{
    showMainMenu();
    cin >> option;
    cin.get();

    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');

  return 0;
}
