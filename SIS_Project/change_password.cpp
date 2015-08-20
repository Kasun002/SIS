#include "change_password.h"
#include "ui_change_password.h"
#include <QMessageBox>
#include <QDebug>

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
}

change_password::~change_password()
{
    delete ui;
}

void change_password::on_btn_changepass_clear_clicked()
{
    ui->txt_changepass_confirmpass->setText("");
    ui->txt_changepass_newpass->setText("");
}

void change_password::on_pushButton_2_clicked()
{
    login conn;
    QString username, password,confirmpassword ;
    username = ui->txt_changepass_uname->text();
    password = ui->txt_changepass_newpass->text();
    confirmpassword = ui->txt_changepass_confirmpass ->text();

    if(!username.isEmpty() && !password.isEmpty() && !confirmpassword.isEmpty()){

         QRegExp rxpassword("((?=.*[0-9])(?=.*[a-zA-Z])(?=.*[@#$%]).{6,20})");

        if(!rxpassword.exactMatch(password)){
            QMessageBox :: critical(this, tr("Error"), tr("Password must include these characteristics.\n 1) must contains one digit from 0-9. \n 2) must contains one lowercase | uppercase characters.\n 3) must contains one special symbols in the list '@#$%'. 4) length at least 6 characters and maximum of 20."));

        }
        else if(password != confirmpassword){

                    QMessageBox :: critical(this, tr("Error"), tr("Password comfirmation was worrong..."));
                }
        else{
        ui->lbl_change_password->setText("ok....");
        conn.connClose();

        if(conn.connOpen()){
             ui->lbl_change_password->setText("connect to DB..");

            QSqlQuery update_quary;


            //connOpen();
            update_quary.prepare("UPDATE User SET password = '"+password+"' WHERE username = '"+username+"'");

            if(update_quary.exec()){

                //int check = 0;

                qDebug() << " ok...";

                update_quary.next();
                conn.connClose();
                QMessageBox::information(this,tr("Success"),tr("Update User name & Password successfuly !"));
                conn.show();
                this->hide();

                /*
                while(update_quary.next()){
                    check ++;
                    qDebug() << " ok...";
                }

                if(check== 1){
                   // ui->lbl_login_status -> setText("Username & Password correct....");

                    QMessageBox::information(this,tr("Success"),tr("Update User name & Password successfuly !"));
                 // con_login = new controller(this);
                  conn.connClose();

                  conn.show();
                  this->hide();
                }
                    */


            }else{
                //ui->lbl_change_password->setText("wrrong quary...");
                qDebug() << "wrrong quay";
            }


        }else{
            ui->lbl_change_password->setText("DB doesn't open..");
            //qDebug() << "Fail to open DB";
            return;
        }
        }
    }else{
            QMessageBox :: critical(this, tr("Error"), tr("Complete the all the feilds..."));
        }

    }

