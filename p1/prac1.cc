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


//function that ask List name until is not empty
//return true if is not empty
string EmptyLoopList(string name){

  do{
    cout<<"Enter list name:"<<endl;
    getline(cin,name);

  }while(name.empty());
  return name;
}

void editProject(Project &toDoList){
  string ProjectName="";
  string ProjectDes="";
  cin.clear();//clean buffer
  do{
    cout<<"Enter project name:"<<endl;
    getline(cin,ProjectName);

    if(ProjectName.empty()){
      error(ERR_EMPTY);
    }
  }while(ProjectName.empty());

  cout<< "Enter project description:"<<endl;
  getline(cin,ProjectDes);
  toDoList.name=ProjectName;
  toDoList.description=ProjectDes;
}


//function that looks if list exist at project
//return true if exist
//return false if is empty or not exist
bool ExistList(string &list_name, Project &toDoList){
  bool ret=false;
  //search at list vector
    for(unsigned int i=0;i<toDoList.lists.size();i++){
      if(toDoList.lists[i].name==list_name){
        ret= true;
      }
    }

  return ret;
}


void addList(Project &toDoList){
  cin.clear();
  string EmptyString="";
  string ListName=EmptyLoopList(EmptyString);

  if(!ExistList(ListName ,toDoList)){
    List newList;
    newList.name=ListName;
    //put list at end of vector Project.lists
    toDoList.lists.push_back(newList);
  }else{
    error(ERR_LIST_NAME);
  }

}
//search at list what pos have the name
//is called only when we know that the list is in Project vector!
//(we have to use it after use ExistList)
unsigned ListPos(string &list_name,Project &toDoList){
unsigned ret=0;
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(toDoList.lists[i].name==list_name){
      ret= i;
    }

}
  return ret;
}


void deleteList(Project &toDoList){
  cin.clear();
  string EmptyString="";
  string ListName=EmptyLoopList(EmptyString);
  if(ExistList(ListName,toDoList)){
    toDoList.lists.erase(toDoList.lists.begin()+ListPos(ListName,toDoList));
  }else{
    error(ERR_LIST_NAME);
  }


}
//function that return true if date is correct
bool CheckDate(int &day,int &month,int &year){
  bool ret=false;

  if(2000<=year && year<=2100 && 0<month && month<12 && 0<day){

      //Months 4,6,9,11 have 30 days
      if(month==4 || month==6 || month == 9 || month ==11){
        if(day<31){
          ret=true;
        }
      }
      else{
        //check if is leap(bisiesto)
        if(month==2 && year%4==0 ){
          if(year%100 && year%400){
              if(day<30){
                ret=true;
              }

          }else{
            if(day<30){
              ret=true;
            }

          }
        }else if(month==2){
          if(day<29){
            ret=true;
          }
        }else{
          if(day<32){
            ret=true;
          }
        }



    }
  }
  return ret;
}
//function that convert date in string format to Date format
//this function show errors too

void addTask(Project &toDoList){

  cin.clear();
  string EmptyString="";
  string ListName=EmptyLoopList(EmptyString);

  if(ExistList(ListName ,toDoList)){

    cout<<"Enter task name:"<<endl;
    string taskName;
    getline(cin,taskName);

    string DateString;
    cout<<"Enter deadline:"<<endl;
    getline(cin,DateString);

    //split DateString in day, month and year
    char delimiter ='/';
    vector <string> DateVector{};
    stringstream sstream(DateString);
    string StringToVector;
    while(getline(sstream,StringToVector,delimiter)){
      DateVector.push_back(StringToVector);

    }
    int day=stoi(DateVector[0]);
    int month=stoi(DateVector[1]);
    int year=stoi(DateVector[2]);
    if(CheckDate(day,month,year)){
      int time=0;
      cout<<"Enter expected time:"<<endl;
      cin>>time;
      if(0<time && time<181){
        Task newTask;
        newTask.name=taskName;
        newTask.deadline.day=day;
        newTask.deadline.month=month;
        newTask.deadline.year=year;
        newTask.isDone=false;
        newTask.time=time;

        toDoList.lists[ListPos(ListName,toDoList)].tasks.push_back(newTask);

      }else{
        error(ERR_TIME);
      }
    }else{
      error(ERR_DATE);
    }


    //for see if date is wrong and throw error, GoodFormatDate return day==-1

  }else{
    error(ERR_LIST_NAME);
  }

}

void deleteTask(Project &toDoList){
  cin.clear();
  string EmptyString="";
  string ListName=EmptyLoopList(EmptyString);

  if(ExistList(ListName ,toDoList)){
    cout<<"Enter task name:"<<endl;
    string taskName;
    getline(cin,taskName);
    int listpos=ListPos(ListName,toDoList);
    int taskSize=toDoList.lists[listpos].tasks.size();
    if(toDoList.lists[listpos].tasks.size()==0){
      error(ERR_TASK_NAME);
    }else{
      int SameNameNum=0;
      for(int i=0;i<taskSize;i++){
        if(toDoList.lists[listpos].tasks[i].name==taskName){
          SameNameNum++;
        }
      }
      if(SameNameNum==0){
        error(ERR_TASK_NAME);
      }else{
        for(int j=0;j<SameNameNum;j++){
          for(int i=0;i<taskSize;i++){
            if(toDoList.lists[listpos].tasks[i].name==taskName){

                  toDoList.lists[listpos].tasks.erase(toDoList.lists[listpos].tasks.begin()+i);
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
  string ListName=EmptyLoopList(EmptyString);
  if(ExistList(ListName,toDoList)){
      cout<<"Enter task name:"<<endl;
      string TaskName;
      getline(cin,TaskName);
      int taskSize=toDoList.lists[ListPos(ListName,toDoList)].tasks.size();
      int listpos=ListPos(ListName,toDoList);
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

void report(const Project &toDoList){
cout<<"Name: "<<toDoList.name<<endl;
if(toDoList.description.size()!=0){
  cout<<"Description: "<<toDoList.description<<endl;
}
if(toDoList.lists.size()>0){
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    cout<<toDoList.lists[i].name<<endl;
    if(toDoList.lists[i].tasks.size()!=0){

      for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
        Task task=toDoList.lists[i].tasks[j];
        if(task.isDone) {
          cout<<"[ ] ("<<task.time<<") "
          <<task.deadline.day<<"-"<<task.deadline.month<<"-"<<task.deadline.year<<
          " : "<<task.name<<endl;
        }
      }
      for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
        Task task=toDoList.lists[i].tasks[j];
        if(!task.isDone) {
          cout<<"[X] ("<<task.time<<") "
          <<task.deadline.day<<"-"<<task.deadline.month<<"-"<<task.deadline.year<<
          " : "<<task.name<<endl;
        }
      }

    }
  }
}


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
