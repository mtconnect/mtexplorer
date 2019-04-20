#ifndef AGENTDIALOG_H
#define AGENTDIALOG_H

#include <QDialog>
using namespace std;

namespace Ui {
class AgentDialog;
}

class AgentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AgentDialog(QWidget *parent = nullptr);
    ~AgentDialog();

public:
    string id;
    string url;
    string comment;

    void setFields(string id, string url, string comment);

private:
    bool eventFilter(QObject * target, QEvent * event);
    void done(int result);
    string trim(const string& str);

    Ui::AgentDialog *ui;
};

#endif // AGENTDIALOG_H
