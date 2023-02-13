#include <iostream>

#include "utils/Log.hpp"
#include "SerializationWriter.hpp"
#include "Field.hpp"
#include "Type.hpp"

int main(int argc, const char * argv[]) {

    size_t bufferSize = 32;
    char* data = new char[bufferSize];
    char* ptr = data;
    
    int val = 8;
    int* ptr2 = &val;
    
    Field* field = new Field("Test", EnumType::INT, ptr2);
    ptr = field->GetBytes(ptr);

    logBytes(data, bufferSize);
    
    delete[] data;
    return 0;
}
