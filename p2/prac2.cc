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
      break;
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
  CONFIRM,
  SAVE
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
    case SAVE:
      cout<<"Save all projects [Y/N]?: ";
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
  toDoList.description=newDescription;


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
//function that ask for id and return the project position if project exist
int SearchProjectID(ToDo &toDo){
  int id;
  show(PROJ_ID);
  cin>>id;

  for(unsigned i=0;i<toDo.projects.size();i++){
    if(toDo.projects[i].id==id){
      return i;
    }
  }
  return -1;//return -1 when project no exist
}


//menu prac1
void menu(Project &toDoList){
  char option;

  do{
    showProjectMenu();
    cin>>option;
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
      case 'b': break;
      default: error(ERR_OPTION);
    }
  }while(option!='b');
}
//case 1 mainMenu
void menuProject(ToDo &toDo){

  int projectPos=SearchProjectID(toDo);

  if(projectPos!=-1){//if project exists
    menu(toDo.projects[projectPos]);
  }else{
    error(ERR_ID);
  }
}
//function that return false if project have ProjectName
bool SearchProjectName(string &projectName,ToDo &toDo){

  for(unsigned int i=0;i<toDo.projects.size();i++){
    if(toDo.projects[i].name==projectName){
      return false;
    }
  }
  return true;
}
//case 2 mainMenu
bool addProject(ToDo &toDo){
  Project newProject;
  cin.clear();//clean buffer
  string newName=AskName("",true);
  string newDescription="";
  if(SearchProjectName(newName,toDo)){
    show(ENTER_DESC);
    getline(cin,newDescription);// new Project Description
    newProject.name=newName;
    newProject.description=newDescription;
    newProject.id=toDo.nextId;
    toDo.projects.push_back(newProject);

    return true;
  }else{
    error(ERR_PROJECT_NAME);
    return false;
  }

}
//case 3 mainMenu
void deleteProject(ToDo &toDo){
  int projectPos=SearchProjectID(toDo);
  if(projectPos!=-1){//si existe proyecto
    //borrar proyecto del vector projects
      toDo.projects.erase(toDo.projects.begin()+projectPos);
  }else{
    error(ERR_ID);
  }
}
//function that ask for project name

