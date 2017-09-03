#ifndef PARTITIONKEYS_H
#define PARTITIONKEYS_H

#include <QString>

namespace PartitionKeys
{
    QString getPartitionIDFromType(int type);
    QString getVolumeStatus(int status);
}

#endif // PARTITIONKEYS_H
