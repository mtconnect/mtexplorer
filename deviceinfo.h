#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <string>

using namespace std;

class DeviceInfo
{
public:
    const string &url;
    string deviceId;
    string deviceName;
    string deviceUUID;

    string metaData;    // result from operation prob
    string current;     // result from operation current
    string sample;     // result from operation sample

public:
    void dump();

    DeviceInfo(const string &aUrl, string aDeviceId, string aDeviceName, string aDeviceUUID):
        url(aUrl),
        deviceId(aDeviceId),
        deviceName(aDeviceName),
        deviceUUID(aDeviceUUID)
    {
    }

    ~DeviceInfo();
};

#endif // DEVICEINFO_H
