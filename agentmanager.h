#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include <map>
#include <string>

#include "agentinfo.h"

using namespace std;

class AgentManager
{
private:
    map<string, AgentInfo*> agentList;

public:
    static AgentManager agentManager;

    AgentManager();  
    ~AgentManager();

    unsigned long count();
    map<string, AgentInfo*> &getList() { return agentList; }
    bool find(const string &id);
    AgentInfo* search(const string &id);
    AgentInfo* add(const string &id, const string &url, const string &comment);
    bool remove(const string &id);
    void removeAll();

    bool backup();
    bool restore();
};

#endif // AGENTMANAGER_H
