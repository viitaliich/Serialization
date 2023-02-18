#include <iostream>

#include "utils/Log.hpp"
#include "SerializationWriter.hpp"
#include "Root.hpp"
#include "Object.hpp"
#include "Field.hpp"
#include "Array.hpp"
#include "Type.hpp"

#define str(s) #s


char* testSerialisation(char* buffer)
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
//    bufferSize += field->GetFieldSize();
//    bufferSize += array->GetArraySize();
//    bufferSize += object->GetObjectSize();
    bufferSize += root->GetRootSize();
    
    buffer = new char[bufferSize];
    char* ptr = buffer;
    
//    ptr = field->GetBytes(ptr);
//    ptr = array->GetBytes(ptr);
//    ptr = object->GetBytes(ptr);
    ptr = root->GetBytes(ptr);
       
    logBytes(buffer, bufferSize);
    
    const char* filePath = "/Users/vklimov/dev/Serialization/Serialization/src/test_file.txt";
    logBytesToFile(filePath, buffer, bufferSize);
    
    return buffer;
}

void testDeserialisation(char* data)
{
    Root* root = new Root();
    root->Deserialize(data);
    
//    std::cout << root->mHeader << std::endl;
//    std::cout << (int)root->mContainerType << std::endl;
//    std::cout << root->mNameLength << std::endl;
//    std::cout << root->mName << std::endl;
}


int main(int argc, const char * argv[]) {
    
    char* data = testSerialisation(data);
    testDeserialisation(data);
    
    return 0;
}
