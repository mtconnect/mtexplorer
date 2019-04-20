#include "mainwindow.h"
#include <QApplication>

#include "agentmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();
    int ret = a.exec();

    AgentManager::agentManager.removeAll();

    return ret;
}
