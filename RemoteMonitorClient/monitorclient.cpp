#include "monitorclient.h"
#include "ui_monitorclient.h"

MonitorClient::MonitorClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MonitorClient)
{
    ui->setupUi(this);
}

MonitorClient::~MonitorClient()
{
    delete ui;
}
