#include "Object.hpp"
#include "utils/Log.hpp"


Object::Object(std::string name)
{
    mContainerType = EnumContainerType::OBJECT;
    setName(name);
    mSize += sizeof(mFieldsCount) + sizeof(mArraysCount);
}

Object::Object()
{
    mContainerType = EnumContainerType::OBJECT;
}

Object::~Object()
{
    delete mFields;
    delete mArrays;
}

char* Object::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &mContainerType);
    ptr = sw->writeBytes(ptr, &mNameLength);
    ptr = sw->writeBytes(ptr, &mName);
    ptr = sw->writeBytes(ptr, &mSize);
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
    mSize += field->GetSize();
    mFieldsCount = mFields->size();
    return true;
}

bool Object::AddArray(Array* array)
{
    if(mArrays == nullptr || array == nullptr) return false;
    mArrays->push_back(array);
    mSize += array->GetSize();
    mArraysCount = mArrays->size();
    return true;
}

char* Object::Deserialize(char* data)
{
    char* ptr = data;
    
    char containerType;
    ptr = sw->readBytes(ptr, &containerType);
    if(containerType != mContainerType)
    {
        std::cout << "Can't deserialize Object: wrong Container Type!" << std::endl;
        return nullptr;
    }
    
    ptr = sw->readBytes(ptr, &mNameLength);
    ptr = sw->readBytes(ptr, &mName, mNameLength);
    ptr = sw->readBytes(ptr, &mSize);
    ptr = sw->readBytes(ptr, &mFieldsCount);
    ptr = sw->readBytes(ptr, &mArraysCount);
    
    for(size_t i = 0; i < mFieldsCount; i++)
    {
        Field* field = new Field();
        
        ptr = field->Deserialize(ptr);
        mFields->push_back(field);
    }
    
    for(size_t i = 0; i < mArraysCount; i++)
    {
        Array* array = new Array();
        ptr = array->Deserialize(ptr);
        mArrays->push_back(array);
    }
    
    return ptr;
}

void Object::LogObject()
{
    std::cout << "mContainerType - " << (int)mContainerType << std::endl;
    std::cout << "mNameLength - " << mNameLength << std::endl;
    std::cout << "mName - " << mName << std::endl;
    std::cout << "mSize - " << mSize << std::endl;
    std::cout << "mFieldsCount - " << mFieldsCount << std::endl;
    std::cout << "mArraysCount - " << mArraysCount << std::endl;
    
    for(size_t i = 0; i < mFieldsCount; i++)
    {
        std::cout << "--Field " << i << std::endl;
        (*mFields)[i]->LogField();
    }
    
    for(size_t i = 0; i < mArraysCount; i++)
    {
        std::cout << "--Array " << i << std::endl;
        (*mArrays)[i]->LogArray();
    }
}
