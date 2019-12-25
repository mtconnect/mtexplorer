#include <QXmlQuery>
#include <QtDebug>
#include <QDomDocument>

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "agentdialog.h"
#include "agentmanager.h"
#include "requestmanager.h"
#include "xmlsyntaxhighlighter.h"


// todo:
// android - splitter does not seem to work
// all - support json display

using namespace std;

static const char *PROMPTMSG = "[Press Ins or + to add new Agent Info]";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    setUnifiedTitleAndToolBarOnMac(true);
    m_requestHeader = QString("text/xml");

    m_ui->setupUi(this);
    m_ui->agentDeviceTree->clear();

    m_lastSelectedDevice = nullptr;

    initXMLTextEdit(m_ui->textProbe);
    initXMLTextEdit(m_ui->textCurrent);
    initXMLTextEdit(m_ui->textSample);

    QTreeWidget *agentDeviceTree = m_ui->agentDeviceTree;
    agentDeviceTree->installEventFilter(this);
    agentDeviceTree->sortByColumn(0, Qt::AscendingOrder); // column/order to sort by
    agentDeviceTree->setSortingEnabled(true);             // should cause sort on add

    // Set the splitter position to minimize the tree display
    QSize size = this->size();
    int windowWidth = size.width();

    QFontMetrics metrics(agentDeviceTree->font());

    // mininum width is 15 characters + some margin
    int treeWidth = metrics.horizontalAdvance("MMMMMMMMMMMMMMM") + 25;

    QList<int> division;

    division.append(treeWidth);
    division.append(windowWidth - treeWidth);

    m_ui->splitter->setSizes(division);

    // restore previous agent info
    AgentManager::agentManager.restore();
    map<string, AgentInfo*> &agentList = AgentManager::agentManager.getList();

    if (agentList.size() == 0)
    {
        QTreeWidgetItem *agents = new QTreeWidgetItem(agentDeviceTree);
        agents->setText(0, tr(PROMPTMSG));
    }
    else {
        for (map<string, AgentInfo*>::iterator it = agentList.begin(); it != agentList.end(); ++it)
        {
            AgentInfo *agent = it->second;

            string id = it->first;
            string url = agent->url;
            string comment = agent->comment;

            QTreeWidgetItem *item = new QTreeWidgetItem(agentDeviceTree);
            item->setText(0, tr(id.c_str()));

            displayDevices(item, agent);
        }
    }
 }

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAdd_triggered()
{
    AgentDialog w;

    int ret = w.exec();

    if (ret == QDialog::Accepted)
    {
        string id = w.id;
        string url = w.url;
        string comment = w.comment;

        AgentInfo *agent = AgentManager::agentManager.add(id, url, comment);
        if (agent != nullptr)
        {
            if (AgentManager::agentManager.count() == 1)
                m_ui->agentDeviceTree->clear();

            QTreeWidgetItem *item = new QTreeWidgetItem(m_ui->agentDeviceTree);
            item->setText(0, tr(id.c_str()));

            // show all the devices
            displayDevices(item, agent);

            AgentManager::agentManager.backup();
        }
    }
}

void MainWindow::on_actionRemove_triggered()
{
    QTreeWidget *agentDeviceTree = m_ui->agentDeviceTree;
    QList<QTreeWidgetItem*> list = agentDeviceTree->selectedItems();
    QList<QTreeWidgetItem*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i)
    {
        QTreeWidgetItem* item = *i;

        if (item->parent() == nullptr)
        {
            string agent = item->text(0).toStdString();

            if (agent.compare(PROMPTMSG))
            {
                string message = "Remove Agent " + agent + "?";

                int ret = QMessageBox::warning(this, tr("Warning"),
                                               tr(message.c_str()), QMessageBox::Yes|QMessageBox::No);

                if (ret == QMessageBox::Yes &&
                        AgentManager::agentManager.remove(agent) == true)
                {
                    // reset device display info regardless if it belongs to this agent
                    clearAllDeviceInfo();

                    QTreeWidgetItem *top = agentDeviceTree->invisibleRootItem();

                    if (top != nullptr)
                    {
                        top->removeChild(item);
                        delete item;
                    }

                    if (AgentManager::agentManager.count() == 0)
                    {
                         QTreeWidgetItem *agents = new QTreeWidgetItem(agentDeviceTree);
                        agents->setText(0, tr(PROMPTMSG));
                    }
                    AgentManager::agentManager.backup();
                }
            }
        }
    }
}

