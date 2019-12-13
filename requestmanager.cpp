#include "requestmanager.h"

#include <QDebug>

#include <cstdio>

using namespace std;

RequestManager::RequestManager(QObject *parent, QString header)
    : QObject(parent)
{
    m_response = "";
    m_header = header;
}

bool RequestManager::request(QUrl aUrl)
{
    m_url = aUrl;
    QNetworkRequest request(m_url);

    request.setRawHeader("Accept", m_header.toUtf8());

    m_currentDownload = m_manager.get(request);

    connect(m_currentDownload, SIGNAL(readyRead()),
            SLOT(requestReadyRead()));

    connect(m_currentDownload, SIGNAL(finished()),
            SLOT(requestFinished()));

    return true;

}

void RequestManager::requestFinished()
{
    if (m_currentDownload->error()) {
        qWarning() << "Request Error: " << m_currentDownload->errorString();
    } else {
        // check if it was a redirect
        if (isHttpRedirect()) {
            reportRedirect();
            m_response = "";

            QUrl lastUrl = m_currentDownload->request().url();

            m_currentDownload->deleteLater();
            if (lastUrl != m_url)
                request(m_url);
            return;
        }
    }

    QList<QNetworkReply::RawHeaderPair> l = m_currentDownload->rawHeaderPairs();
    int sz = l.count();
    for(int i = 0; i<sz; i++)
    {
        QNetworkReply::RawHeaderPair pair = l[i];

        if (pair.first == "Content-Type")
        {
            QString responseHeader = pair.second;

            if (!((m_header.contains("json", Qt::CaseInsensitive) && responseHeader.contains("json", Qt::CaseInsensitive)) ||
                (m_header.contains("xml", Qt::CaseInsensitive) && responseHeader.contains("xml", Qt::CaseInsensitive))))
                m_response = "MT Agent does not support request protocol " + m_header;
            break;
        }
    }

    m_currentDownload->deleteLater();
    emit finished();
}

void RequestManager::requestReadyRead()
{
    m_response += m_currentDownload->readAll();
}

bool RequestManager::isHttpRedirect() const
{
    int statusCode = m_currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void RequestManager::reportRedirect()
{
    int statusCode = m_currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QUrl requestUrl = m_currentDownload->request().url();
    qWarning() << "Request: " << requestUrl.toDisplayString()
                        << " was redirected with code: " << statusCode;

    QVariant target = m_currentDownload->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!target.isValid())
        return;

    QUrl redirectUrl = target.toUrl();
    if (redirectUrl.isRelative())
        redirectUrl = requestUrl.resolved(redirectUrl);

    qWarning() << "Redirected to: " << redirectUrl.toDisplayString();

    m_url = redirectUrl;
}
