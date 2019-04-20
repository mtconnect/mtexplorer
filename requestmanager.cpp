#include "requestmanager.h"

#include <QDebug>

#include <cstdio>

using namespace std;

RequestManager::RequestManager(QObject *parent)
    : QObject(parent)
{
    response = "";
}

bool RequestManager::request(QUrl aUrl)
{
    url = aUrl;
    QNetworkRequest request(url);
    currentDownload = manager.get(request);

    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(requestReadyRead()));

    connect(currentDownload, SIGNAL(finished()),
            SLOT(requestFinished()));

    return true;

}

void RequestManager::requestFinished()
{
    if (currentDownload->error()) {
        qWarning() << "Request Error: " << currentDownload->errorString();
    } else {
        // check if it was a redirect
        if (isHttpRedirect()) {
            reportRedirect();
            response = "";

            QUrl lastUrl = currentDownload->request().url();

            currentDownload->deleteLater();
            if (lastUrl != url)
                request(url);
            return;
        }
    }

    currentDownload->deleteLater();
    emit finished();
}

void RequestManager::requestReadyRead()
{
    response += currentDownload->readAll();
}

bool RequestManager::isHttpRedirect() const
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void RequestManager::reportRedirect()
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QUrl requestUrl = currentDownload->request().url();
    qWarning() << "Request: " << requestUrl.toDisplayString()
                        << " was redirected with code: " << statusCode;

    QVariant target = currentDownload->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!target.isValid())
        return;

    QUrl redirectUrl = target.toUrl();
    if (redirectUrl.isRelative())
        redirectUrl = requestUrl.resolved(redirectUrl);

    qWarning() << "Redirected to: " << redirectUrl.toDisplayString();

    url = redirectUrl;
}
