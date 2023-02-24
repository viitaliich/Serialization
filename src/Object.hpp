#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Field.hpp"
#include "Array.hpp"
#include "Base.hpp"


class Object : public Base
{
private:

    // use hash table instead (Ep. 10) ???
    std::vector<Field*>* mFields = new std::vector<Field*>;
    std::vector<Array*>* mArrays = new std::vector<Array*>;
    short mFieldsCount;
    short mArraysCount;
    
public:
    
    Object(std::string name);
    Object();
    ~Object();
    
    bool AddField(Field* field);
    bool AddArray(Array* array);
    
    char* GetBytes(char* buffer);
    
    char* Deserialize(char* data);
    
    Field* FindField(std::string name);
    Array* FindArray(std::string name);
    
    void LogObject();
};
