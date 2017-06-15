#include "monitorserver.h"
#include "ui_monitorserver.h"

MonitorServer::MonitorServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MonitorServer)
{
    ui->setupUi(this);
}

MonitorServer::~MonitorServer()
{
    delete ui;
}
