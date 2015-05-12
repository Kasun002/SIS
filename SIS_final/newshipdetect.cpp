#include "newshipdetect.h"
#include "ui_newshipdetect.h"

NewShipDetect::NewShipDetect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewShipDetect)
{
    ui->setupUi(this);
}

NewShipDetect::~NewShipDetect()
{
    delete ui;
}
