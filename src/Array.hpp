#pragma once

#include <string>
#include <iostream>
#include <math.h>

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
        mDataCount = length;
        
        if(type != EnumType::BOOL)
        {
            mDataSize = sizeof(T);
            mSize += sizeof(mDataType) + sizeof(mDataCount) + sizeof(mDataSize) + mDataSize;
            this->mData = new char[mDataSize];
            sw->writeBytes(mData, value, mDataSize);
        }
        else
        {
            mDataSize = (int)(mDataCount/8) + 1;
            mSize += sizeof(mDataType) + sizeof(mDataCount) + sizeof(mDataSize) + mDataSize;
            mData = new char[mDataSize];
            
            char* ptr = mData;
            char val = 0;
            for (int i = 0; i < length; i++)
            {
                if(i > 0 && (i % 8) == 0)
                {
                    ptr = sw->writeBytes(ptr, &val);
                    val = 0;
                }
                val ^= ((*value)[i] << i % 8);
            }
            
            ptr = sw->writeBytes(ptr, &val);
        }
    }
    
    Array();
    ~Array();
    
    char* GetBytes(char* buffer);
    
    char* Deserialize(char* data);
    
    void LogArray();
};
