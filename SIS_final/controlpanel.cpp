#include "controlpanel.h"
#include "ui_controlpanel.h"

controlpanel::controlpanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controlpanel)
{
    ui->setupUi(this);
}

controlpanel::~controlpanel()
{
    delete ui;
}
