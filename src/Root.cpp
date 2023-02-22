#include "Root.hpp"
#include "utils/Log.hpp"


Root::Root(std::string name)
{
    mContainerType = EnumContainerType::ROOT;
    setName(name);
    mSize += mHeader.length() + sizeof(mVersion) + sizeof(mObjectsCount);
}

Root::Root()
{
    mContainerType = EnumContainerType::ROOT;
}

Root::~Root()
{
    for(size_t i = 0; i < mObjectsCount; i++)
    {
        delete (*mObjects)[i];
    }
    delete mObjects;
}

char* Root::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &mHeader);
    ptr = sw->writeBytes(ptr, &mVersion);
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
    mSize += object->GetSize();
    mObjectsCount = mObjects->size();
    return true;
}

char* Root::Deserialize(char* data)
{
    char* ptr = data;
    
    std::string header;
    ptr = sw->readBytes(ptr, &header, 4);
    if(header.compare(mHeader))
    {
        std::cout << "Can't deserialize Root: wrong header!" << std::endl;
        return nullptr;
    }
    
    short version;
    ptr = sw->readBytes(ptr, &version);
    if(version != mVersion)
    {
        std::cout << "Can't deserialize Root: wrong version!" << std::endl;
        return nullptr;
    }
    
    char containerType;
    ptr = sw->readBytes(ptr, &containerType);
    if(containerType != mContainerType)
    {
        std::cout << "Can't deserialize Root: wrong Container Type!" << std::endl;
        return nullptr;
    }
    
    ptr = sw->readBytes(ptr, &mNameLength);
    ptr = sw->readBytes(ptr, &mName, mNameLength);
    ptr = sw->readBytes(ptr, &mSize);
    ptr = sw->readBytes(ptr, &mObjectsCount);
    
    for(size_t i = 0; i < mObjectsCount; i++)
    {
        Object* object = new Object();
        ptr = object->Deserialize(ptr);
        mObjects->push_back(object);
    }
    
    return ptr;
}

void Root::LogRoot()
{
    std::cout << "mVersion - " << mVersion << std::endl;
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
