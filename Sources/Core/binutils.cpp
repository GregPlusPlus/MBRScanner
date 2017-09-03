#include "binutils.h"

uint32_t BinUtils::changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

uint32_t BinUtils::get32BitNumberFromArray(const QByteArray &array, int start, BinUtils::Endianness endianess)
{
    uint32_t result = 0;
    uint8_t *bytes = new uint8_t[4];

    for(int i = start ; i < start + 4 ; i++)
    {
        bytes[i - start] = (uint8_t)array.at(i);
    }
    memcpy(&result, bytes, sizeof(uint32_t));

    delete bytes;

    if(endianess == BinUtils::Big_Endianness)
    {
        result = BinUtils::changeEndianness(result);
    }

    return result;
}
