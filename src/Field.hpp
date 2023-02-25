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
    
    // TODO: use abstract builder / abstract factory pattern
    // can be helpful in template redefinition
    
    template <typename T>
    Field(std::string name, char type, const T* value)
    {
        mContainerType = EnumWrapperType::FIELD;
        setName(name);
        mDataType = type;
        mDataSize = sizeof(T);
        this->mData = new char[mDataSize];
        mSize += sizeof(mDataType) + sizeof(mDataSize) + mDataSize;
        sw->writeBytes(this->mData, value);
    }
    
    Field(std::string name, char type, const std::string* value)
    {
        mContainerType = EnumWrapperType::FIELD;
        setName(name);
        mDataType = type;
        mDataSize = value->length();
        this->mData = new char[mDataSize];
        mSize += sizeof(mDataType) + sizeof(mDataSize) + mDataSize;
        sw->writeBytes(this->mData, value);
    }
    
    Field();
    ~Field();
    
    char* PackBytes(char* buffer);
    
    char* Deserialize(char* data);
    
    void LogField();
};
