#pragma once

#include <iostream>

enum EnumType : char
{
    UNKNOWN_TYPE = 0,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    BOOL

};

class Type{
  
public:
    
    const EnumType mType;
    
public:
    
    Type();
    ~Type();
    
    size_t GetSize(char type);
    
};

