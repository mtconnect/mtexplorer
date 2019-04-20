#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QtNetwork>
#include <QtCore>

class RequestManager: public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = nullptr);

    bool request(QUrl url);
    QString getResponse() { return response; }


signals:
    void finished();

private slots:
    void requestFinished();
    void requestReadyRead();

private:
    bool isHttpRedirect() const;
    void reportRedirect();

    QUrl url;
    QNetworkAccessManager manager;
    QNetworkReply *currentDownload = nullptr;
    QString response;
};

#endif
