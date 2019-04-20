#include <iostream>
#include <QDebug>

#include "agentinfo.h"

AgentInfo::AgentInfo(string aId, string aUrl, string aComment)
{
    id = aId;
    url = aUrl;
    comment = aComment;
}

void AgentInfo::addDevice(DeviceInfo *device)
{
    deviceList.push_back(device);
}

DeviceInfo* AgentInfo::addDevice(string deviceId, string deviceName, string deviceUUID)
{
    DeviceInfo* device = new DeviceInfo(url, deviceId, deviceName, deviceUUID);
    addDevice(device);
    return device;
}

void AgentInfo::dump()
{
    cout << "url = [" << url << "]" << endl;
    cout << "comment = [" << comment << "]" << endl;

    cout << "# of devices = " << deviceList.size() << endl;

    list<DeviceInfo*>::iterator it = deviceList.begin();

    while (it != deviceList.end())
    {
        DeviceInfo *device = *it;

        device->dump();

        delete device;
        ++it;
    }
}

AgentInfo::~AgentInfo()
{
    qDebug() << "Delete Agent [" << QString(id.c_str()) << "]";

    if (deviceList.size() == 0)
        return;

    list<DeviceInfo*>::iterator it = deviceList.begin();

    while (it != deviceList.end())
    {
        DeviceInfo *device = *it;

        delete device;
        ++it;
    }
}
