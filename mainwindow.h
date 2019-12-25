#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QXmlQuery>

#include "agentinfo.h"
#include "requestmanager.h"

#define MTEXPLORER_VERSION "1.1.1"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:
    void on_actionQuit_triggered();
    void on_actionAdd_triggered();
    void on_actionRemove_triggered();
    void on_actionHide_Panel_triggered();

    void on_actionRefresh_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionAbout_MTExplorer_triggered();

    void on_actionHTML_triggered();
    void on_actionXML_triggered();
    void on_actionJSON_triggered();

    void on_agentDeviceTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_agentDeviceTree_itemEntered(QTreeWidgetItem *item, int column);

private:
    void on_actionModify_triggered();
    void modifyAgentDef(QTreeWidgetItem *item);
    void displayDevices(QTreeWidgetItem *parent, AgentInfo *agent);
    void showDevicesInTree(RequestManager *manager, QTreeWidgetItem *parent, AgentInfo *agent);
    void showDeviceInfo(QTreeWidgetItem *item);
    void showDeviceInfo(RequestManager *manager, AgentInfo *agent, QTextEdit *textEdit,
                        QString formatInfo, string deviceId, string request);
    void updateDeviceTab(AgentInfo *agent, string deviceId, string request, QTextEdit *textEdit);
    void initXMLTextEdit(QTextEdit *textEdit);
    void resizeFont(double scaleFactor);
    void clearAllDeviceInfo();
    void initQXmlQuery(QXmlQuery *&query, QString &styleName);

    bool eventFilter(QObject * target, QEvent * event);
    bool isSwipeEvent(QObject *target, QEvent *event);
    Ui::MainWindow *m_ui;
    QTreeWidgetItem* m_lastSelectedDevice;
    QString m_requestHeader;
};

#endif // MAINWINDOW_H
