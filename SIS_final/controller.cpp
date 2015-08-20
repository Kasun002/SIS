#include "controller.h"
#include "ui_controller.h"

controller::controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controller)
{
    ui->setupUi(this);
}

controller::~controller()
{
    delete ui;
}
