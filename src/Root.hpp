#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Field.hpp"
#include "Array.hpp"
#include "Object.hpp"
#include "Base.hpp"

// TODO: make Objects contain Objects instead of Root (Data Nodels ...)

class Root : public Base
{
    
public:
    
    const std::string mHeader = "ROOT";
    const short mVersion = 0x0100;    // major and minor revisions format
    
private:
    
    // TODO: use hash table instead (Ep. 10) ???
    std::vector<Object*>* mObjects = new std::vector<Object*>;
    short mObjectsCount;
    
public:
    
    Root(std::string name);
    Root();
    ~Root();
    
    char* GetBytes(char* buffer);
    
    bool AddObject(Object* object);
    
    char* Deserialize(char* data);
    
    Object* FindObject(std::string name);
    
    void LogRoot();
    
};
