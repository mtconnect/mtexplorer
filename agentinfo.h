#ifndef AGENTINFO_H
#define AGENTINFO_H
#include <string>
#include <list>

#include "deviceinfo.h"

using namespace std;

class AgentInfo
{
public:
    string id;
    string url;
    string comment;

private:
    list<DeviceInfo*> deviceList;

public:

    list<DeviceInfo*> &getDeviceList() { return deviceList; }
    void addDevice(DeviceInfo* device);
    DeviceInfo* addDevice(string deviceId, string deviceName, string deviceUUID);
    void dump();

    AgentInfo(string aId, string aUrl, string aComment);
    ~AgentInfo();
};

#endif // AGENTINFO_H
