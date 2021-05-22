#include <iostream>
#include <string.h>
#include<sstream>
#include <vector>
#include <stdio.h>
#include "Task.h"
#include "Util.h"
using namespace std;
//--------------------Funciones auxiliares-----------------------------
//function that get string and return a vector with the date
//split String in day, month and year
vector <string> Task::getDeadline(string date){

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

//function that return true if date is correct
bool Task::CheckDate(int day,int month,int year){
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


//-------------------------Funciones principales------------------------
Task::Task(string name2){
    name=name2;
    time=1;
    deadline.day=1;
    deadline.month=1; 
    deadline.year=2000;
    isDone=false;
}
string Task::getName() const{
    return name;
}
Date Task::getDeadline() const{
    return deadline;
}
bool Task::getIsDone() const{
    return isDone;
}
int Task::getTime() const{
    return time;
}
void Task::setName(string name2){
    name=name2;
}
bool Task::setDeadline(string deadline2){
    //function that convert the deadline
     vector <string> dateVector=getDeadline(deadline2);
     //si la fecha es correcta
    if(CheckDate(stoi(dateVector[0]),stoi(dateVector[1]),stoi(dateVector[2]))){
        deadline.day=stoi(dateVector[0]);
        deadline.month=stoi(dateVector[1]);
        deadline.year=stoi(dateVector[2]);
        return true;
    }else{
        Util::error(ERR_DATE);
        return false;
    }

}
bool Task::setTime(int time2){
     if(0<time2 && time2<181){
         time=time2;
         return true;
     }else{
         //error
         Util::error(ERR_TIME);
         return false;
     }
}
void Task::toggle(){
    if(isDone){
        isDone=false;
    }else{
        isDone=true;
    }
}
ostream& operator << (ostream &os,const Task &task){

  os<<"[";
 if(task.isDone){
    os<<"X] (";
  }else{
    os<<" ] (";
  }
  os<<task.getTime()<<") "
      <<task.getDeadline().year<<"-"<<task.getDeadline().month<<"-"<<task.getDeadline().day
      <<" : "<<task.getName()<<endl;

return os;
}