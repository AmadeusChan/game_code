#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QList>
#include <QObject>

class myNetwork:public QObject{

    Q_OBJECT

public:
    myNetwork(QObject *parent=0);
    ~myNetwork()=default;

private:
    QTcpServer *server;
    QTcpSocket *socket;
    bool connected_flag;

    QHostAddress getIpAddress();

signals:
    void serverSetUp(QHostAddress,int);
    void clientSetUp(QHostAddress,int);
    void connected();
    void disconnected();
    void dataRead(QString);
    void dataWritten();

private slots:
    void setUpServer();
    void actionOfConnectedServer();
    void setUpClient(QHostAddress address_,int port_);
    void actionOfConnectedClient();
    void readData();
    void writeData(const QString &data_);

};

#endif // MYNETWORK_H
