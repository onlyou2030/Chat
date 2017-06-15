#include "monitor.h"
#include "ui_monitor.h"

Monitor::Monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);
}

Monitor::~Monitor()
{
    delete ui;
}
