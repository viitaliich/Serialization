#include "Object.hpp"
#include "utils/Log.hpp"


Object::Object(std::string name):        // int ???
    mSize(0)
{
    sw = new SerializationWriter();
    setName(name);
    mSize += sizeof(containerType) + sizeof(nameLength) + sizeof(mFieldsCount) + sizeof(mArraysCount);
}

Object::~Object()
{
    delete sw;
    delete mFields;
    delete mArrays;
}

void Object::setName(std::string name)
{
    if (!this->name.empty())
    {
        mSize -= nameLength;
    }
    
    nameLength = name.length();
    this->name = name;
    
    mSize += nameLength;
}


char* Object::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &containerType);
    ptr = sw->writeBytes(ptr, &nameLength);
    ptr = sw->writeBytes(ptr, &name);
    ptr = sw->writeBytes(ptr, &mFieldsCount);
    ptr = sw->writeBytes(ptr, &mArraysCount);

    for(size_t i = 0; i < mFields->size(); i++)
    {
        ptr = (*mFields)[i]->GetBytes(ptr);
    }

    for(size_t i = 0; i < mArrays->size(); i++)
    {
        ptr = (*mArrays)[i]->GetBytes(ptr);
    }
    
    return ptr;
}


bool Object::AddField(Field* field)
{
    if(mFields == nullptr || field == nullptr) return false;
    mFields->push_back(field);
    mSize += field->GetFieldSize();
    mFieldsCount = mFields->size();
    return true;
}

bool Object::AddArray(Array* array)
{
    if(mArrays == nullptr || array == nullptr) return false;
    mArrays->push_back(array);
    mSize += array->GetArraySize();
    mArraysCount = mArrays->size();
    return true;
}


