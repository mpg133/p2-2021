//DNI 74395666G Pérez Giménez, Miguel
using namespace std;
#include <cstdlib>
#include <iostream>
#include<sstream>
#include <vector>
#include <stdio.h>
#include<string.h>
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

void editProject(Project &toDoList){
  string ProjectName="";
  string ProjectDes="";

  cin.clear();//clean buffer
  do{
    cout<<"Enter project name: ";
    getline(cin,ProjectName);
    if(ProjectName.empty()){
      error(ERR_EMPTY);
    }
  }while(ProjectName.empty());

  cout<< "Enter project description: ";
  getline(cin,ProjectDes);
  toDoList.name=ProjectName;
  toDoList.description=ProjectDes;
}
//function that ask List name until is not empty
//return true if is not empty
string AskName (string name){
  do{
    cout<<"Enter list name: ";
    getline(cin,name);
    if(name.length()==0){
      error(ERR_EMPTY);
    }
  }while(name.empty());
  return name;
}
//search at list what pos have the name
//if no name -> return -1;
//else return pos of name;

int SearchList(string &list_name,Project &toDoList){
int ret=-1;
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(toDoList.lists[i].name==list_name){
      ret= i;
    }
}
  return ret;
}
void addList(Project &toDoList){
  cin.clear();
  string EmptyString="";
  string ListName=AskName(EmptyString);

  if(SearchList(ListName ,toDoList)==-1){
    List newList;
    newList.name=ListName;
    newList.tasks.clear();
    //put list at end of vector Project.lists
    toDoList.lists.push_back(newList);
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteList(Project &toDoList){
  cin.clear();
  string EmptyString="";
  string ListName=AskName(EmptyString);
  if(SearchList(ListName,toDoList)!=-1){
    toDoList.lists.erase(toDoList.lists.begin()+SearchList(ListName,toDoList));
  }else{
    error(ERR_LIST_NAME);
  }
}
//function that return true if date is correct
bool CheckDate(int day,int month,int year){
  bool ret=false;
  bool leap=false;
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


//Class that creates a Task (copy construct)
Task CreateTask(string name,int day,int month,int year,int dead){
  Task newTask;
  newTask.name=name;
  newTask.deadline.day=day;
  newTask.deadline.month=month;
  newTask.deadline.year=year;
  newTask.time=dead;
  newTask.isDone=false;
  return newTask;
}
//function that get the date and show errors
vector <string> getDeadline(string date){
  //split DateString in day, month and year
  char delimiter ='/';
  vector <string> DateVector{};
  stringstream sstream(date);
  string StringToVector;
  //read until delimeter
  while(getline(sstream,StringToVector,delimiter)){
    DateVector.push_back(StringToVector);
  }
  return DateVector;
}

void addTask(Project &toDoList){

  cin.clear();
  string EmptyString="";
  string ListName=AskName(EmptyString);

  if(SearchList(ListName ,toDoList)!=-1){
    string taskName,DateString;
    cout<<"Enter task name: ";
    getline(cin,taskName);
    cout<<"Enter deadline: ";
    getline(cin,DateString);
    vector <string> vec=getDeadline(DateString);
    if(!CheckDate(stoi(vec[0]),stoi(vec[1]),stoi(vec[2]))){
        error(ERR_DATE);
      }else{
        int time=0;
        cout<<"Enter expected time: ";
        cin>>time;
          if(0<time && time<181){
            Task newTask=CreateTask(taskName,stoi(vec[0]),stoi(vec[1]),stoi(vec[2]),time);
            toDoList.lists[SearchList(ListName,toDoList)].tasks.push_back(newTask);
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
  string EmptyString="";
  string ListName=AskName(EmptyString);

  if(SearchList(ListName ,toDoList)!=-1){
    cout<<"Enter task name: ";
    string taskName;
    getline(cin,taskName);
    int taskSize=toDoList.lists[SearchList(ListName,toDoList)].tasks.size();
    if(taskSize==0){
      error(ERR_TASK_NAME);
    }else{
      int SameNameNum=0;
      for(int i=0;i<taskSize;i++){
        if(toDoList.lists[SearchList(ListName,toDoList)].tasks[i].name==taskName){
          SameNameNum++;
        }
      }
      if(SameNameNum==0){
        error(ERR_TASK_NAME);
      }else{
        for(int j=0;j<SameNameNum;j++){
          for(int i=0;i<taskSize;i++){
            if(toDoList.lists[SearchList(ListName,toDoList)].tasks[i].name==taskName){
                  toDoList.lists[SearchList(ListName,toDoList)].tasks.erase(toDoList.lists[SearchList(ListName,toDoList)].tasks.begin()+i);
              }
            }
        }
      }
    }
  }
}


void toggleTask(Project &toDoList){
  cin.clear();
  string EmptyString="";
  string ListName=AskName(EmptyString);
  if(SearchList(ListName,toDoList)!=-1){
      cout<<"Enter task name:";
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
//function that print the tasks at report
void showTasks(const List &list){
int pos=0;
List AuxList=list;
    for(unsigned int i=0; i<=AuxList.tasks.size();i++){

          pos=Oldest(AuxList);
          printTask(AuxList.tasks[pos]);
          AuxList.tasks.erase(AuxList.tasks.begin() + pos);

   }
  //  }
}

//function that print Total Done and Total left
void showTotal(const Project &toDoList){
int left=0;
int leftTime=0;
int doneTime=0;
int done=0;
bool noTask=true;
    for(unsigned i=0;i<toDoList.lists.size();i++){
      for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
        noTask=false;
        if(toDoList.lists[i].tasks[i].isDone==false){
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
  cout<<"Total left: 0 (0 minutes)"<<endl;
  cout<<"Total done: 0 (0 minutes)"<<endl;
}

}
//function that show list.name and call showTasks to print the task of a list
void showLists(const Project &toDoList){
    for(unsigned i=0;i<toDoList.lists.size();i++){
      cout<<toDoList.lists[i].name<<endl;
      if(toDoList.lists[i].tasks.size()>0){
          showTasks(toDoList.lists[i]);
      }
    }

}



void showPriority(const Project toDoList){
Task task;
int pos=0;
bool show=false;
vector<Task> AuxList;

    for(unsigned i=0;i<toDoList.lists.size();i++){
      for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
        AuxList.push_back(toDoList.lists[i].tasks[j]);
      }
      if(toDoList.lists[i].tasks.size()>0){

        for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
          if(!toDoList.lists[i].tasks[j].isDone){
            show=true;
            pos=Oldest(toDoList.lists[i]);
            task=toDoList.lists[i].tasks[pos];
          }
        }
      }
    }
if(show){
  cout<<"Highest priority: "<<task.name<<" ("<<task.deadline.year<<"-"<<task.deadline.month<<"-"<<task.deadline.day<<")"<<endl;
}
}
void report(const Project &toDoList){

  cout<<"Name: "<<toDoList.name<<endl;
  if(toDoList.description.size()!=0){
    cout<<"Description: "<<toDoList.description<<endl;
  }
  if(toDoList.lists.size()!=0){
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
