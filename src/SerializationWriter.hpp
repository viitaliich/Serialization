#pragma once

#include <string>
#include <iostream>
#include "utils/Log.hpp"

class SerializationWriter
{
public:
    const char* mHeader;
    const char mHeaderLength;
    const short mVersion;
    
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
    
    char* readBytes(char* buffer, char* value, short* valueLength)        // short -> size_t
    {
        char* ptr = buffer;
        ptr = readBytes(ptr, valueLength);
        std::memcpy(value, ptr, *valueLength);
        ptr += *valueLength;
        
        return ptr;
    }
    
    char* readBytes(char* buffer, std::string* value)
    {
        short valueLength;      // short -> size_t
        char* val;
        char* ptr = buffer;
        ptr = readBytes(ptr, val, &valueLength);
        *value = val;
        
        return ptr;
    }
    
public:
    
    SerializationWriter();
    ~SerializationWriter();
};
