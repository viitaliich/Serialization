#include <iostream>

#include "utils/Log.hpp"
#include "ReadWriteBytes.hpp"
#include "Root.hpp"
#include "Object.hpp"
#include "Array.hpp"
#include "Field.hpp"

#define str(s) #s

// TODO: serialise int16_t, int 32_t, ...
// TODO: serialise vector, ...

// TODO: reflection, RTTI

class SandBox
{
public:
    int valInt;
    std::string valStr;
    bool arr[10] = {true, true, true};
    
    SandBox()
    {
        valInt = 8;
        valStr = "Hello";
    }
};


char* testSerialisation(char* buffer)
{
    SandBox* sandbox = new SandBox();

    Field* field = new Field(str(sandbox->valInt), EnumType::INT, &sandbox->valInt);
    Array* array = new Array(str(sandbox->arr), EnumType::BOOL, &sandbox->arr, 10);
    
    Object* object = new Object(str(sandbox));
    object->AddArray(array);
    object->AddField(field);
    
    Root* root = new Root(str(root));
    root->AddObject(object);
    
    size_t bufferSize = 0;
//    bufferSize += field->GetSize();
//    bufferSize += array->GetSize();
//    bufferSize += object->GetSize();
    bufferSize += root->GetSize();
    
    buffer = new char[bufferSize];
    char* ptr = buffer;
    
//    ptr = field->PackBytes(ptr);
//    ptr = array->PackBytes(ptr);
//    ptr = object->PackBytes(ptr);
    ptr = root->PackBytes(ptr);
       
    logBytes(buffer, bufferSize);
    
//    const char* filePath = "/Users/vklimov/dev/Serialization/Serialization/src/test_file.txt";
//    logBytesToFile(filePath, buffer, bufferSize);
    
    return buffer;
}

void testDeserialisation(char* data)
{
    char* ptr = data;
    Root* root = new Root();
    ptr = root->Deserialize(ptr);
    root->LogRoot();
    
    Object* object = root->FindObject("sandbox");
    Field* field = object->FindField("sandbox->valInt");
    int intVal;
    std::memcpy(&intVal, field->mData, sizeof(int));
    std::cout << "INT_VAL = " << intVal << std::endl;
    
    delete root;
}


int main(int argc, const char * argv[]) {
    
    char* data = testSerialisation(nullptr);
    testDeserialisation(data);
    
    return 0;
}
