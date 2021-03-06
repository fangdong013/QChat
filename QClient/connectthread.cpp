#include "connectthread.h"

ConnectThread::ConnectThread(int socketDescriptor, QObject *parent):
    QThread(parent),
    socketDescriptor(socketDescriptor),
    runThread(true),
    userID(0),
    tcpMsg(new TcpSocketMsg(this))
{
    connect (tcpMsg, &TcpSocketMsg::disconnected, this, &ConnectThread::disconnect);
    connect (tcpMsg, &TcpSocketMsg::readyRead, this, &ConnectThread::threadReadyRead);
    if (!tcpMsg->setSocketDescriptor (socketDescriptor)) {
        emit error (tcpMsg->error ());
        return;
    }
}

ConnectThread::ConnectThread(const QString &address, quint16 port, quint32 userID, QObject *parent):
    QThread(parent),
    socketDescriptor(0),
    runThread(true),
    userID(userID),
    tcpMsg(new TcpSocketMsg(this))
{

    tcpMsg->connectToHost (QHostAddress(address), port);
    tcpMsg->setBlockSize (0);
    connect (tcpMsg, &TcpSocketMsg::disconnected, this, &ConnectThread::disconnect);
    connect (tcpMsg, &TcpSocketMsg::readyRead, this, &ConnectThread::threadReadyRead);
    connect (tcpMsg, &TcpSocketMsg::connected, this, &ConnectThread::connectSuccess);
//    connect (tcpMsg, &TcpSocketMsg::connected, this, &ConnectThread::d);
}

void ConnectThread::run()
{
    while (runThread) {
    }
    if (tcpMsg) {
        if (tcpMsg->state () != TcpSocketMsg::ConnectedState) {
            tcpMsg->disconnectFromHost ();
            tcpMsg->waitForDisconnected();
        }
        tcpMsg->deleteLater ();
    }
}

void ConnectThread::stop()
{
    runThread = false;
}

void ConnectThread::setUserID(quint32 id)
{
    userID = id;
}

quint32 ConnectThread::getUserID()
{
    return userID;
}

void ConnectThread::threadReadyRead()
{
    Message *msg = tcpMsg->read ();
    if (msg == nullptr) return;
    emit newMsg (this, msg);
}


void ConnectThread::disconnect()
{
    emit loseConnect (this);
}

void ConnectThread::connectSuccess()
{
    emit setUpCommunication (this);
}

void ConnectThread::sendMsg(ConnectThread *thread, Message *msg)
{
    if (thread != this) return;
    tcpMsg->send (msg);
}

