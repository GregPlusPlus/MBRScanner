#include "mbrtools.h"

int MBRTools::readDisk
(QString dsk,    // disk to access
 char *&_buff,         // buffer where sector will be stored
 unsigned int _nsect,   // sector number, starting with 0
 unsigned int _length
 )
{
#ifdef Q_OS_WIN
    DWORD dwRead;
    HANDLE hDisk=CreateFile ((LPCWSTR)dsk.toStdWString().c_str(), GENERIC_READ,
                             FILE_SHARE_READ|FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if(hDisk==INVALID_HANDLE_VALUE) // this may happen if another program is already reading from disk
    {
        CloseHandle(hDisk);

        return 1;
    }
    SetFilePointer(hDisk,_nsect*_length,0,FILE_BEGIN); // which sector to read

    ReadFile(hDisk,_buff,_length,&dwRead,0);  // read sector
    CloseHandle(hDisk);
    return 0;
#endif
}

QStringList MBRTools::getPhysicalDisks()
{
    HDEVINFO hDeviceInfoSet;
    ULONG ulMemberIndex;
    ULONG ulErrorCode;
    BOOL bOk;
    QStringList disks;

    // create a HDEVINFO with all present devices
    hDeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_DISK, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (hDeviceInfoSet == INVALID_HANDLE_VALUE) {

        return disks;
    }

    // enumerate through all devices in the set
    ulMemberIndex = 0;
    while (TRUE)
    {
        // get device info
        SP_DEVINFO_DATA deviceInfoData;
        deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        if (!::SetupDiEnumDeviceInfo(hDeviceInfoSet, ulMemberIndex, &deviceInfoData))
        {
            if (::GetLastError() == ERROR_NO_MORE_ITEMS) {
                // ok, reached end of the device enumeration
                break;
            } else {
                // error

                ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
                return disks;
            }
        }

        // get device interfaces
        SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
        deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        if (!::SetupDiEnumDeviceInterfaces(hDeviceInfoSet, NULL, &GUID_DEVINTERFACE_DISK, ulMemberIndex, &deviceInterfaceData))
        {
            if (::GetLastError() == ERROR_NO_MORE_ITEMS) {
                // ok, reached end of the device enumeration
                break;
            } else {
                // error

                ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
                return disks;
            }
        }

        // process the next device next time
        ulMemberIndex++;

        // get hardware id of the device
        ULONG ulPropertyRegDataType = 0;
        ULONG ulRequiredSize = 0;
        ULONG ulBufferSize = 0;
        BYTE *pbyBuffer = NULL;
        if (!::SetupDiGetDeviceRegistryProperty(hDeviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, &ulPropertyRegDataType, NULL, 0, &ulRequiredSize))
        {
            if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
                pbyBuffer = (BYTE *)::malloc(ulRequiredSize);
                ulBufferSize = ulRequiredSize;
                if (!::SetupDiGetDeviceRegistryProperty(hDeviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, &ulPropertyRegDataType, pbyBuffer, ulBufferSize, &ulRequiredSize))
                {
                    // getting the hardware id failed

                    ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
                    ::free(pbyBuffer);
                    return disks;
                }
            } else {
                // getting device registry property failed

                ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
                return disks;
            }
        } else {
            // getting hardware id of the device succeeded unexpectedly

            ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
            return disks;
        }

        // retrieve detailed information about the device
        // (especially the device path which is needed to create the device object)
        SP_DEVICE_INTERFACE_DETAIL_DATA *pDeviceInterfaceDetailData = NULL;
        ULONG ulDeviceInterfaceDetailDataSize = 0;
        ulRequiredSize = 0;
        bOk = ::SetupDiGetDeviceInterfaceDetail(hDeviceInfoSet, &deviceInterfaceData, pDeviceInterfaceDetailData, ulDeviceInterfaceDetailDataSize, &ulRequiredSize, NULL);
        if (!bOk)
        {
            ulErrorCode = ::GetLastError();
            if (ulErrorCode == ERROR_INSUFFICIENT_BUFFER) {
                // insufficient buffer space
                // => that's ok, allocate enough space and try again
                pDeviceInterfaceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA *)::malloc(ulRequiredSize);
                pDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
                ulDeviceInterfaceDetailDataSize = ulRequiredSize;
                deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
                bOk = ::SetupDiGetDeviceInterfaceDetail(hDeviceInfoSet, &deviceInterfaceData, pDeviceInterfaceDetailData, ulDeviceInterfaceDetailDataSize, &ulRequiredSize, &deviceInfoData);
                ulErrorCode = ::GetLastError();
            }

            if (!bOk) {
                // retrieving detailed information about the device failed

                ::free(pbyBuffer);
                ::free(pDeviceInterfaceDetailData);
                ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
                return disks;
            }
        } else {
            // retrieving detailed information about the device succeeded unexpectedly

            ::free(pbyBuffer);
            ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
            return disks;
        }

        disks.append(QString::fromWCharArray(pDeviceInterfaceDetailData->DevicePath));

        // free buffer for device interface details
        ::free(pDeviceInterfaceDetailData);

        // free buffer
        ::free(pbyBuffer);
    }

    // destroy device info list
    ::SetupDiDestroyDeviceInfoList(hDeviceInfoSet);

    return disks;
}

QStringList MBRTools::getMountedDrives()
{
    QStringList drives;
    DWORD buffSize = GetLogicalDriveStringsW(0, NULL);

    LPWSTR LPWSTRDrives = (LPWSTR)malloc(sizeof(WCHAR) * buffSize);

    GetLogicalDriveStringsW(buffSize, (LPWSTR)LPWSTRDrives);

    QString s;

    for(DWORD i = 0 ; i < buffSize ; i++)
    {

        WCHAR c = (WCHAR)LPWSTRDrives[i];
        if(c != '\00')
        {
            s.append(QChar(c));
        }
        else
        {
            if(!s.isEmpty())
            {
                drives.append(s);
            }

            s.clear();
        }
    }

    free(LPWSTRDrives);

    return drives;
}
