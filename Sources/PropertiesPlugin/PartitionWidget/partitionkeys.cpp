#include "partitionkeys.h"

QString PartitionKeys::getPartitionIDFromType(int type)
{
    switch (type) {
    case 0x01:
        return "FAT12 primary partition or logical drive";
        break;
    case 0x04:
        return "FAT16 partition or logical drive";
        break;
    case 0x05:
        return "Extended partition";
        break;
    case 0x06:
        return "BIGDOS FAT16 partition or logical drive";
        break;
    case 0x07:
        return "NTFS partition or logical drive";
        break;
    case 0x0B:
        return "FAT32 partition or logical drive";
        break;
    case 0x0C:
        return "FAT32 partition or logical drive BIOS INT 13h";
        break;
    case 0x0E:
        return "BIGDOS FAT16 partition or logical drive BIOS INT 13h";
        break;
    case 0x0F:
        return "Extended partition BIOS INT 13h";
        break;
    case 0x12:
        return "EISA partition";
        break;
    case 0x42:
        return "Dynamic disk volume";
        break;
    case 0x86:
        return "Legacy FT FAT16 disk";
        break;
    case 0x87:
        return "Legacy FT NTFS disk";
        break;
    case 0x8B:
        return "Legacy FT volume FAT32";
        break;
    case 0x8C:
        return "Legacy FT volume  BIOS INT 13h FAT32";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

QString PartitionKeys::getVolumeStatus(int status)
{
    switch (status) {
    case 0x80:
        return "Active partition";
        break;
    case 0x00:
        return "Do not use for booting";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}
