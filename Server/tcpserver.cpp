#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "mysql.h"

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    this->tcpServer=new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(this,SIGNAL(userNumChange()),this,SLOT(sendUserList()));
}

TcpServer::~TcpServer()
{
    delete ui;
}


void TcpServer::receiveData()
{
    QTcpSocket *tempTcp=static_cast<QTcpSocket*>(sender());
    QString data=tempTcp->readAll();
    qDebug()<<data;
    QStringList list=data.split("#");
    bool ret=0;
    if(list[0]=="a")     //注册
        ret=checkSignUp(list[1],list[2]);
    else if(list[0]=="b")  //登录
    {
        ret=checkSignIn(list[1],list[2]);
        if (ret)
        {
            userMessage.insert(tempTcp,list[1]);
            connect(tempTcp,SIGNAL(disconnected()),this,SLOT(removeUserFormList()));
        }
    }
    else if(list[0]=="c")
    {
        QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
        QString message="c#"+list[1]+"#"+list[2];
        while(it!=userMessage.end())
        {
            QTcpSocket *tcp=it.key();
            if(tcp!=tempTcp)
                tcp->write(message.toLatin1());
            ++it;
        }
        return;
    }
    else if(list[0]=="d")
    {
        //userMessage[list[2]]->write(list[1]+"#"+list[3]);
        QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
        QTcpSocket *tcp=NULL;
        while(it!=userMessage.end())
        {
            if(it.value()==list[2])
            {
                tcp=it.key();
                break;
            }
            ++it;
        }
        if(tcp==NULL)
            return;
        QString mes="e#"+list[1]+"#"+list[2]+"#"+list[3];
        tcp->write(mes.toLatin1());
        return;
    }
    else if(list[0]=="e")
    {
        emit sendUserList();
        return;
    }
    else
        return;
    QString sendData=list[0];
    if(ret)
        sendData+="#"+list[1]+"#true";
    else
        sendData+="#"+list[1]+"#false";
    tempTcp->write(sendData.toLatin1());
}

void TcpServer::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    if(!tcpServer->listen(QHostAddress::Any,8000))
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
}


void TcpServer::acceptConnection()
{
    QTcpSocket *tcp=tcpServer->nextPendingConnection();
    //QString ip=tcp->peerAddress().toString();
    //qDebug()<<ip;
    connect(tcp,SIGNAL(readyRead()),this,SLOT(receiveData()));   //**********
}

/*
void TcpServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}*/



bool TcpServer::checkSignIn(QString name,QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->loguser(name,passward);
    if(ret)
    {
        ui->listWidget->addItem(name);
    }
    return ret;
}

bool TcpServer::checkSignUp(QString name, QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->signup(name,passward);
    return ret;
}


void TcpServer::removeUserFormList()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QString name=userMessage[socket];
    QList<QListWidgetItem*> list;
    list=ui->listWidget->findItems(name,Qt::MatchCaseSensitive);
    QListWidgetItem *sel=list[0];
    int r=ui->listWidget->row(sel);
    QListWidgetItem *item=ui->listWidget->takeItem(r);
    ui->listWidget->removeItemWidget(item);
    delete item;


    userMessage.remove(socket);
    emit userNumChange();
}


void TcpServer::sendUserList()
{
    QString message="d";
    QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
    while(it!=userMessage.end())
    {
        message+="#";
        message+=it.value();
        ++it;
    }
    if(message=="d")
        return;
    it=userMessage.begin();
    while(it!=userMessage.end())
    {
        it.key()->write(message.toLatin1());
        ++it;
    }
    //qDebug()<<message;
}
