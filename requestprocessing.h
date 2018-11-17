#ifndef REQUESTPROCESSING_H
#define REQUESTPROCESSING_H
#include <QRunnable>
#include <QTcpSocket>
#include <QTcpServer>

class RequestProcessing : public QRunnable
{
public:
    RequestProcessing(qintptr socket_id, QString* filmsData, QString* channelsData);
    ~RequestProcessing();
    void run();
private:
    QString GetUri(const QString& body_http);
    void Responce();
    void ChannelsHandle();
    void FilmsHandle();
private:
    qintptr Socket_id;
    QString* FilmsData;
    QString* ChannelsData;
    QTcpSocket* Socket;
};

#endif // REQUESTPROCESSING_H
