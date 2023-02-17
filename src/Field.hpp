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
    std::string name;
    char dataType;
    short dataSize;
    char* data;
    
private:
    SerializationWriter* sw;
    
public:
    
    template <typename T>
    Field(std::string name, char type, const T* value)
    {
        sw = new SerializationWriter();
        setName(name);
        dataType = type;        // ??? do we need this?
        dataSize = sizeof(T);
        
        this->data = new char[dataSize];
        sw->writeBytes(this->data, value);
    }
    
    Field(std::string name, char type, const std::string* value)
    {
        sw = new SerializationWriter();
        setName(name);
        dataType = type;        // ??? do we need this?
        dataSize = value->length();
        
        this->data = new char[dataSize];
        sw->writeBytes(this->data, value);
    }
    
    ~Field();
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
    
    inline size_t GetFieldSize()
    {
        // can be modified (depends on class members) ???
        return sizeof(containerType) + sizeof(nameLength) + nameLength + sizeof(dataType) + sizeof(dataSize) + dataSize;
    }
};
