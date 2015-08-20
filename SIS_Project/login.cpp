#include "login.h"
#include "ui_login.h"
#include "change_password.h"
#include "controller.h"
#include "registor.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

//#include "registor.h"

#define path_db "/home/janaka/SIS_Project/DB/SIS_DB.sqlite"

QString login::public_username="";

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{

    ui->setupUi(this);
    ui->lbl_logo->setStyleSheet("background-image: url(/home/janaka/logo_4.png);");
    //db = QSqlDatabase :: addDatabase("QSQLITE");
    //db.setDatabaseName("/home/janaka/SIS_DB.sqlite");
    //QFileInfo checkFile(path_db);

    //if(checkFile.isFile()){
        if(connOpen()){
           ui->lbl_login_status->setText("[+] Connect to Database file..");
           // QDebug ()<<("Connect to Database....");
        }else{
            ui->lbl_login_status->setText("[-]Connect to Database file does not exit..");
            // QDebug ()<<("Does not Connect to Database....");

        }
        /*
    }else{
        ui->lbl_login_status->setText("DB doesn't open..");

    }*/
  //  registor login_reg;
}

login::~login()
{
    delete ui;
    //db.close();
    connClose();
}

void login::on_btn_login_clear_clicked()
{
    ui->txt_login_password->setText("");
    ui->txt_login_uname->setText("");
}

void login::on_btn_login_login_clicked()
{
    QString username, password;

    username = ui->txt_login_uname->text();
    password = ui->txt_login_password->text();
    // set session from user name
    QString public_username = "";


    //if(db.isOpen()){
    if(connOpen()){

        QSqlQuery login_quary;
        ui->lbl_login_status -> setText("Username = "+username+" & Password = "+password);

        //connOpen();
        login_quary.prepare("SELECT username, password FROM User WHERE username = '"+username+"' AND password = '"+password+"'");

        if(login_quary.exec()){

            int check = 0;
            ui->lbl_login_status -> setText("check = "+check);
            while(login_quary.next()){
                check ++;
            }

            if(check== 1){
                ui->lbl_login_status -> setText("Username & Password correct....");
                login::public_username = username;
                 publicUserName(login::public_username);
                //qDebug() << "public name----" << public_username;
             // con_login = new controller(this);
              connClose();
              this->hide();
              controller_new con_login;
              con_login.setModal(true);
              con_login.exec();
              //con_login.show();



            }

            if(check > 1){
                ui->lbl_login_status -> setText("Username & Password duplicate....");
            }

            if(check < 1){
                ui->lbl_login_status -> setText("Username & Password incorrect....");
                QMessageBox::warning(this,"Warning","Incorrect User name & Password");
            }
             connClose();

        }else{
            ui->lbl_login_status->setText("wrrong quary...");
             connClose();
        }


    }else{
        ui->lbl_login_status->setText("DB doesn't open..");
        qDebug() << "Fail to open DB";
        return;
    }


}

void login::openAbout()
{
    //winAbout = new registor(this);
    //winAbout->show();
}


void login::on_commandLinkButton_clicked()
{
    connClose();
    change_password cp;
    cp.setModal(true);

    cp.exec();
}

void login::on_commandLinkButton_2_clicked()
{
    //registor *login_reg= new registor(this);
    //login_reg= new registor(this);
    //login_reg.show();
    //login_reg.window();
    //login_reg.show();
    //login_reg.raise();
   // login_reg.activateWindow();
    //login_reg.setModal(true);
    //login_reg.exec();
    //this->hide();
    //openAbout();
    this->hide();
    register_new login_reg;
    login_reg.setModal("true");
    login_reg.exec();
}
