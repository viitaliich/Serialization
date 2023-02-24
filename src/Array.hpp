#pragma once

#include <string>
#include <iostream>

#include "Base.hpp"


class Array : public Base
{
public:
    
    char mDataType;
    short mDataCount;          // size_t ???
    short mDataSize;
    char* mData;
    
public:
    
    template <typename T>
    Array(std::string name, char type, const T* value, const short length)        // int ???
    {
        mContainerType = EnumContainerType::ARRAY;
        setName(name);
        mDataType = type;
        mDataSize = sizeof(T);
        mDataCount = length;
        mSize += sizeof(mDataType) + sizeof(mDataCount) + sizeof(mDataSize) + mDataSize;
        this->mData = new char[mDataSize];
        sw->writeBytes(mData, value, mDataSize);
    }
    
    Array();
    ~Array();
    
    char* GetBytes(char* buffer);
    
    char* Deserialize(char* data);
    
    void LogArray();
};
