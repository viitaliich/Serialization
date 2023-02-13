#include <iostream>

#include "utils/Log.hpp"
#include "SerializationWriter.hpp"
#include "Field.hpp"
#include "Array.hpp"
#include "Type.hpp"

int main(int argc, const char * argv[]) {

    size_t bufferSize = 32;         // field->GetFieldSize()
    char* data = new char[bufferSize];
    char* ptr = data;
    
//    long val = 10;
//    Field* field = new Field("Test", EnumType::LONG, &val);
//    ptr = field->GetBytes(ptr);

    int arr[] = {1, 2, 3, 4, 5};
    Array* array = new Array("Test", EnumType::INT, &arr, 5);
    ptr = array->GetBytes(ptr);
    
//    int array[] = {1, 2};
//    SerializationWriter* sw = new SerializationWriter();
//    ptr = sw->writeBytes(ptr, array, 2);
    
    logBytes(data, bufferSize);
    
    delete[] data;
    return 0;
}
