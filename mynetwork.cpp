#include "mynetwork.h"

#include <QChar>
#include <QByteArray>
#include <QDebug>
#include <QThread>

myNetwork::myNetwork(QObject *parent):QObject(parent){
    connected_flag=false;
    server=NULL;
    socket=NULL;
}

QHostAddress myNetwork::getIpAddress(){
    QList<QHostAddress> list_=QNetworkInterface::allAddresses();
    for (int i=0;i<list_.size();++i){
        if (!list_.at(i).isLoopback()){
            if (list_.at(i).protocol()==QAbstractSocket::IPv4Protocol){
                return list_.at(i);
            }
        }
    }
}

void myNetwork::setUpServer(){
    qDebug()<<"void myNetwork::setUpServer()";
    qDebug()<<"Thread of network:"<<QThread::currentThreadId();
    server=new QTcpServer(this);
    server->listen(getIpAddress());
    connect(server,SIGNAL(newConnection()),
            this,SLOT(actionOfConnectedServer()));
    emit serverSetUp(server->serverAddress(),server->serverPort());
}

void myNetwork::actionOfConnectedServer(){
        socket=server->nextPendingConnection();
        connected_flag=true;
        connect(socket,SIGNAL(readyRead()),
                this,SLOT(readData()));
        connect(socket,SIGNAL(disconnected()),
                this,SIGNAL(disconnected()));
        emit connected();
}

void myNetwork::setUpClient(QHostAddress address_,int port_){
    socket=new QTcpSocket(this);
    socket->connectToHost(address_,port_);
    connect(socket,SIGNAL(connected()),
            this,SLOT(actionOfConnectedClient()));
    emit clientSetUp(socket->localAddress(),socket->localPort());
}

void myNetwork::actionOfConnectedClient(){
    connected_flag=true;
    connect(socket,SIGNAL(readyRead()),
            this,SLOT(readData()));
    connect(socket,SIGNAL(disconnected()),
            this,SIGNAL(disconnected()));
    emit connected();
}

void myNetwork::readData(){
    QByteArray ba=socket->readAll();
    char *data_=ba.data();
    QString string_="";
    while (*data_){
        string_+=QChar(*data_);
        ++data_;
    }
    if (string_.size()){
        emit dataRead(string_);
    }
}

void myNetwork::writeData(const QString &data_){
    QByteArray ba;
    ba.clear();
    ba.append(data_);
    socket->write(ba);
    emit dataWritten();
}
