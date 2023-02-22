#include "Base.hpp"

Base::Base():
    mSize(sizeof(mNameLength) + sizeof(mSize) + sizeof(mContainerType))
{
    sw = new ReadWriteBytes();
}

Base::~Base()
{
    delete sw;
}

void Base::setName(std::string name)
{
    if (!this->mName.empty())
    {
        mSize -= mNameLength;
    }
    
    mNameLength = name.length();
    this->mName = name;
    
    mSize += mNameLength;
}
