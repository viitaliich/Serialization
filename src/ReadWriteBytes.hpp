#pragma once

#include <string>
#include <iostream>

#include "utils/Log.hpp"


// TODO: use it as functions, not object methods (statically?) ???
// TODO: Reflection ???

class ReadWriteBytes
{
public:
    
    template <typename T>
    char* writeBytes(char* buffer, const T* value)
    {
        char* ptr = buffer;
        std::memcpy(ptr, value, sizeof(T));
        ptr += sizeof(T);
        return ptr;
    }
    
    template <typename T>
    char* writeBytes(char* buffer, const T* value, short arraySize)        // short -> size_t
    {
        char* ptr = buffer;
        std::memcpy(ptr, value, arraySize);
        ptr += arraySize;
        return ptr;
    }
    
    char* writeBytes(char* buffer, const std::string* value)
    {
        short valueLength = value->length();        // short -> size_t
        const char* valueChar = value->c_str();
        
        char* ptr = writeBytes(buffer, valueChar, valueLength);
        return ptr;
    }
    
    // TODO: list of 8 booleans in 1 byte
    
    template <typename T>
    char* readBytes(char* buffer, T* value)
    {
        char* ptr = buffer;
        std::memcpy(value, ptr, sizeof(T));
        ptr += sizeof(T);
        return ptr;
    }
    
    char* readBytes(char* buffer, std::string* value, short valueLength)
    {
        char* ptr = buffer;
        std::string strValue(ptr, valueLength);
        *value = strValue;
        ptr += valueLength;
        return ptr;
    }
    
    template <typename T>
    char* readBytes(char* buffer, T* value, short valueLength)        // short -> size_t
    {
        char* ptr = buffer;
        std::memcpy(value, ptr, valueLength);
        ptr += valueLength;
        return ptr;
    }
    
public:
    
    ReadWriteBytes(){}
    ~ReadWriteBytes(){}
    
};
