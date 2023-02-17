#include <iostream>

#include "utils/Log.hpp"
#include "SerializationWriter.hpp"
#include "Object.hpp"
#include "Field.hpp"
#include "Array.hpp"
#include "Type.hpp"


int main(int argc, const char * argv[]) {
    
//    int diff = rand() % (int)((2 * 100 + 1) - 100);
//    printf("%d\n", diff);
    
    

    size_t bufferSize = 200;         // field->GetFieldSize()
    char* data = new char[bufferSize];
    char* ptr = data;
    
    int val = 8;
    Field* field = new Field("TestField", EnumType::INT, &val);
    ptr = field->GetBytes(ptr);

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Array* array = new Array("TestArray", EnumType::INT, &arr, 10);
    ptr = array->GetBytes(ptr);
    
    Object* object = new Object("Test Object");
    object->AddArray(array);
    object->AddField(field);
    ptr = object->GetBytes(ptr);
    
   
    logBytes(data, bufferSize);
    
    const char* filePath = "/Users/vklimov/dev/Serialization/Serialization/src/test_file.txt";
    logBytesToFile(filePath, data, bufferSize);
    
    delete[] data;
    return 0;
}
