#include "registeruser.h"
#include "ui_registeruser.h"

registeruser::registeruser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registeruser)
{
    ui->setupUi(this);
}

registeruser::~registeruser()
{
    delete ui;
}
