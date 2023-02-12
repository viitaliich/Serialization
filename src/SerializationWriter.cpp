#include "SerializationWriter.hpp"

SerializationWriter::SerializationWriter():
    mHeader("CPS"),
    mHeaderLength(std::strlen(mHeader) / sizeof(mHeader)),
    mVersion(0x0100)    // major and minor revisions format
{
    
}

SerializationWriter::~SerializationWriter()
{
    
}
