//DNI 74395666G Pérez Giménez, Miguel
using namespace std;
#include <cstdlib>
#include <iostream>
#include <vector>
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
    List list;
    list.name=ListName;
    //put list at end of vector Project.lists
    toDoList.lists.push_back(list);
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
  }


}




void addTask(Project &toDoList){


}

void deleteTask(Project &toDoList){
}

void toggleTask(Project &toDoList){
}

void report(const Project &toDoList){
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
