#ifndef PERSONALDIALOG_H
#define PERSONALDIALOG_H

#include <QDialog>

namespace Ui {
class PersonalDialog;
}

class PersonalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalDialog(QWidget *parent = 0);
    ~PersonalDialog();

private:
    Ui::PersonalDialog *ui;
};

#endif // PERSONALDIALOG_H
