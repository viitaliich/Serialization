#pragma once

#include <string>
#include <iostream>

#include "ContainerType.hpp"
#include "SerializationWriter.hpp"
//#include "Writer.hpp"


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
    
    template <typename T>
    Field(std::string name, char type, const T* value)
    {
        sw = new SerializationWriter();
        setName(name);
        dataType = type;
        for(int i = 0; i < nameLength; i++)
        {
            std::cout << this->name[i] << " ";
        }
        std::cout << "\n";
        
        dataSize = sizeof(T);
        
        this->data = new char[sizeof(T)];
        sw->writeBytes(this->data, value);

//        char* buf = new char[sizeof(T)];
//        sw->writeBytes(buf, &value);
        
//        this->data = new char[sizeof(T)];
//        sw->writeBytes(this->data, buf, sizeof(T));

        
    }
    
    void setName(std::string name)
    {
        nameLength = name.length();
        this->name = (char*)name.c_str();
    }

    char* GetBytes(char* buffer)
    {
        char* ptr = buffer;
        ptr = sw->writeBytes(ptr, &containerType);
        ptr = sw->writeBytes(ptr, &nameLength);
        ptr = sw->writeBytes(ptr, this->name, nameLength);
        ptr = sw->writeBytes(ptr, &dataType);
        ptr = sw->writeBytes(ptr, &dataSize);
        ptr = sw->writeBytes(ptr, data, dataSize);
        
        
        return ptr;
    }
};
