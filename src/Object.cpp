#include "Object.hpp"
#include "utils/Log.hpp"


Object::Object(std::string name):        // int ???
    mSize(0)
{
    sw = new SerializationWriter();
    setName(name);
    mSize += sizeof(mContainerType) + sizeof(mNameLength) + sizeof(mSize) + sizeof(mFieldsCount) + sizeof(mArraysCount);
}

Object::~Object()
{
    delete sw;
    delete mFields;
    delete mArrays;
}

Object::Object()
{
}


void Object::setName(std::string name)
{
    if (!this->mName.empty())
    {
        mSize -= mNameLength;
    }
    
    mNameLength = name.length();
    this->mName = name;
    
    mSize += mNameLength;
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

void Object::Deserialize(char* data)
{
    char* ptr = data;
    
    char containerType;
    ptr = sw->readBytes(ptr, &containerType);
    if(containerType != mContainerType)
    {
        std::cout << "Can't deserialize Object: wrong Container Type!" << std::endl;
        return;
    }
    
    ptr = sw->readBytes(ptr, &mNameLength);
    ptr = sw->readBytes(ptr, &mName, mNameLength);
    ptr = sw->readBytes(ptr, &mSize);
    ptr = sw->readBytes(ptr, &mFieldsCount);
    // TODO: Fileds
    ptr = sw->readBytes(ptr, &mArraysCount);
    // TODO: Arrays
    
//    std::cout << mObjectsCount << std::endl;
    
}

void Object::LogObject()
{
    std::cout << "mContainerType - " << (int)mContainerType << std::endl;
    std::cout << "mNameLength - " << mNameLength << std::endl;
    std::cout << "mName - " << mName << std::endl;
    std::cout << "mSize - " << mSize << std::endl;
    std::cout << "mArraysCount - " << mArraysCount << std::endl;
    for(size_t i = 0; i < mArraysCount; i++)
    {
        std::cout << "--Array " << i << std::endl;
    }
    std::cout << "mFieldsCount - " << mFieldsCount << std::endl;
    for(size_t i = 0; i < mFieldsCount; i++)
    {
        std::cout << "--Field " << i << std::endl;
    }
    
}


