#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QtNetwork>
#include <QtCore>

class RequestManager: public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = nullptr, QString header = QString("text/xml"));

    bool request(QUrl m_url);
    QString getResponse() { return m_response; }


signals:
    void finished();

private slots:
    void requestFinished();
    void requestReadyRead();

private:
    bool isHttpRedirect() const;
    void reportRedirect();

    QUrl m_url;
    QNetworkAccessManager m_manager;
    QNetworkReply *m_currentDownload = nullptr;
    QString m_response;
    QString m_header;
};

#endif
