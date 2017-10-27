#ifndef RECEIVEFILE_H
#define RECEIVEFILE_H

#include <QDialog>
#include "receivefilethread.h"

namespace Ui {
class ReceiveFile;
}

class ReceiveFile : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveFile(QWidget *parent = 0);
    ~ReceiveFile();

    void initSocket(QFile *file,
                    QHostAddress address, quint16 port,
                    QHostAddress destination, quint16 destinationPort, qint64 fileSize);

private:
    Ui::ReceiveFile *ui;

    qint64 fileSize;
    ReceiveFileThread *thread;

    void updateProgress(qint64 x);
};

#endif // RECEIVEFILE_H