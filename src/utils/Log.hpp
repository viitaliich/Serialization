#pragma once

#include <iostream>

inline void logHex(int value)
{
    printf("Hex val = %x (decimal val = %d)\n", value, value);
}

inline void logHex(char value)
{
    printf("Hex val = %x (decimal val = %d, char value = %c)\n", value, value, value);
}

inline void logBytes(char* buffer, size_t bufferLength)
{
    for(size_t i = 0; i < bufferLength; i++)
    {
        printf("[%zu] - ", i);
        logHex(buffer[i]);
    }
}

inline void logCharArray(const char* array, const size_t length)
{
    for(size_t i = 0; i < length; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}