void MainWindow::on_actionModify_triggered()
{
    QTreeWidget *agentDeviceTree = m_ui->agentDeviceTree;
    QList<QTreeWidgetItem*> list = agentDeviceTree->selectedItems();
    QList<QTreeWidgetItem*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i)
    {
        QTreeWidgetItem* item = *i;

        if (item->parent() == nullptr)
        {
            // modify agent info
            string agentId = item->text(0).toStdString();

            if (agentId.compare(PROMPTMSG) == 0)
            {
                on_actionAdd_triggered();
                return;
            }

            modifyAgentDef(item);
            break;
        }
        else {
            // display device info
            showDeviceInfo(item);
            m_lastSelectedDevice = item;
        }
    }
}


void MainWindow::on_actionHide_Panel_triggered()
{
    static int lastWindowWidth = 0;

    int treeWidth = 0;

    if (m_ui->actionHide_Panel->isChecked())
    {
        // save the current panel width
        lastWindowWidth = m_ui->agentDeviceTree->size().width();
        treeWidth = 0;
    }
    else
        treeWidth = lastWindowWidth;

    QSize size = this->size();
    int windowWidth = size.width();

    QList<int> division;

    division.append(treeWidth);
    division.append(windowWidth - treeWidth);
    m_ui->splitter->setSizes(division);
}

void MainWindow::on_actionRefresh_triggered()
{
    // refresh the display
    showDeviceInfo(m_lastSelectedDevice);
}

void MainWindow::on_actionHTML_triggered()
{
    m_ui->actionHTML->setChecked(true);
    m_ui->actionXML->setChecked(false);
    m_ui->actionJSON->setChecked(false);

    // refresh the display
    m_requestHeader = QString("text/xml");
    showDeviceInfo(m_lastSelectedDevice);
}

void MainWindow::on_actionXML_triggered()
{
    m_ui->actionHTML->setChecked(false);
    m_ui->actionXML->setChecked(true);
    m_ui->actionJSON->setChecked(false);

    // refresh the display
    m_requestHeader = QString("text/xml");
    showDeviceInfo(m_lastSelectedDevice);
}

void MainWindow::on_actionJSON_triggered()
{
    m_ui->actionHTML->setChecked(false);
    m_ui->actionXML->setChecked(false);
    m_ui->actionJSON->setChecked(true);

    // refresh the display
    m_requestHeader = QString("application/json");
    showDeviceInfo(m_lastSelectedDevice);
}

void MainWindow::on_actionZoom_In_triggered()
{
    resizeFont(1.1);
}

void MainWindow::on_actionZoom_Out_triggered()
{
    resizeFont(0.9);
}

void MainWindow::on_actionAbout_MTExplorer_triggered()
{
    QString about = "MTExplorer is an Open Source Project for MTConnect\n\n";

    about += "Repo: https://github.com/mtconnect/mtexplorer\n";
    about += "Author: Simon Yeung / syeung1111@gmail.com\n";
    about += "Version: " + QString(MTEXPLORER_VERSION) + "\n";
    about += "Build Time: " + QString(__DATE__) + QString(" ") + QString(__TIME__);

    QMessageBox::about(this, "About MTExplorer", about);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    qDebug() << "eventFilter is called: " << event->type() << " " << target->objectName();

    if (isSwipeEvent(target, event))
        return true;

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent * keyEvent = static_cast<QKeyEvent*>(event);

        qDebug() << "   Key event - " << keyEvent->key();

        switch (keyEvent->key()) {
        case Qt::Key_Delete:
        case Qt::Key_Backspace:
        case Qt::Key_Minus:
            on_actionRemove_triggered();
            return true;
        case Qt::Key_Insert:
        case Qt::Key_Plus:
            on_actionAdd_triggered();
            return true;
        case Qt::Key_Return:
            on_actionModify_triggered();
            return true;
        }

    }
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        // Double-clicked
        showDeviceInfo(m_lastSelectedDevice);
        return true;
    }
    else if (event->type() == QEvent::Gesture)
    {
        QGestureEvent * guestEvent = static_cast<QGestureEvent*>(event);

        if (QGesture *pinch = guestEvent->gesture(Qt::PinchGesture)) {

            QPinchGesture *pinchGesture = static_cast<QPinchGesture *>(pinch);

            qDebug() << "   Pinch gesture event " << pinchGesture->scaleFactor();
            resizeFont(pinchGesture->scaleFactor());

            return true;
        }
    }


    return false;
}

