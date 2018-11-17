#include "requestprocessing.h"

RequestProcessing::RequestProcessing(qintptr socket_id, QSqlDatabase* db)
    : Socket_id(socket_id)
    , DB(db)
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
    QJsonArray channels_array;
    QSqlQuery* query = new QSqlQuery(*DB);
    if (query->exec("SELECT * FROM channel")) {
        while (query->next()) {
            QJsonObject channel;
            channel["name"] = query->value(1).toString();
            channel["description"] = query->value(2).toString();
            channels_array.append(channel);
        }
    }
    QJsonDocument doc;
    doc.setArray(channels_array);
    Socket->write(responce.arg(QString(doc.toJson())).toLocal8Bit());
}

void RequestProcessing::FilmsHandle() {
    QString responce = "HTTP/1.1 200 OK\r\n\r\n%1";
    QJsonArray films_array;
    QSqlQuery* query = new QSqlQuery(*DB);
    if (query->exec("SELECT * FROM films")) {
        while (query->next()) {
            QJsonObject film;
            film["title"] = query->value(1).toString();
            film["description"] = query->value(2).toString();
            film["thumbnail"] = query->value(3).toString();
            films_array.append(film);
        }
    }
    QJsonDocument doc;
    doc.setArray(films_array);
    Socket->write(responce.arg(QString(doc.toJson())).toLocal8Bit());
}
void RequestProcessing::Responce() {

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
