#include "Field.hpp"


Field::Field()
{
    mContainerType = EnumWrapperType::FIELD;
}

Field::~Field()
{
    delete[] mData;
}

char* Field::PackBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &mContainerType);
    ptr = sw->writeBytes(ptr, &mNameLength);
    ptr = sw->writeBytes(ptr, &mName);
    ptr = sw->writeBytes(ptr, &mDataType);
    ptr = sw->writeBytes(ptr, &mDataSize);
    ptr = sw->writeBytes(ptr, &mSize);
    ptr = sw->writeBytes(ptr, mData, mDataSize);
    return ptr;
}

char* Field::Deserialize(char* data)
{
    char* ptr = data;
    
    char containerType;
    ptr = sw->readBytes(ptr, &containerType);
    if(containerType != mContainerType)
    {
        std::cout << "Can't deserialize Field: wrong Container Type!" << std::endl;
        return nullptr;
    }
    
    ptr = sw->readBytes(ptr, &mNameLength);
    ptr = sw->readBytes(ptr, &mName, mNameLength);
    ptr = sw->readBytes(ptr, &mDataType);
    ptr = sw->readBytes(ptr, &mDataSize);
    ptr = sw->readBytes(ptr, &mSize);
    mData = new char[mDataSize];
    ptr = sw->readBytes(ptr, mData, mDataSize);
    
    return ptr;
}

void Field::LogField()
{
    std::cout << "mContainerType - " << (int)mContainerType << std::endl;
    std::cout << "mNameLength - " << mNameLength << std::endl;
    std::cout << "mName - " << mName << std::endl;
    std::cout << "mDataType - " << (int)mDataType << std::endl;
    std::cout << "mDataSize - " << mDataSize << std::endl;
    
    char charResult;
    short shortResult;
    int intResult;
    long longResult;
    float floatResult;
    double doubleResult;
    bool boolResult;
    
    switch (mDataType) {
        case EnumType::CHAR:
            sw->readBytes(mData, &charResult);
            std::cout << "mData - " << charResult << std::endl;
            break;
        case EnumType::SHORT:
            sw->readBytes(mData, &shortResult);
            std::cout << "mData - " << shortResult << std::endl;
            break;
        case EnumType::INT:
            sw->readBytes(mData, &intResult);
            std::cout << "mData - " << intResult << std::endl;
            break;
        case EnumType::LONG:
            sw->readBytes(mData, &longResult);
            std::cout << "mData - " << longResult << std::endl;
            break;
        case EnumType::FLOAT:
            sw->readBytes(mData, &floatResult);
            std::cout << "mData - " << floatResult << std::endl;
            break;
        case EnumType::DOUBLE:
            sw->readBytes(mData, &doubleResult);
            std::cout << "mData - " << doubleResult << std::endl;
            break;
        case EnumType::BOOL:
            sw->readBytes(mData, &boolResult);
            std::cout << "mData - " << boolResult << std::endl;
            break;
        case EnumType::STRING:
            std::cout << "mData - " << std::string(mData, mDataSize) << std::endl;
            break;
        default:
            std::cout << "ERROR: Unrecognised Field type!" << std::endl;
            return;
    }
}
