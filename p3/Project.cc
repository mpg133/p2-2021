#include <iostream>
#include <string.h>
#include<sstream>
#include <vector>
#include <stdio.h>
#include "Project.h"
#include "List.h"
#include "Util.h"
using namespace std;

Project::Project(string name2,string description2=""){

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
        if(lists.getName()==nameList){
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
        error(ERR_EMPTY);
        return false;
    }
}
void Project::setDescription(string description2){
    description=description2;
}
void Project::edit(string name2="",string description2=""){
    string usuName;
    string usuDesc;
    bool repetir=true;
    if(name2.empty()){
        do{
            cout<<"Enter project name: ";
            getline(cin,usuName);
            if(setName(usuName)){
                repetir=false;
            }
            
        }while(repetir);
        
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
void Project::addList(string nameList=""){
 string usuName;
 bool repetir=true;
    if(nameList.empty()){
         do{
            cout<<"Enter list name: ";
            getline(cin,usuName);
            try{
                List list(usuName);
            }catch(ERR_EMPTY){
                Util::error(ERR_EMPTY);
            }

        }while(usuName.empty());
    }else{
        List list(nameList);
    }

    if(getPosList(usuName)!=-1){
        list.tasks.clear();
        lists.push_back(list);
    }else{
        Util::error(ERR_LIST_NAME);
    }

}
void Project::addTaskToList(string name=""){


    
}