string getFileName(){
  string fileName;
  show(FILE_NAME);
  //  cin.ignore();
  getline(cin,fileName);
  return fileName;
}
//function that delete the first character of string
string cutString(string &fullString){
if(fullString.length()>0){
  char charString [fullString.length()+1];
    for(unsigned i=0;i<fullString.length();i++){
      if(i==fullString.length()){
        charString[i]='\0';
      }else{
        charString[i]=fullString[i+1];
      }

    }
    fullString=charString;
}

  return fullString;
}
//funtion that return the first character of string
char PrimerCaracter(string &s){
      return s[0];
}
//Function that create a Task from file:
//task.deadline.day=-1 if ERR_DATE
//task.dead+.day=-2 if ERR_TIME
Task CreateTaskFile(string &line){
      char delimiter ='|';
      vector <string> taskDivided{};
      Task newTask;
      stringstream sstream(line);
      string StringToVector; //the string that we push to vector
      //read until delimeter
      while(getline(sstream,StringToVector,delimiter)){
        taskDivided.push_back(StringToVector); //save day,year and month
      }
      vector <string> deadline=getDeadline(taskDivided[1]);//function that convert the deadline
      if(!CheckDate(stoi(deadline[0]),stoi(deadline[1]),stoi(deadline[2]))){
        error(ERR_DATE);
        newTask.deadline.day=-1;

      }else if(0>stoi(taskDivided[3]) || stoi(taskDivided[3])>181){
        error(ERR_TIME);
        newTask.deadline.day=-2;
      }else{
        newTask=CreateTask(taskDivided[0],stoi(deadline[0]),stoi(deadline[1]),stoi(deadline[2]),stoi(taskDivided[3]));
        if(taskDivided[2]=="F"){
          newTask.isDone=false;
        }else{
          newTask.isDone=true;
        }
      }
      return newTask;
}
//case 4 of mainMenu
void import(ToDo &toDo,string &FileName){
  bool endProject=false;//boolean that control the end of project
  string Description="";
  string ProjectName,ListName,taskname,isDone,time,date,line;
  Project newProject;
  List newList;

  ifstream file(FileName);//open file in read mode
  if(file.is_open()){
    while(getline(file,line)){//read line in loop
      endProject=false;
      //start of project
      if(line=="<"){

        getline(file,line);
        if(PrimerCaracter(line)=='#'){

          ProjectName=cutString(line);//read project name
          if(SearchProjectName(ProjectName,toDo)){

            getline(file,line);
            if(PrimerCaracter(line)=='*'){
              Description=cutString(line);//read description if exist
              getline(file,line);
            }
            newProject.name=ProjectName;
            newProject.description=Description;
            while(!endProject){
                if(PrimerCaracter(line)=='@'){//read lists
                  ListName=cutString(line);
                  newList.name=ListName;
                  newList.tasks.clear();
                  while(getline(file,line)){//read task
                    if(PrimerCaracter(line)=='@'){//if read another list we exit loop
                      newProject.lists.push_back(newList);
                      break;
                    }else if(PrimerCaracter(line)=='>'){//if read endOfproject exit loop and endProject= true
                      endProject=true;
                      newProject.lists.push_back(newList);
                      break;
                    }else{
                      Task newTask=CreateTaskFile(line);//create a Task with CreateTaskFile
                      if(newTask.deadline.day>0){//if we don't have errors we save it
                        newList.tasks.push_back(newTask);
                     }
                   }
                }
              }else{//finish lists
                endProject=true;
                break;
              }
          }
          newProject.id=toDo.nextId;
          toDo.nextId++;
          toDo.projects.push_back(newProject);
          newProject.lists.clear();
          Description="";

        }else{
          error(ERR_PROJECT_NAME);
        }
      }
    }
  }
  file.close();
  }else{
    file.close();
    error(ERR_FILE);
  }
}
//fuction that looks if user enter y/Y or n/N
bool checkRespuesta(int option){
  string respuesta;

  do{
    if(option==1){
        show(SAVE);
    }else{
      show(CONFIRM);
    }
    getline(cin,respuesta);
    if(respuesta=="Y" || respuesta=="y"){
      return true;
    }else if(respuesta=="N" || respuesta == "n"){
      break;
    }
  } while(respuesta!="y" && respuesta!="Y" && respuesta!= "n" && respuesta != "N");


  return false;
}
//fucntion that write one project or all projects
void WriteProject(ToDo &toDo,string &fileName,int &pos){
  Project project;

    ofstream file(fileName);//open file in write mode
    if(file.is_open()){

        file.clear();
        //export all projects
        if(pos==-1){

          for(unsigned int i=0;i<toDo.projects.size();i++){
            project=toDo.projects[i];
            file<<"<"<<endl;
            file<<"#"<<project.name<<endl;
            if(project.description!=""){
              file<<"*"<<project.description<<endl;
            }
            for(unsigned j=0;j<project.lists.size();j++){
                file<<"@"<<project.lists[j].name<<endl;
                for(unsigned z=0;z<project.lists[j].tasks.size();z++){
                  file<<project.lists[j].tasks[z].name<<"|";
                  file<<project.lists[j].tasks[z].deadline.day<<"/";
                  file<<project.lists[j].tasks[z].deadline.month<<"/";
                  file<<project.lists[j].tasks[z].deadline.year<<"|";
                  if(project.lists[j].tasks[z].isDone){
                    file<<"T|"<<project.lists[j].tasks[z].time<<endl;
                  }else{
                    file<<"F|"<<project.lists[j].tasks[z].time<<endl;
                  }
                }
            }

            file<<">"<<endl;
          }
        //export one project
        }else{

          file<<"<"<<endl;
          project=toDo.projects[pos];
          file<<"#"<<project.name<<endl;
          if(project.description!=""){
            file<<"*"<<project.description<<endl;
          }
          for(unsigned i=0;i<project.lists.size();i++){
              file<<"@"<<project.lists[i].name<<endl;
              for(unsigned j=0;j<project.lists[i].tasks.size();j++){
                file<<project.lists[i].tasks[j].name<<"|";
                file<<project.lists[i].tasks[j].deadline.day<<"/";
                file<<project.lists[i].tasks[j].deadline.month<<"/";
                file<<project.lists[i].tasks[j].deadline.year<<"|";
                if(project.lists[i].tasks[j].isDone){
                  file<<"T|"<<project.lists[i].tasks[j].time<<endl;
                }else{
                  file<<"F|"<<project.lists[i].tasks[j].time<<endl;
                }
              }
          }

          file<<">"<<endl;
        }


        file.close();

    }else{
      file.close();
      error(ERR_FILE);
    }
}
//case 5 mainMenu
void exportFile(ToDo &toDo){
  int option=1;
  int pos=-1;
  bool respuesta=checkRespuesta(option);
  if(respuesta==true){//ha contestado Y/y
        cin.clear();
        string fileName=getFileName();
        WriteProject(toDo,fileName,pos);
        toDo.projects.clear();
    //se guarda todo
  }else{//ha contestado N/n
    //se guarda un proyecto
    pos=SearchProjectID(toDo);
    if(pos!=-1){
      string fileName=getFileName();
      WriteProject(toDo,fileName,pos);
      toDo.projects.erase(toDo.projects.begin()+pos);
    }
  }
}
//case 6 mainMenu
void load(ToDo &toDo,string &FileName, bool &respuesta){
    BinToDo binToDo;
    BinProject binProject;
    BinTask binTask;
    BinList binList;
    Project newProject;
    List newList;
    Task newTask;
    ifstream file(FileName, ios::in | ios::binary);
    if(file.is_open()){

      if(respuesta){// Y/y
        toDo.projects.clear();
        toDo.nextId=1;
        //lectura registro BinToDo
        file.read( (char *) &binToDo , sizeof(BinToDo));
        toDo.name=binToDo.name;
        for(unsigned i=0;i<binToDo.numProjects;i++){


          file.read((char *) &binProject ,sizeof(BinProject));
          newProject.name=binProject.name;
          newProject.description=binProject.description;
          newProject.lists.clear();
          for(unsigned int j=0;j<binProject.numLists;j++){
              file.read((char *) &binList,sizeof(BinList));
                newList.name=binList.name;
                newList.tasks.clear();
              for(unsigned z=0;z<binList.numTasks;z++){
                file.read((char *) &binTask,sizeof(BinTask));
                  newTask.name=binTask.name;
                  newTask.deadline=binTask.deadline;
                  newTask.isDone=binTask.isDone;
                  newTask.time=binTask.time;
                  newList.tasks.push_back(newTask);
              }
              newProject.lists.push_back(newList);
          }
          newProject.id=toDo.nextId;
          toDo.projects.push_back(newProject);
          toDo.nextId++;
        }

      }
      file.close();
    }else{
      file.close();
      error(ERR_FILE);
    }
}
//case 7 mainMenu
void save(ToDo &toDo){
  BinToDo toDoBin;
  BinProject projectBin;
  BinList ListBin;
  BinTask TaskBin;
  string fileName=getFileName();
  ofstream file(fileName, ios::out | ios::binary);
  if(file.is_open()){
    file.clear();
    //save toDoBin
    strncpy(toDoBin.name,toDo.name.c_str(),KMAXNAME);
    toDoBin.name[KMAXNAME-1]='\0';
    toDoBin.numProjects=toDo.projects.size();
    file.write((const char*) &toDoBin , sizeof(toDoBin));
    //save BinProject
    for(unsigned i=0;i<toDo.projects.size();i++){

      strncpy(projectBin.name,toDo.projects[i].name.c_str(),KMAXNAME);
      projectBin.name[KMAXNAME-1]='\0';

      strncpy(projectBin.description,toDo.projects[i].description.c_str(),KMAXDESC);
      projectBin.description[KMAXDESC-1]='\0';
      projectBin.numLists=toDo.projects[i].lists.size();

      file.write((const char*) &projectBin , sizeof(projectBin));
      //save Lists
      for(unsigned j=0;j<toDo.projects[i].lists.size();j++){
          strncpy(ListBin.name,toDo.projects[i].lists[j].name.c_str(),KMAXNAME);
          ListBin.name[KMAXNAME-1]='\0';

          ListBin.numTasks=toDo.projects[i].lists[j].tasks.size();
          file.write((const char*) &ListBin , sizeof(ListBin));
          //save Tasks
          for(unsigned z=0;z<toDo.projects[i].lists[j].tasks.size();z++){
            strncpy(TaskBin.name,toDo.projects[i].lists[j].tasks[z].name.c_str(),KMAXNAME);

            TaskBin.name[KMAXNAME-1]='\0';
            TaskBin.deadline=toDo.projects[i].lists[j].tasks[z].deadline;
            TaskBin.isDone=toDo.projects[i].lists[j].tasks[z].isDone;
            TaskBin.time=toDo.projects[i].lists[j].tasks[z].time;
            file.write((const char*) &TaskBin , sizeof(TaskBin));
          }

      }

     }
    file.close();
  }else{
    file.close();
    error(ERR_FILE);
  }
}

