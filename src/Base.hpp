#pragma once

#include <iostream>

#include "utils/Log.hpp"
#include "ReadWriteBytes.hpp"


enum EnumWrapperType : char
{
    UNKNOWN_CONTAINER = 0,
    FIELD,
    ARRAY,
    OBJECT,
    ROOT
};

// TODO: serialise int16_t, int 32_t, ...
// TODO: serialise vector, ...

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
protected:
    ReadWriteBytes* sw;
    char mContainerType;
    short mNameLength;       // short    ???
    std::string mName;
    short mSize;
    
protected:
    Base();
    ~Base();
    
public:
    void setName(std::string name);
    
    // TODO: ??? virtual char* GetBytes(char* buffer) = 0;
    
    inline size_t GetSize() const
    {
        return mSize;
    }
    
    inline std::string GetName() const
    {
        return mName;
    }
};
