#pragma once

enum EnumContainerType : char
{
    UNKNOWN_CONTAINER = 0,
    FIELD,
    ARRAY,
    OBJECT,
    ROOT
};

class ContainerType
{
public:
    
    const EnumContainerType mEnumContainerType;
    
public:
    
    ContainerType();
    ~ContainerType();
    
};
