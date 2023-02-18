#include <iostream>

#include "utils/Log.hpp"
#include "SerializationWriter.hpp"
#include "Root.hpp"
#include "Object.hpp"
#include "Field.hpp"
#include "Array.hpp"
#include "Type.hpp"

#define str(s) #s


void testSerialisation()
{
    
//    int val = 8;
    std::string val = "HELLO";
    int arr[] = {1, 2, 3};
    
    Field* field = new Field(str(val), EnumType::INT, &val);
    Array* array = new Array(str(arr), EnumType::INT, &arr, 3);
    
    Object* object = new Object(str(object));
    object->AddArray(array);
    object->AddField(field);
    
    Root* root = new Root(str(root));
    root->AddObject(object);
    
    size_t bufferSize = 0;         // field->GetFieldSize()
    bufferSize += field->GetFieldSize();
    bufferSize += array->GetArraySize();
    bufferSize += object->GetObjectSize();
    bufferSize += root->GetRootSize();
    
    char* data = new char[bufferSize];
    char* ptr = data;
    
    ptr = field->GetBytes(ptr);
    ptr = array->GetBytes(ptr);
    ptr = object->GetBytes(ptr);
    ptr = root->GetBytes(ptr);
       
    logBytes(data, bufferSize);
    
    const char* filePath = "/Users/vklimov/dev/Serialization/Serialization/src/test_file.txt";
    logBytesToFile(filePath, data, bufferSize);
    
    delete[] data;
}

void testDeserialisation()
{
    
}


int main(int argc, const char * argv[]) {
    
    testSerialisation();
    testDeserialisation();
    
    return 0;
}
