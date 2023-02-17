#include "Field.hpp"


Field::~Field()
{
    delete sw;
}

void Field::setName(std::string name)
{
    nameLength = name.length();
    this->name = name;
}

char* Field::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &containerType);
    ptr = sw->writeBytes(ptr, &nameLength);
    ptr = sw->writeBytes(ptr, &name);
    ptr = sw->writeBytes(ptr, &dataType);
    ptr = sw->writeBytes(ptr, &dataSize);
    ptr = sw->writeBytes(ptr, data, dataSize);
    
    
    return ptr;
}


