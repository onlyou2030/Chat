#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTimer>
#include <QMap>

namespace Ui {
class TcpServer;
}

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

    bool checkSignIn(QString name,QString passward);
    bool checkSignUp(QString name,QString passward);

signals:
    void userNumChange();

private slots:
    void on_startBtn_clicked();

    void acceptConnection();

    void receiveData();

    void removeUserFormList();

    void sendUserList();

private:
    Ui::TcpServer *ui;
    //QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
    //QList<QTcpSocket *> userList;
    QMap<QTcpSocket *,QString> userMessage;
};

#endif // TCPSERVER_H
