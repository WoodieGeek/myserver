#include "server.h"

Server::Server(QObject* parent) : QTcpServer(parent) {
    QFile fileChannels("channels.json");
    fileChannels.open(QIODevice::ReadOnly | QIODevice::Text);
    ChannelsData = fileChannels.readAll();
    fileChannels.close();
    QFile fileFilms("films.json");
    fileFilms.open(QIODevice::ReadOnly | QIODevice::Text);
    FilmsData = fileFilms.readAll();
    fileFilms.close();
    ThreadPool = new QThreadPool(this);
}

Server::~Server() {
}

void Server::StartServer() {
    QHostAddress localhost("127.0.0.1");
    if (this->listen(localhost, PORT)) {
        qDebug() << "Listening";
    }
    else {
        qDebug() << "Server not started";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    RequestProcessing* requestProcessing = new RequestProcessing(socketDescriptor, &FilmsData, &ChannelsData);
    ThreadPool->start(requestProcessing);
}
