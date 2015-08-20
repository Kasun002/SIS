#include "di0alog_add.h"
#include "ui_di0alog_add.h"

Di0alog_add::Di0alog_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Di0alog_add)
{
    ui->setupUi(this);
}

Di0alog_add::~Di0alog_add()
{
    delete ui;
}
