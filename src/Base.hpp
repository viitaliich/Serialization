#pragma once

#include <iostream>

#include "ReadWriteBytes.hpp"

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
    
    inline size_t GetSize()
    {
        return mSize;
    }
};
