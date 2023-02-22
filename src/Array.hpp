#pragma once

#include <string>
#include <iostream>

#include "Type.hpp"
#include "ContainerType.hpp"
#include "SerializationWriter.hpp"


class Array
{
public:
    
    const char mContainerType = EnumContainerType::ARRAY;
    short mNameLength;       // short    ???
    std::string mName;
    char mDataType;
    short mDataCount;          // size_t ???
    short mDataSize;
    char* mData;
    
private:
    SerializationWriter* sw;
    short mSize;
    
public:
    
    template <typename T>
    Array(std::string name, char type, const T* value, const short length)        // int ???
    {
        sw = new SerializationWriter();
        setName(name);
        mDataType = type;
        mDataSize = sizeof(T);
        mDataCount = length;
        mSize += sizeof(mContainerType) + sizeof(mNameLength) + sizeof(mSize) + sizeof(mDataType) + sizeof(mDataCount) + sizeof(mDataSize) + mDataSize;
        this->mData = new char[mDataSize ];
        sw->writeBytes(mData, value, mDataSize );
    }
    
    Array();
    ~Array();
    
    void setName(std::string name);
    char* GetBytes(char* buffer);
    
    inline size_t GetArraySize() const
    {
        return mSize;
    }
    
    char* Deserialize(char* data);
    
    void LogArray();
};
