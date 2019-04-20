#include <QUrl>
#include "agentdialog.h"
#include "ui_agentdialog.h"

#include "agentmanager.h"

using namespace std;

AgentDialog::AgentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentDialog)
{
    ui->setupUi(this);

    QPalette palette = ui->status->palette();
    palette.setColor(ui->status->foregroundRole(), Qt::red);
    ui->status->setPalette(palette);

    ui->id->installEventFilter(this);
    ui->url->installEventFilter(this);
}

AgentDialog::~AgentDialog()
{
    delete ui;
}

void AgentDialog::done(int result)
{
    if(QDialog::Accepted == result)  // ok was pressed
    {
        id = trim(ui->id->text().toStdString());
        url = trim(ui->url->text().toStdString());
        comment = trim(ui->comment->text().toStdString());

        if (id.length() == 0)
        {
            ui->status->setText("Invalid Agent ID");
            return;
        }

        if (url.length() == 0)
        {
            ui->status->setText("Enter agent's URL address");
            return;
        }

        QUrl qinput(url.c_str(), QUrl::StrictMode);
        if (!qinput.isValid())
        {
            ui->status->setText("Agent's URL is not valid!");
            return;
        }

        QString title = windowTitle();

        if (title == "New Agent Info" && AgentManager::agentManager.find(id))
        {
            ui->status->setText("Agent ID is already in use!");
            return;
        }

        QDialog::done(result);
    }
    else    // cancel, close or exc was pressed
    {
        QDialog::done(result);
        return;
    }
}

void AgentDialog::setFields(string id, string url, string comment)
{
    setWindowTitle("Update Agent Info");

    ui->id->setText(id.c_str());
    ui->url->setText(url.c_str());
    ui->comment->setText(comment.c_str());
}

bool AgentDialog::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
        ui->status->setText("");
    return false;
}

string AgentDialog::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}
