#include "ncrtestform.h"
#include "ui_ncrtestform.h"

ncrtestform::ncrtestform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ncrtestform)
{
    ui->setupUi(this);
}

ncrtestform::~ncrtestform()
{
    delete ui;
}