bool MainWindow::isSwipeEvent(QObject *target, QEvent *event)
{
    if (event->type() != QEvent::MouseButtonPress &&
           event->type() != QEvent::MouseButtonRelease)
        return false;

    static bool Start = false;
    static int xpos_start = 0;
    static QElapsedTimer timer;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if((event->type() == QEvent::MouseButtonPress) && (Start == false))
    {
        Start = true;
        timer.restart();
        xpos_start = mouseEvent->pos().x();
    }
    else if((event->type() == QEvent::MouseButtonRelease) && (Start == true))
    {
        int xpos = mouseEvent->pos().x();
        int diff_xpos = xpos_start-xpos;
        qint64 mSec = timer.elapsed();

        Start = false;

        qDebug() << "time: " << mSec << "  distance: " << diff_xpos;

        // 300 pixels typical 200 ms
        if ((abs(diff_xpos) > 300) && (mSec < 200))
        {
            if (diff_xpos < 0)
            {
                // swipe right
                m_ui->actionHide_Panel->setChecked(false);
                on_actionHide_Panel_triggered();
            }
            else {
                // swipe left
                m_ui->actionHide_Panel->setChecked(true);
                on_actionHide_Panel_triggered();
            }
        }
        return true;
    }

    return false;
}

void MainWindow::on_agentDeviceTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    on_actionModify_triggered();
}


void MainWindow::modifyAgentDef(QTreeWidgetItem *item)
{
    string id = item->text(0).toStdString();

    AgentInfo* agent = AgentManager::agentManager.search(id);

    string url = agent->url;
    string comment = agent->comment;

    if (agent == nullptr)
        return;

    AgentDialog w;

    w.setFields(id, url, comment);

    int ret = w.exec();

    if (ret == QDialog::Accepted)
    {
        if (!AgentManager::agentManager.remove(id))
            return;

        agent = AgentManager::agentManager.add(w.id, w.url, w.comment);
        if (agent == nullptr)
            return;

        if (id.compare(w.id))
        {
            // id changes, replace the one in the display
            QTreeWidget *agentDeviceTree = m_ui->agentDeviceTree;

            QTreeWidgetItem *top = agentDeviceTree->invisibleRootItem();

            if (top != nullptr)
            {
                top->removeChild(item);
                delete item;
            }
            item = new QTreeWidgetItem(m_ui->agentDeviceTree);
            item->setText(0, tr(w.id.c_str()));
        }

        // show all the devices
        displayDevices(item, agent);

        AgentManager::agentManager.backup();
    }
}

void MainWindow::displayDevices(QTreeWidgetItem *parent, AgentInfo *agent)
{
    foreach(auto i, parent->takeChildren())
        delete i;

    clearAllDeviceInfo();

    RequestManager *manager = new RequestManager(nullptr, m_requestHeader);

    string inputUrl = agent->url + "//";

    QUrl baseUrl = QUrl(inputUrl.c_str());
    QUrl probeUrl = QUrl("probe");

    QUrl requestUrl = baseUrl.resolved(probeUrl);

    manager->request(requestUrl);

    QObject::connect(manager, &RequestManager::finished, this, [=]() { this->showDevicesInTree(manager, parent, agent); });
}

void MainWindow::showDevicesInTree(RequestManager *manager, QTreeWidgetItem *parent, AgentInfo *agent)
{
    QString response = manager->getResponse();

    // extract device information
    QXmlStreamReader reader(response);

    if (reader.readNextStartElement()) {
        if (reader.name() == "MTConnectDevices"){
            while (reader.readNextStartElement()){
                if(reader.name() == "Devices") {
                    while (reader.readNextStartElement())
                    {
                        QStringRef nodeName = reader.name();
                        if (nodeName == "Device") {
                            QString deviceId = reader.attributes().value("id").toString();
                            QString deviceName = reader.attributes().value("name").toString();
                            QString deviceUUID = reader.attributes().value("uuid").toString();

                            agent->addDevice(deviceId.toStdString(), deviceName.toStdString(), deviceUUID.toStdString());
                        }

                        reader.skipCurrentElement();
                    }
                 }
                else
                    reader.skipCurrentElement();
            }
        }
    }

    // show all the devices
    list<DeviceInfo*> deviceList = agent->getDeviceList();

    list<DeviceInfo*>::iterator it = deviceList.begin();

    while (it != deviceList.end())
    {
        DeviceInfo *device = *it;
        QTreeWidgetItem *child = new QTreeWidgetItem(parent);

        child->setText(0, tr(device->deviceName.c_str()));
        ++it;
    }

    delete manager;
}

