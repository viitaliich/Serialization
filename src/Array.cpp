#include "Array.hpp"


Array::Array()
{
    mContainerType = EnumContainerType::ARRAY;
}

Array::~Array()
{
    delete[] mData;
}

char* Array::GetBytes(char* buffer)
{
    char* ptr = buffer;
    ptr = sw->writeBytes(ptr, &mContainerType);
    ptr = sw->writeBytes(ptr, &mNameLength);
    ptr = sw->writeBytes(ptr, &mName);
    ptr = sw->writeBytes(ptr, &mSize);
    ptr = sw->writeBytes(ptr, &mDataType);
    ptr = sw->writeBytes(ptr, &mDataSize);
    ptr = sw->writeBytes(ptr, &mDataCount);
    ptr = sw->writeBytes(ptr, mData, mDataSize);
    
    return ptr;
}

char* Array::Deserialize(char* data)
{
    char* ptr = data;
    
    char containerType;
    ptr = sw->readBytes(ptr, &containerType);
    if(containerType != mContainerType)
    {
        std::cout << "Can't deserialize Array: wrong Container Type!" << std::endl;
        return nullptr;
    }
    
    ptr = sw->readBytes(ptr, &mNameLength);
    ptr = sw->readBytes(ptr, &mName, mNameLength);
    ptr = sw->readBytes(ptr, &mSize);
    ptr = sw->readBytes(ptr, &mDataType);
    ptr = sw->readBytes(ptr, &mDataSize);
    ptr = sw->readBytes(ptr, &mDataCount);
    mData = new char[mDataSize];
    ptr = sw->readBytes(ptr, mData, mDataSize);
    
    return ptr;
}

void Array::LogArray()
{
    std::cout << "mContainerType - " << (int)mContainerType << std::endl;
    std::cout << "mNameLength - " << mNameLength << std::endl;
    std::cout << "mName - " << mName << std::endl;
    std::cout << "mSize - " << mSize << std::endl;
    std::cout << "mDataType - " << (int)mDataType << std::endl;
    std::cout << "mDataCount - " << mDataCount << std::endl;
    std::cout << "mDataSize - " << mDataSize << std::endl;
    
    char* ptr = mData;
    
    if(mDataType == EnumType::BOOL)
    {
        char boolResult;
        for(int i = 0; i < mDataCount/8 + 1; i++)
        {
            sw->readBytes(ptr, &boolResult);
            for(char j = 0; j < 8; j++)
            {
                std::cout << "---ArrayElement " << j << " ";
                std::cout << (bool)((int)boolResult & ((int)pow(2, j))) << std::endl;
            }
            ptr += sizeof(char);
        }
        return;
    }
    
    for(size_t i = 0; i < mDataCount; i++)
    {
        std::cout << "---ArrayElement " << i << " ";
                
        char charResult;
        short shortResult;
        int intResult;
        long longResult;
        float floatResult;
        double doubleResult;
        
        switch (mDataType) {
            case EnumType::CHAR:
                sw->readBytes(ptr, &charResult);
                std::cout << charResult << std::endl;
                ptr += sizeof(charResult);
                break;
            case EnumType::SHORT:
                sw->readBytes(ptr, &shortResult);
                std::cout << shortResult << std::endl;
                ptr += sizeof(shortResult);
                break;
            case EnumType::INT:
                sw->readBytes(ptr, &intResult);
                std::cout << intResult << std::endl;
                ptr += sizeof(intResult);
                break;
            case EnumType::LONG:
                sw->readBytes(ptr, &longResult);
                std::cout << longResult << std::endl;
                ptr += sizeof(longResult);
                break;
            case EnumType::FLOAT:
                sw->readBytes(ptr, &floatResult);
                std::cout << floatResult << std::endl;
                ptr += sizeof(floatResult);
                break;
            case EnumType::DOUBLE:
                sw->readBytes(ptr, &doubleResult);
                std::cout << doubleResult << std::endl;
                ptr += sizeof(doubleResult);
                break;
            case EnumType::BOOL:
                
                break;
            case EnumType::STRING:
                std::cout << std::string(ptr, mDataSize/mDataCount) << std::endl;
                ptr += mDataSize/mDataCount;
                break;
            default:
                std::cout << "ERROR: Unrecognised Array element type!" << std::endl;
                return;
        }
    }
}
