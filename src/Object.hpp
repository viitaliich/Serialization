#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "ContainerType.hpp"
#include "ReadWriteBytes.hpp"
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
    
    void LogObject();
};
