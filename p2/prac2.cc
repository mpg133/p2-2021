//DNI 74395666G Pérez Giménez, Miguel

#include <cstdlib>
#include <iostream>
#include<sstream>
#include <vector>
#include <stdio.h>
#include<string.h>
#include <fstream>

using namespace std;
//global variables for char[] name of BIN structs
const int KMAXNAME=20;
const int KMAXDESC=40;

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
//news structs

struct ToDo{
int nextId;
string name;
vector<Project> projects;
};

struct BinTask{
char name[KMAXNAME];
Date deadline;
bool isDone;
int time;
};

struct BinList{
char name[KMAXNAME];
unsigned numTasks;
};

struct BinProject{
char name[KMAXNAME];
char description[KMAXDESC];
unsigned numLists;
};
struct BinToDo{
char name[KMAXNAME];
unsigned numProjects;
};
enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
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
      case ERR_ID:
        cout << "ERROR: wrong project id" << endl;
        break;
      case ERR_PROJECT_NAME:
        cout << "ERROR: wrong project name" << endl;
        break;
      case ERR_FILE:
        cout << "ERROR: cannot open file" << endl;
        break;
      case ERR_ARGS:
        cout << "ERROR: wrong arguments" << endl;
  }
}
enum Cad{
  PROJ_NAME,
  LIST_NAME,
  TASK_NAME,
  ENTER_DESC,
  ENTER_DEADLINE,
  ENTER_TIME,
  TOTAL_0,
  PROJ_ID,
  FILE_NAME,
  CONFIRM
};
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
      cout<<"Enter deadline: ";
      break;
    case ENTER_TIME:
      cout<<"Enter expected time: ";
      break;
    case PROJ_ID:
      cout<<"Enter project id: ";
      break;
    case TOTAL_0:
      cout<<"Total left: 0 (0 minutes)"<<endl;
      cout<<"Total done: 0 (0 minutes)"<<endl;
      break;
    case FILE_NAME:
      cout<<"Enter filename: ";
      break;
    case CONFIRM:
      cout<<"Confirm [Y/N]?: ";
      break;
  }




}
void showMainMenu(){
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary"<<endl
       << "q- Quit" << endl
       << "Option: ";


}
void showProjectMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}


//BinTask btask;
//file.read(char* &btask,sizeof(BinTask);



//BinTask btask;
//file.write(const &btask,sizeof(BinTask));
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
  if(newDescription!=""){
      toDoList.description=newDescription;
  }

}

//search at list what pos have the name
//if name don't exist-> return -1;
//else return pos of name;
int SearchList(string &listName,Project &toDoList){
int ret=-1;//variable that return the function
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(toDoList.lists[i].name==listName){
      ret= i;
    }
}
  return ret;
}

