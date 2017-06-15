#ifndef MONITORCLIENT_H
#define MONITORCLIENT_H

#include <QMainWindow>

namespace Ui {
class MonitorClient;
}

class MonitorClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit MonitorClient(QWidget *parent = 0);
    ~MonitorClient();

private:
    Ui::MonitorClient *ui;
};

#endif // MONITORCLIENT_H
