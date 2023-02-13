#include "Array.hpp"


Array::~Array()
{
    delete sw;
}

void Array::setName(std::string name)
{
    nameLength = name.length();
    this->name = (char*)name.c_str();
}

char* Array::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &containerType);
    ptr = sw->writeBytes(ptr, &nameLength);
    ptr = sw->writeBytes(ptr, this->name, nameLength);
    ptr = sw->writeBytes(ptr, &dataType);
    ptr = sw->writeBytes(ptr, &dataSize);
    ptr = sw->writeBytes(ptr, &dataCount);
    ptr = sw->writeBytes(ptr, data, dataSize);
    
    
    return ptr;
}


