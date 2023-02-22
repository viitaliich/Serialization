#include "Type.hpp"

Type::Type() :
    mType(UNKNOWN_TYPE)
{
    
}

Type::~Type()
{
    
}

size_t Type::GetSize(char type)
{
    switch(type)
    {
        case CHAR:
            return sizeof(char);
        case SHORT:
            return sizeof(short);
        case INT:
            return sizeof(int);
        case LONG:
            return sizeof(long);
        case FLOAT:
            return sizeof(float);
        case DOUBLE:
            return sizeof(double);
        case BOOL:
            return sizeof(bool);
        default:
            return 0;
    }
}
