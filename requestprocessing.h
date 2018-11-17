#ifndef REQUESTPROCESSING_H
#define REQUESTPROCESSING_H
#include <QRunnable>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

class RequestProcessing : public QRunnable
{
public:
    RequestProcessing(qintptr socket_id, QSqlDatabase* db);
    ~RequestProcessing();
    void run();
private:
    QString GetUri(const QString& body_http);
    void Responce();
    void ChannelsHandle();
    void FilmsHandle();
private:
    qintptr Socket_id;
    QTcpSocket* Socket;
    QSqlDatabase* DB;
};

#endif // REQUESTPROCESSING_H
