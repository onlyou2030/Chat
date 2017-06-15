#include "personaldialog.h"
#include "ui_personaldialog.h"

PersonalDialog::PersonalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalDialog)
{
    ui->setupUi(this);
}

PersonalDialog::~PersonalDialog()
{
    delete ui;
}
