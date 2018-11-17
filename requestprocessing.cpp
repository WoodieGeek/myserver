#include "requestprocessing.h"

RequestProcessing::RequestProcessing(qintptr socket_id, QString* filmsData, QString* channelsData)
    : Socket_id(socket_id)
    , FilmsData(filmsData)
    , ChannelsData(channelsData)
{
    qDebug() << "clinet id = " <<  socket_id;
}

QString RequestProcessing::GetUri(const QString& body_http) {
    int index = body_http.indexOf("GET") + 4;
    QString uri;
    while (index < body_http.size() && body_http[index] != ' ') {
        uri.append(body_http[index]);
        index++;
    }
    return uri;
}

void RequestProcessing::ChannelsHandle() {
    QString responce = "HTTP/1.1 200 OK\r\n\r\n%1";
    Socket->write(responce.arg(*ChannelsData).toLocal8Bit());
}

void RequestProcessing::FilmsHandle() {
    QString responce = "HTTP/1.1 200 OK\r\n\r\n%1";
    Socket->write(responce.arg(*FilmsData).toLocal8Bit());
}
void RequestProcessing::Responce() {

    for ( int i = 0; i < 1e9; i++) {}
    QString uri = GetUri(Socket->readAll());
    qDebug() << "uri = " << uri;
    if (uri == "/channels.json") {
        ChannelsHandle();
    }
    else if (uri == "/films.json") {
        FilmsHandle();
    }
    else {
        QString responce = "HTTP/1.1 404 \r\n\r\nBad request";
        Socket->write(responce.toLocal8Bit());
    }
    Socket->disconnectFromHost();
}

void RequestProcessing::run() {
    Socket = new QTcpSocket();
    Socket->setSocketDescriptor(Socket_id);
    Socket->waitForReadyRead(1000);
    Responce();
    Socket->waitForBytesWritten(1000);

    Socket->close();
    Socket->deleteLater();

}

RequestProcessing::~RequestProcessing() {

}
