#pragma once

#include <string>
#include <iostream>

#include "ContainerType.hpp"
#include "SerializationWriter.hpp"


class Field
{
public:
    
    const char containerType = EnumContainerType::FIELD;
    short nameLength;       // short    ???
    char* name;
    char dataType;
    short dataSize;
    char* data;
    SerializationWriter* sw;
    
public:
    
    Field();
    ~Field();
    
    template <typename T>
    Field(std::string name, char type, const T* value)
    {
        sw = new SerializationWriter();
        setName(name);
        dataType = type;        // ??? do we need this?
        dataSize = sizeof(T);
        
        this->data = new char[sizeof(T)];
        sw->writeBytes(this->data, value);
    }
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
};
