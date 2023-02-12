#pragma once

enum EnumContainerType : char
{
    UNKNOWN_CONTAINER = 0,
    FIELD,
    ARRAY,
    OBJECT
};

class ContainerType
{
public:
    
    const EnumContainerType mEnumContainerType;
    
    
public:
    
    ContainerType();
    ~ContainerType();
    
    
};
