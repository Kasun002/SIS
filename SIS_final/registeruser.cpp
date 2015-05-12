#include "registeruser.h"
#include "ui_registeruser.h"

registerUser::registerUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerUser)
{
    ui->setupUi(this);
}

registerUser::~registerUser()
{
    delete ui;
}
