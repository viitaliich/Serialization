#include "Root.hpp"
#include "utils/Log.hpp"


Root::Root(std::string name):        // int ???
    mSize(0)
{
    sw = new SerializationWriter();
    setName(name);
    mSize += mHeader.length() + sizeof(mContainerType) + sizeof(mNameLength) + sizeof(mSize) + sizeof(mObjectsCount);
}

Root::Root()
{
}

Root::~Root()
{
    delete sw;
    for(size_t i = 0; i < mObjectsCount; i++)
    {
        delete (*mObjects)[i];
    }
    delete mObjects;
}

void Root::setName(std::string name)
{
    if (!this->mName.empty())
    {
        mSize -= mNameLength;
    }
    
    mNameLength = name.length();
    this->mName = name;
    
    mSize += mNameLength;
}

char* Root::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &mHeader);
    ptr = sw->writeBytes(ptr, &mContainerType);
    ptr = sw->writeBytes(ptr, &mNameLength);
    ptr = sw->writeBytes(ptr, &mName);
    ptr = sw->writeBytes(ptr, &mSize);
    ptr = sw->writeBytes(ptr, &mObjectsCount);

    for(size_t i = 0; i < mObjects->size(); i++)
    {
        ptr = (*mObjects)[i]->GetBytes(ptr);
    }
    
    return ptr;
}

bool Root::AddObject(Object* object)
{
    if(mObjects == nullptr || object == nullptr) return false;
    mObjects->push_back(object);
    mSize += object->GetObjectSize();
    mObjectsCount = mObjects->size();
    return true;
}

void Root::Deserialize(char* data)
{
    char* ptr = data;
    
    std::string header;
    ptr = sw->readBytes(ptr, &header, 4);
    if(header.compare(mHeader))
    {
        std::cout << "Can't deserialize Root: wrong header!" << std::endl;
        return;
    }
    
    char containerType;
    ptr = sw->readBytes(ptr, &containerType);
    if(containerType != mContainerType)
    {
        std::cout << "Can't deserialize Root: wrong Container Type!" << std::endl;
        return;
    }
    
    ptr = sw->readBytes(ptr, &mNameLength);
    ptr = sw->readBytes(ptr, &mName, mNameLength);
    ptr = sw->readBytes(ptr, &mSize);
    ptr = sw->readBytes(ptr, &mObjectsCount);
    
    for(size_t i = 0; i < mObjectsCount; i++)
    {
        Object* object = new Object();
        object->Deserialize(ptr);
        mObjects->push_back(object);
    }
    
//    std::cout << mObjectsCount << std::endl;
    
}

void Root::LogRoot()
{
    std::cout << "mHeader - " << mHeader << std::endl;
    std::cout << "mContainerType - " << (int)mContainerType << std::endl;
    std::cout << "mNameLength - " << mNameLength << std::endl;
    std::cout << "mName - " << mName << std::endl;
    std::cout << "mSize - " << mSize << std::endl;
    std::cout << "mObjectsCount - " << mObjectsCount << std::endl;
    for(size_t i = 0; i < mObjectsCount; i++)
    {
        std::cout << "-Object " << i << std::endl;
        (*mObjects)[i]->LogObject();
    }
    
}

