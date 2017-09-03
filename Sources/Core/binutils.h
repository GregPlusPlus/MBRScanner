#ifndef BINUTILS_H
#define BINUTILS_H

#include <QByteArray>

namespace BinUtils
{
    enum Endianness{
        Little_Endianness,
        Big_Endianness
    };

    uint32_t changeEndianness(uint32_t value);
    uint32_t get32BitNumberFromArray(const QByteArray &array, int start, Endianness endianess);
}

#endif // BINUTILS_H
