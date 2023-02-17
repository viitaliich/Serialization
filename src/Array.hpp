#pragma once

#include <string>
#include <iostream>

#include "ContainerType.hpp"
#include "SerializationWriter.hpp"


class Array
{
public:
    
    const char containerType = EnumContainerType::ARRAY;
    short nameLength;       // short    ???
    std::string name;
    char dataType;
    short dataCount;          // size_t ???
    short dataSize;
    char* data;
    
private:
    SerializationWriter* sw;
    
public:
    
    template <typename T>
    Array(std::string name, char type, const T* value, const short length)        // int ???
    {
        sw = new SerializationWriter();
        setName(name);
        dataType = type;        // ??? do we need this?
        dataSize = sizeof(T);
        dataCount = length;
        this->data = new char[dataSize ];
        sw->writeBytes(data, value, dataSize );
    }
    
    ~Array();
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
    
    inline size_t GetArraySize()
    {
        // can be modified (depends on class members) ???
        return sizeof(containerType) + sizeof(nameLength) + nameLength + sizeof(dataType) + sizeof(dataCount) + sizeof(dataSize) + dataSize * dataCount;
    }
};
