#pragma once

#include <iostream>

#include "utils/Log.hpp"
#include "ReadWriteBytes.hpp"


enum EnumContainerType : char
{
    UNKNOWN_CONTAINER = 0,
    FIELD,
    ARRAY,
    OBJECT,
    ROOT
};

enum EnumType : char
{
    UNKNOWN_TYPE = 0,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    BOOL,
    STRING
};

class Base
{

private:
    
    
    
protected:

    ReadWriteBytes* sw;
    char mContainerType;
    short mNameLength;       // short    ???
    std::string mName;
    short mSize;
    
public:
    
    Base();
    ~Base();
    
    void setName(std::string name);
    
    inline size_t GetSize() const
    {
        return mSize;
    }
    
    inline std::string GetName() const
    {
        return mName;
    }
};