void addList(Project &toDoList){
  cin.clear();
  string listName=AskName("",false);//name of the list

  if(SearchList(listName ,toDoList)==-1){ //if the name don't exist
    List newList; //new List at Project
    newList.name=listName;
    newList.tasks.clear();//With that always vector tasks is empty
    toDoList.lists.push_back(newList);//put newList at the end of vector Project.lists
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteList(Project &toDoList){
  cin.clear();
  string listName=AskName("",false);//name of the list
  if(SearchList(listName,toDoList)!=-1){//if exists a list with this name
    toDoList.lists.erase(toDoList.lists.begin()+SearchList(listName,toDoList));
  }else{
    error(ERR_LIST_NAME);
  }
}
//function that return true if date is correct
bool CheckDate(int day,int month,int year){
  bool ret=false;//variable that return if date is correct or not
  bool isLeap=false;//variable to look if year is leap

  //check if is leap(bisiesto)
  if(year%4==0){
    if(year%100==0 && !(year%400==0)){isLeap=false;}
    else{isLeap=true;}
  }

  //check the date
  if(0<month && month<13 && 0<day && day<32 && year>=2000 && year<=2100){
      //Months 4,6,9,11 have 30 days
      if((month==4 || month==6 || month == 9 || month ==11) && day<=30){
          ret=true;
      }
      else{
        if(month==2 && isLeap && day<=29) {ret=true;}
        else if(month==2 && !isLeap && day<=28) {ret=true;}
        else if(month!=2){
            if(!(month==4 || month==6 || month == 9 || month ==11)  && day<=31){
              ret=true;
            }
        }
      }
  }
  return ret;
}

//Class that creates a Task with (!isDone) /// (copy constructor)
Task CreateTask(string name,int day,int month,int year,int time){
  Task newTask;
  newTask.name=name;
  newTask.deadline.day=day;
  newTask.deadline.month=month;
  newTask.deadline.year=year;
  newTask.time=time;
  newTask.isDone=false;
  return newTask;
}
//function that get string and return a vector with the date
//split String in day, month and year
vector <string> getDeadline(string date){

  char delimiter ='/';
  vector <string> dateVector{};//vector that we return
  stringstream sstream(date);
  string StringToVector; //the string that we push to vector
  //read until delimeter
  while(getline(sstream,StringToVector,delimiter)){
    dateVector.push_back(StringToVector); //save day,year and month
  }
  return dateVector;
}

void addTask(Project &toDoList){

  cin.clear();
  string listName=AskName("",false);

  if(SearchList(listName ,toDoList)!=-1){ //if the list exist...
    string taskName,deadline;

    show(TASK_NAME);
    getline(cin,taskName);
    show(ENTER_DEADLINE);
    getline(cin,deadline);
    vector <string> dateVector=getDeadline(deadline);//function that convert the deadline
    if(CheckDate(stoi(dateVector[0]),stoi(dateVector[1]),stoi(dateVector[2]))){//si la fecha es correcta
      int time=0;
      show(ENTER_TIME);
      cin>>time;
        if(0<time && time<181){
          Task task=CreateTask(taskName,stoi(dateVector[0]),stoi(dateVector[1]),stoi(dateVector[2]),time);
          toDoList.lists[SearchList(listName,toDoList)].tasks.push_back(task);
        }else{
          error(ERR_TIME);
        }
    }else{
      error(ERR_DATE);
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteTask(Project &toDoList){
  cin.clear();
  string listName=AskName("",false);
  int SameName=0; //the number of tasks with the same name
  int listPos=SearchList(listName ,toDoList);
  string taskName;
  if(listPos!=-1){ //if list exists...
    show(TASK_NAME);
    getline(cin,taskName);
    unsigned int size=toDoList.lists[listPos].tasks.size();//the size of vector tasks at list

      for(unsigned int i=0;i<size;i++){
        if(toDoList.lists[listPos].tasks[i].name==taskName){
          SameName++;
        }
      }
      if(SameName!=0){
        for(int j=0;j<SameName;j++){ //borra la tareas con el mismo nombre
          for(unsigned int i=0;i<toDoList.lists[listPos].tasks.size();i++){
            if(toDoList.lists[listPos].tasks[i].name==taskName){
                  //delete the tasks at vector lists
                  toDoList.lists[listPos].tasks.erase(toDoList.lists[listPos].tasks.begin()+i);
                  i--;
              }
            }
        }

      }else{// no task with the name that user give
        error(ERR_TASK_NAME);
      }

  }else{
    error(ERR_LIST_NAME);
  }

}

void toggleTask(Project &toDoList){
  cin.clear();
  int numberName=-1;
  string listName=AskName("",false);
  int listPos=SearchList(listName,toDoList);
  if(listPos!=-1){//if list exists...
    show(TASK_NAME);
    string taskName;
    getline(cin,taskName);
    int taskSize=toDoList.lists[listPos].tasks.size();

    if(toDoList.lists[listPos].tasks.size()==0){
      error(ERR_TASK_NAME);
    }else{

      for(int i=0;i<taskSize;i++){
        if(toDoList.lists[listPos].tasks[i].name==taskName){
          numberName++;
          if(toDoList.lists[listPos].tasks[i].isDone){//es true -> false;
            toDoList.lists[listPos].tasks[i].isDone=false;
          }else{
            toDoList.lists[listPos].tasks[i].isDone=true;
          }
        }
      }
    }
  }else{
    error(ERR_LIST_NAME);
    numberName=-2;
  }
  if(numberName==-1){
    error(ERR_TASK_NAME);
  }
}

//fuction that print one task
void printTask(Task &task){
  cout<<"[";
  if(!task.isDone){
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
void showTotal(Project &toDoList){
int left=0;
int leftTime=0;
int doneTime=0;
int done=0;
bool noTask=true;
if(toDoList.lists.size()>0){
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
}
  if(noTask==false){
    cout<<"Total left: "<<left<<" ("<<leftTime<<" minutes)"<<endl;
    cout<<"Total done: "<<done<<" ("<<doneTime<<" minutes)"<<endl;
  }else{
    show(TOTAL_0);
  }

}
//function that show list.name and call showTasks to print the task of a list
void showLists(Project &toDoList){
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    cout<<toDoList.lists[i].name<<endl;
    if(toDoList.lists[i].tasks.size()>0){
      //show Tasks
      for(unsigned int j=0; j<toDoList.lists[i].tasks.size();j++){
        if(!toDoList.lists[i].tasks[j].isDone){
          printTask(toDoList.lists[i].tasks[j]);
        }
      }
      for(unsigned int j=0; j<toDoList.lists[i].tasks.size();j++){
        if(toDoList.lists[i].tasks[j].isDone){
          printTask(toDoList.lists[i].tasks[j]);
        }
      }
    }
  }
}

//function that return the position of oldest task in a list
int Oldest(List &list){

int oldPos=0;// the position of the oldest

  for(unsigned int i=0; i<list.tasks.size();i++){

    if(!list.tasks[i].isDone){
      if(list.tasks[i].deadline.year<list.tasks[oldPos].deadline.year){ oldPos=i; }

      else if(  list.tasks[i].deadline.year==list.tasks[oldPos].deadline.year
            &&  list.tasks[i].deadline.month<list.tasks[oldPos].deadline.month){ oldPos=i; }

      else if(  list.tasks[i].deadline.year==list.tasks[oldPos].deadline.year
                && list.tasks[i].deadline.month==list.tasks[oldPos].deadline.month
                && list.tasks[i].deadline.day<list.tasks[oldPos].deadline.day){ oldPos=i; }
    }

  }

return oldPos;
}

void showPriority(Project &toDoList){
  Task prioTask;
  int oldPos=0;
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
    oldPos=Oldest(AuxList);
    prioTask=AuxList.tasks[oldPos];
    cout<<"Highest priority: "<<prioTask.name<<" ("<<prioTask.deadline.year<<"-"<<prioTask.deadline.month<<"-"<<prioTask.deadline.day<<")"<<endl;
  }

}
void report(Project &toDoList){

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
// ----------------------------------------------------------------------------------------------------------------------
// -----------------------------------FUNCIONES PRACTICA 2---------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------
//function that ask for id and return the project if project exist
int SearchProjectID(ToDo &toDo){
  int id;
  show(PROJ_ID);
  cin>>id;

  for(unsigned i=0;i<toDo.projects.size();i++){
    if(toDo.projects[i].id==id){
      return i;
    }
  }
  return -1;
}



void menu(Project &toDoList){
  char optionProject;

  do{
    showProjectMenu();
    cin>>optionProject;
    cin.get();
    switch(optionProject){
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
      case 'b': break;
      default: error(ERR_OPTION);
    }
  }while(optionProject!='b');
}
void menuProject(ToDo &toDo){

  int pos=SearchProjectID(toDo);

  if(pos!=-1){//si existe proyecto
    menu(toDo.projects[pos]);
  }else{
    error(ERR_ID);
  }


}
//function that return false if project has that name
bool SearchProjectName(string &ProjectName,ToDo &toDo){

  for(unsigned int i=0;i<toDo.projects.size();i++){
    if(toDo.projects[i].name==ProjectName){
      return false;
    }
  }
  return true;
}
bool addProject(ToDo &toDo){
  Project ret;
  cin.clear();//clean buffer
  string newName=AskName("",true);
  string newDescription="";
  if(SearchProjectName(newName,toDo)){
    show(ENTER_DESC);
    getline(cin,newDescription);// new Project Description
    ret.name=newName;
    ret.description=newDescription;
    ret.id=toDo.nextId;
    toDo.projects.push_back(ret);

    return true;
  }else{
    error(ERR_PROJECT_NAME);
    return false;
  }

}

void deleteProject(ToDo &toDo){
  int pos=SearchProjectID(toDo);
  if(pos!=-1){//si existe proyecto
    //borrar proyecto del vector projects
      toDo.projects.erase(toDo.projects.begin()+pos);
  }else{
    error(ERR_ID);
  }
}
//function that ask for project name

string getFileName(){
  string FileName;
  cin.clear();
  show(FILE_NAME);
  getline(cin,FileName);

  return FileName;
}
//funcion que quita el primer caracter del string
string cutString(string &s){

char charString [s.length()+1];
  for(unsigned i=0;i<s.length()+1;i++){
    if((i+1)==s.length()){
      charString[i]='\0';
    }else{
      charString[i]=s[i+1];
    }

  }
  s=charString;
  return s;
}
//funcion que devuelve el primer caracter del string
char PrimerCaracter(string &s){
      return s[0];
}
//function that return 1 if date and time are correct
//return 0 if date is wrong and 2 if time is wrong
int canCreateTask(string &line){
      char delimiter ='|';
      vector <string> taskDivided{};

      stringstream sstream(line);
      string StringToVector; //the string that we push to vector
      //read until delimeter
      while(getline(sstream,StringToVector,delimiter)){
        taskDivided.push_back(StringToVector); //save day,year and month
      }
      vector <string> deadline=getDeadline(taskDivided[1]);//function that convert the deadline
      if(!CheckDate(stoi(deadline[0]),stoi(deadline[1]),stoi(deadline[2]))){
        return 0;
      }else if(0>stoi(taskDivided[3]) || stoi(taskDivided[3])>181){
        return 2;
      }else{
        return 1;
      }
}

//function that creates a task with a string
void createTaskFile(string &taskString,ToDo &toDo ){



}
//create a project
void createProject(Project &project,ToDo &toDo){

}
void import(ToDo &toDo){
  bool errorName=false;
  bool endProject=false;
  string ProjectName,Description,ListName,taskname,isDone,time,date,line;
  string FileName=getFileName();
  Project project;
  ifstream file(FileName);//lectura
  if(file.is_open()){
    while(getline(file,line)){//leemos linea a linea
      errorName=false;
      endProject=false;
      //inicio proyecto
      if(line=="<"){

        getline(file,line);
        if(PrimerCaracter(line)=='#'){
          ProjectName=cutString(line);
          if(!SearchProjectName(ProjectName,toDo)){
            errorName=true;
          }
        }
        getline(file,line);
        if(!errorName && PrimerCaracter(line)=='*'){
          Description=cutString(line);
          getline(file,line);
        }
        if(!errorName){
          project.name=ProjectName;
          project.description=Description;

          createProject(project,toDo);
        }
        if(!errorName && PrimerCaracter(line)=='@'){
          ListName=cutString(line);
          while(!endProject){
            while(getline(file,line)){//leemos tareas
              if(PrimerCaracter(line)=='@'){
                break;
              }else if(PrimerCaracter(line)=='>'){
                endProject=true;
                break;
              }else{
                if(canCreateTask(line)==1){
                 createTaskFile(line);
                }else if(canCreateTask(line)==0){
                  error(ERR_DATE);
                }else if(canCreateTask(line)==2){
                  error(ERR_TIME);
                }

              }
            }
          }

        }
        if(errorName){
          error(ERR_PROJECT_NAME);
        }
      }

      }

    file.close();
  }else{
    file.close();
    error(ERR_FILE);
  }



}
/*
do{
  show(CONFIRM);
  cin>>confirm;
  cin.get();
  if(confirm=='Y' || confirm == 'y'){
    return 2;
  }else if(confirm=='N' || confirm=='n'){
    return 3;
  }
}while (!exit);

*/
/*iexport(){}
load(){}
save(){}
summary(){}*/
int main(int argc,char *argv[]){
  //parsing arguments
  //for(int i=1;i<argc;i++){
    //string arg=argv[i];

  ToDo toDo;
  toDo.name="My ToDo list";
  toDo.nextId=1;

  char option;

  do{
    showMainMenu();
    cin>>option;
    cin.get();
    switch(option){
      case '1': menuProject(toDo);
                break;
      case '2':
                if(addProject(toDo)){

                  toDo.nextId++;
                }

                break;
      case '3': deleteProject(toDo);
                break;
      case '4': import(toDo);
                break;
    /*  case '5': export();
                break;
      case '6': load();
                break;
      case '7': save();
                break;
      case '8': summary();
                break;*/
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');


  return 0;
}
