#pragma once

#include <string>
#include <iostream>

#include "Base.hpp"


class Field : public Base
{
public:
    
    char mDataType;
    short mDataSize;
    char* mData;
    
public:
    
    template <typename T>
    Field(std::string name, char type, const T* value)
    {
        mContainerType = EnumContainerType::FIELD;
        setName(name);
        mDataType = type;
        mDataSize = sizeof(T);
        this->mData = new char[mDataSize];
        mSize += sizeof(mDataType) + sizeof(mDataSize) + mDataSize;
        sw->writeBytes(this->mData, value);
    }
    
    Field(std::string name, char type, const std::string* value)
    {
        mContainerType = EnumContainerType::FIELD;
        setName(name);
        mDataType = type;
        mDataSize = value->length();
        this->mData = new char[mDataSize];
        mSize += sizeof(mDataType) + sizeof(mDataSize) + mDataSize;
        sw->writeBytes(this->mData, value);
    }
    
    Field();
    ~Field();
    
    char* GetBytes(char* buffer);
    
    char* Deserialize(char* data);
    
    void LogField();
};
