#include "Root.hpp"
#include "utils/Log.hpp"


Root::Root(std::string name):        // int ???
    mSize(0)
{
    sw = new SerializationWriter();
    setName(name);
    mSize += header.length() + sizeof(containerType) + sizeof(nameLength) + sizeof(mSize) + sizeof(mObjectsCount);
}

Root::~Root()
{
    delete sw;
    delete mObjects;
}

void Root::setName(std::string name)
{
    if (!this->name.empty())
    {
        mSize -= nameLength;
    }
    
    nameLength = name.length();
    this->name = name;
    
    mSize += nameLength;
}

char* Root::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &header);
    ptr = sw->writeBytes(ptr, &containerType);
    ptr = sw->writeBytes(ptr, &nameLength);
    ptr = sw->writeBytes(ptr, &name);
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


