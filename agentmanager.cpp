#include <QSettings>
#include "agentmanager.h"

AgentManager AgentManager::agentManager;

AgentManager::AgentManager()
{
}


AgentManager::~AgentManager()
{
    removeAll();
}

void AgentManager::removeAll()
{
    for (map<string, AgentInfo*>::iterator it = agentList.begin(); it != agentList.end(); ++it)
    {
        AgentInfo *agent = it->second;
        delete agent;
    }

    agentList.clear();
}

unsigned long AgentManager::count()
{
    return agentList.size();
}

bool AgentManager::find(const string &id)
{
    map<string, AgentInfo*>::iterator i = agentList.find(id);

    if (i != agentList.end())
        return true;

    return false;
}


AgentInfo *AgentManager::search(const string &id)
{
    map<string, AgentInfo*>::iterator i = agentList.find(id);

    if (i != agentList.end())
        return i->second;

    return nullptr;
}

AgentInfo* AgentManager::add(const string &id, const string &url, const string &comment)
{
    if (find(id))
        return nullptr;

    AgentInfo *agent = new AgentInfo(id, url, comment);
    agentList.insert(make_pair(id, agent));
    return agent;
}

bool AgentManager::remove(const string &id)
{
    map<string, AgentInfo*>::iterator i = agentList.find(id);

    if (i == agentList.end())
        return false;

    AgentInfo *agent = i->second;
    delete agent;

    agentList.erase(i);
    return true;
}


bool AgentManager::backup()
{
    QSettings settings("MTConnect", "MTExplorer");
    settings.beginWriteArray("Agents");

    int i = 0;
    for (map<string, AgentInfo*>::iterator it = agentList.begin(); it != agentList.end(); ++it, i++)
    {
        AgentInfo *agent = it->second;

        string id = it->first;
        string url = agent->url;
        string comment = agent->comment;

        settings.setArrayIndex(i);
        settings.setValue("id", id.c_str());
        settings.setValue("url", url.c_str());
        settings.setValue("comment", comment.c_str());
    }
    settings.endArray();
    return true;
}

bool AgentManager::restore()
{
    QSettings settings("MTConnect", "MTExplorer");

    agentList.clear();
    int size = settings.beginReadArray("Agents");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);

        string id = settings.value("id").toString().toStdString();
        string url = settings.value("url").toString().toStdString();
        string comment = settings.value("comment").toString().toStdString();

        agentList.insert(make_pair(id, new AgentInfo(id, url, comment)));
    }
    settings.endArray();

    return true;
}
