#pragma once

#include <string>
#include <iostream>

#include "Type.hpp"
#include "ContainerType.hpp"
#include "SerializationWriter.hpp"


class Field
{
public:
    
    const char mContainerType = EnumContainerType::FIELD;
    short mNameLength;       // short    ???
    std::string mName;
    char mDataType;
    short mDataSize;
    char* mData;
    
private:
    SerializationWriter* sw;
    
public:
    
    template <typename T>
    Field(std::string name, char type, const T* value)
    {
        sw = new SerializationWriter();
        setName(name);
        mDataType = type;
        mDataSize = sizeof(T);
        
        this->mData = new char[mDataSize];
        sw->writeBytes(this->mData, value);
    }
    
    Field(std::string name, char type, const std::string* value)
    {
        sw = new SerializationWriter();
        setName(name);
        mDataType = type;
        mDataSize = value->length();
        
        this->mData = new char[mDataSize];
        sw->writeBytes(this->mData, value);
    }
    
    Field();
    ~Field();
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
    
    inline size_t GetFieldSize() const
    {
        // can be modified (depends on class members) ???
        return sizeof(mContainerType) + sizeof(mNameLength) + mNameLength + sizeof(mDataType) + sizeof(mDataSize) + mDataSize;
    }
    
    char* Deserialize(char* data);
    
    void LogField();
};
