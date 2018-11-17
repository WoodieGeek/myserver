#ifndef SERVER_H
#define SERVER_H

#include "requestprocessing.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QFile>
#include <QThreadPool>
#include <QSqlDatabase>
#include <QSqlQuery>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);
    ~Server();

    QTcpSocket* Socket;
    QByteArray Data;
    void incomingConnection(qintptr socketDescriptor);
public slots:
    void StartServer();
private:
    QString ChannelsData;
    QString FilmsData;
    QThreadPool* ThreadPool;
    quint16 PORT = 8001;
    QSqlDatabase DB;
};

#endif // SERVER_H
