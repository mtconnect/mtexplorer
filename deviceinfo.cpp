#include <iostream>
#include <QDebug>

#include "deviceinfo.h"

void DeviceInfo::dump()
{
    cout << "Device - " << deviceId << endl;
    if (metaData.size() > 0)
        cout << "     Definition = [" << metaData << "]" << endl;

    if (current.size() > 0)
        cout << "     Current Data = [" << current << "]" << endl;

    if (sample.size() > 0)
        cout << "     Sample = [" << sample << "]" << endl;
}

DeviceInfo::~DeviceInfo()
{
    qDebug() << "Delete device [" << QString(deviceId.c_str()) << "]";
}
