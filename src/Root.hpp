#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "ContainerType.hpp"
#include "SerializationWriter.hpp"
#include "Field.hpp"
#include "Array.hpp"
#include "Object.hpp"

// TODO: make Objects contain Objects instead of Root (Data Nodels ...)

class Root
{
public:
    const std::string mHeader = "ROOT";
    const char mContainerType = EnumContainerType::ROOT;
    short mNameLength;       // short    ???
    std::string mName;
    
private:
    SerializationWriter* sw;
    short mSize;
    
    // use hash table instead (Ep. 10) ???
    std::vector<Object*>* mObjects = new std::vector<Object*>;
    short mObjectsCount;
    
public:
    
    Root(std::string name);
    Root();
    ~Root();
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
    
    inline size_t GetRootSize()
    {
        return mSize;
    }
    
    bool AddObject(Object* object);
    
    void Deserialize(char* data);
};
