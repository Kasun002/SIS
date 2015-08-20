#include "cheack_register_dialogbox.h"
#include "ui_cheack_register_dialogbox.h"

cheack_register_dialogbox::cheack_register_dialogbox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cheack_register_dialogbox)
{
    ui->setupUi(this);
}

cheack_register_dialogbox::~cheack_register_dialogbox()
{
    delete ui;
}

void cheack_register_dialogbox::on_reg_check_btn_yes_clicked()
{
    this -> hide();

    register_new regnew;
    regnew.setModal(true);
    regnew.exec();

}

void cheack_register_dialogbox::on_reg_check_btn_no_clicked()
{

    this -> hide();

    login lg;
    lg.setModal(true);
    lg.exec();

}
