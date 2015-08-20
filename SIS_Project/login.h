#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtSql>
#include <QFileInfo>
#include <QDebug>
#include <stdio.h>

#include "controller_new.h"

// newly created register from dialog widget
#include "register_new.h"


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    static QString public_username ; // session uname
    //string st = "cdc";
    QSqlDatabase db; // user details DB
    QSqlDatabase imgdb; // ship details DB

    void publicUserName(QString s){
        qDebug() << "in header file public user name (s)==//" << s;
        //return s;
        public_username = s;
        qDebug() << "in header file public user name ==**" << public_username;
    }

    QString getPublicUserName(){
        qDebug() << "in header file get public user name ==" << public_username;
        return public_username;
    }

    void connCloseImg(){
        imgdb.close();
        imgdb.removeDatabase(QSqlDatabase::defaultConnection);
        qDebug() <<("Default Img DB Connection remove.....");

    }

    void connClose(){

        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
        qDebug() <<("Default DB Connection remove.....");
    }

    bool connOpenImg(){
        imgdb = QSqlDatabase :: addDatabase("QSQLITE");
        imgdb.setDatabaseName("/home/janaka/New3/DB/test_imageDB.sqlite");
        //QFileInfo checkFile(path_db);

        if(imgdb.open()){
           // ui->lbl_login_status->setText("[+] Connect to Database file..");
            qDebug ()<<("Connect to Img Database....");
            return true;
        }else{

            //ui->lbl_login_status->setText("[-]Connect to Database file does not exit..");
            qDebug ()<<("Does not Img Connect to Database....");
            return false;

        }
    }

    bool connOpen(){
        db = QSqlDatabase :: addDatabase("QSQLITE");
        db.setDatabaseName("/home/janaka/SIS_Project/DB/SIS_DB.sqlite");
        //QFileInfo checkFile(path_db);

        if(db.open()){
           // ui->lbl_login_status->setText("[+] Connect to Database file..");
            qDebug ()<<("Connect to Database....");
            return true;
        }else{

            //ui->lbl_login_status->setText("[-]Connect to Database file does not exit..");
            qDebug ()<<("Does not Connect to Database....");
            return false;

        }
    }

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_btn_login_clear_clicked();

    void on_btn_login_login_clicked();

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

     void openAbout(); //make a new function to call the window

private:
    Ui::login *ui;
    //registor login_reg;

    //controller con_login;

    //registor *winAbout; //make a new declaration for the new window

};

#endif // LOGIN_H
