#include <iostream>

#include "utils/test.hpp"
#include "SerializationWriter.hpp"
#include "Field.hpp"
#include "IntField.hpp"
#include "Type.hpp"
//#include "Writer.hpp"

int main(int argc, const char * argv[]) {

    size_t bufferSize = 32;
    char* data = new char[bufferSize];
    char* ptr = data;
    
    int val = 8;
    int* ptr2 = &val;
    
//    SerializationWriter* sw = new SerializationWriter();
//    sw->writeBytes(ptr, &val);
    
    Field* field = new Field("Test", EnumType::INT, ptr2);
    ptr = field->GetBytes(ptr);

    for(int i = 0; i < field->nameLength; i++)
    {
        std::cout << (char)(field->name)[i] << " ";
    }
    std::cout << "\n";

    
    
    logBytes(data, bufferSize);
    
    delete[] data;
    return 0;
}