//case 8 mainMenu
void summary(ToDo &toDo){
//resumen de los proyectos existentes
int TotalTask=0;
int doneTasks=0;

  for(unsigned i=0;i<toDo.projects.size();i++){

    cout<<"("<<toDo.projects[i].id<<") "<<toDo.projects[i].name<<" [";

    for(unsigned j=0;j<toDo.projects[i].lists.size();j++){
      TotalTask=0;
      doneTasks=0;
      TotalTask=TotalTask+toDo.projects[i].lists[j].tasks.size();
      for(unsigned z=0;z<toDo.projects[i].lists[j].tasks.size();z++){
        if(toDo.projects[i].lists[j].tasks[z].isDone){
          doneTasks++;
        }
      }
    }


    cout<<doneTasks<<"/"<<TotalTask<<"]"<<endl;
  }



}
int main(int argc,char *argv[]){
  bool respuesta=true;
  int option2=2;
  ToDo toDo;
  string file_name;
  string Importfile_name,Loadfile_name;
  toDo.name="My ToDo list";
  toDo.nextId=1;
  //variables que controlan si un argumento ha salido más de una vez
  int Numimport=0;
  int  Numload=0;
  //parsing arguments
  for(int i=1;i<argc;i++){
    string arg=argv[i];

    if(arg=="-i"){

      //importar proyectos -i fihero
      i++;
      if(i>=argc){
        error(ERR_ARGS);
        exit(EXIT_FAILURE);
      }else{

        Numimport++;
        Importfile_name= argv[i];
      }

    }else if(arg=="-l"){
      i++;
      if(i>=argc){
        error(ERR_ARGS);
        exit(EXIT_FAILURE);
      }else{
        Numload++;
        Loadfile_name= argv[i];
      }

    }else{

      error(ERR_ARGS);
      exit(EXIT_FAILURE);
    }
  }
  if(Numload <= 1 && Numimport <= 1){
    if(Numload==1 && Numimport==1 ){
      load(toDo,Loadfile_name,respuesta);
      import(toDo,Importfile_name);
    }else if(Numload==1 && Numimport==0){
      load(toDo,Loadfile_name,respuesta);
    }else if(Numimport==1 && Numload==0){
      import(toDo,Importfile_name);
    }
  }else{

    error(ERR_ARGS);
    exit(EXIT_FAILURE);
  }
  char option;
  cin.clear();
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
      case '4': file_name=getFileName();
                import(toDo,file_name);
                break;
      case '5': exportFile(toDo);
                break;

      case '6': file_name=getFileName();
                respuesta=checkRespuesta(option2);
                load(toDo,file_name,respuesta);
                break;
      case '7': save(toDo);
                break;
      case '8': summary(toDo);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');


  return 0;
}
