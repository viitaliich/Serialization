#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "ContainerType.hpp"
#include "SerializationWriter.hpp"
#include "Field.hpp"
#include "Array.hpp"


class Object
{
public:
    
    const char mContainerType = EnumContainerType::OBJECT;
    short mNameLength;       // short    ???
    std::string mName;
    
private:
    SerializationWriter* sw;
    short mSize;
    
    // use hash table instead (Ep. 10) ???
    std::vector<Field*>* mFields = new std::vector<Field*>;
    std::vector<Array*>* mArrays = new std::vector<Array*>;
    short mFieldsCount;
    short mArraysCount;
    
public:
    
    Object(std::string name);
    Object();
    ~Object();
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
    
    inline size_t GetObjectSize()
    {
        return mSize;
    }
    
    bool AddField(Field* field);
    bool AddArray(Array* array);
    
    void Deserialize(char* data);
    
    void LogObject();
};