void MainWindow::showDeviceInfo(QTreeWidgetItem *item)
{
    if (item == nullptr)
        return;

    // gather the device info and display them
    string agentId = item->parent()->text(0).toStdString();
    string deviceId = item->text(0).toStdString();

    AgentInfo *agent = AgentManager::agentManager.search(agentId);
    if (agent)
    {
        updateDeviceTab(agent, deviceId, "probe", m_ui->textProbe);
        updateDeviceTab(agent, deviceId, "current", m_ui->textCurrent);
    }
}

void MainWindow::showDeviceInfo(RequestManager *manager, AgentInfo *agent, QTextEdit *textEdit, QString formatInfo, string deviceId, string request)
{
    QString response = manager->getResponse();
    if (request.compare("current") == 0)
    {
        QRegExp rxlen("\\blastSequence\\s*=\\s*\"(\\d+)\"");
        int pos = rxlen.indexIn(response);
        if (pos > -1) {
            QString sequenceNum = rxlen.cap(1);
            long s = sequenceNum.toLong() - 1000;
            updateDeviceTab(agent, deviceId, "sample?count=1000&from="+std::to_string(s), m_ui->textSample);
        }
    }

    if (m_ui->actionXML->isChecked())
    {
        QString xmlOut;
        QDomDocument output;

        // reformat XML
        output.setContent(response);
        QTextStream stream;
        stream.setString(&xmlOut);
        output.save(stream, 4); // 4 spaces for indentation

        textEdit->setText(xmlOut);
    } else if (m_ui->actionHTML->isChecked()) {

        QUrl xslUrl = QUrl("qrc:/resources/" + formatInfo + ".xsl");
        QXmlQuery query(QXmlQuery::XSLT20);

        QString output;
        query.setFocus(response);
        query.setQuery(xslUrl);
        query.evaluateTo(&output);

        textEdit->setHtml(output);
    }
    else {
        QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());

        if (json.isEmpty())
            textEdit->setText(response);
        else
        {
            QString jsonString = json.toJson(QJsonDocument::Indented);
            textEdit->setText(jsonString);
        }
    }

    if (textEdit->toPlainText().length() == 0)
        textEdit->setText("No Data");

    delete manager;
}

void MainWindow::updateDeviceTab(AgentInfo *agent, string deviceId, string request, QTextEdit *textEdit)
{
    textEdit->clear();

    string display = "Retrieving data for " + deviceId + " ...";
    textEdit->setText(display.c_str());

    RequestManager *manager = new RequestManager(nullptr, m_requestHeader);

    string inputUrl = agent->url + "//";
    string deviceUrl = deviceId + "/" + request;
    QUrl baseUrl = QUrl(inputUrl.c_str());
    QUrl pathUrl = QUrl(deviceUrl.c_str());

    QUrl requestUrl = baseUrl.resolved(pathUrl);

    QString formatInfo = "Streams";
    if (request == "probe")
        formatInfo = "Devices";

    manager->request(requestUrl);
    QObject::connect(manager, &RequestManager::finished, this,
                     [=]() { this->showDeviceInfo(manager, agent, textEdit, formatInfo, deviceId, request); });

}

void MainWindow::initXMLTextEdit(QTextEdit *textEdit)
{
    textEdit->installEventFilter(this);
    textEdit->grabGesture(Qt::PinchGesture);

    new XmlSyntaxHighlighter(textEdit->document());
}

void MainWindow::resizeFont(double scaleFactor)
{
    QFont font = m_ui->textProbe->font();

    if ((scaleFactor < 1.0 && font.pointSize() > 5) ||
        (scaleFactor > 1.0 && font.pointSize() < 20))
    {
        font.setPointSizeF(font.pointSizeF() * scaleFactor);
        m_ui->textProbe->setFont(font);
        m_ui->textSample->setFont(font);
        m_ui->textCurrent->setFont(font);
    }
}
void MainWindow::clearAllDeviceInfo()
{
    m_ui->textProbe->setText("");
    m_ui->textSample->setText("");
    m_ui->textCurrent->setText("");

    m_lastSelectedDevice = nullptr;
}


void MainWindow::on_agentDeviceTree_itemEntered(QTreeWidgetItem *item, int column)
{
    on_actionModify_triggered();
}
