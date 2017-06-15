#ifndef MONITORSERVER_H
#define MONITORSERVER_H

#include <QMainWindow>

namespace Ui {
class MonitorServer;
}

class MonitorServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MonitorServer(QWidget *parent = 0);
    ~MonitorServer();

private:
    Ui::MonitorServer *ui;
};

#endif // MONITORSERVER_H
