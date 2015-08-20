#include "registor.h"
#include "ui_registor.h"
#include <QMessageBox>
#include <QSqlQuery>
#define path_db "/home/janaka/SIS_DB.sqlite"
//#include "login.h"

registor::registor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registor)

{



    ui->setupUi(this);

//    login login;
/*
    if(connOpen()){
       ui->lbl_reg_connect->setText("[+] Connect to Database file..");
       // QDebug ()<<("Connect to Database....");
    }else{
        ui->lbl_reg_connect->setText("[-]Connect to Database file does not exit..");
        // QDebug ()<<("Does not Connect to Database....");

    }
*/



    //login conn;

    //conn.connOpen();
/*
    db = QSqlDatabase :: addDatabase("QSQLITE");
    db.setDatabaseName(path_db);
    QFileInfo checkFile(path_db);

    if(checkFile.isFile()){
        if(db.open()){
            ui->lbl_reg_connect->setText("[+] Connect to Database file..");
            //qDebug() << "Fail to open DB";
        }else{
            ui->lbl_reg_connect->setText("[-]Connect to Database file does not exit..");
           // qDebug() << "Fail to open DB";

        }
    }else{
        ui->lbl_reg_connect->setText("DB doesn't open..");

    }

    */
}

registor::~registor()
{
    delete ui;
}

void registor::on_btn_reg_clear_2_clicked()
{
    ui->txt_reg_city->setText("");
    ui->txt_reg_email->setText("");
    ui->txt_reg_fullname->setText("");
    ui->txt_reg_houseno->setText("");
    ui->txt_reg_password->setText("");
    ui->txt_reg_postalcode->setText("");
    ui->txt_reg_street->setText("");
    ui->txt_reg_username->setText("");
    ui->txt_reg_userid->setText("");
    ui->txt_reg_usertype->setText("");
    ui->txt_reg_contactno->setText("");
}

void registor::on_btn_reg_register_2_clicked()
{

/*
    login conn;
    QString fullname, username, password, houseno, postalcode, street, city, email, userid, contactno, usertype;

    userid = ui->txt_reg_userid->text();
    username = ui->txt_reg_username->text();
    password = ui->txt_reg_password->text();
    fullname = ui->txt_reg_fullname ->text();
    houseno = ui -> txt_reg_houseno -> text();
    postalcode = ui->txt_reg_postalcode ->text();
    street = ui->txt_reg_street ->text();
    city = ui -> txt_reg_city ->text();
    email = ui-> txt_reg_email ->text();
    contactno = ui->txt_reg_contactno->text();
    contactno = ui->txt_reg_contactno->text();
    usertype = ui -> txt_reg_usertype ->text();

     conn.connOpen();
     if(conn.connOpen()){

         QSqlQuery insert_quary;
         insert_quary.prepare("INSERT INTO User (userid, fullname, usertype, username, password, email, homeno, street, city, contactno, postalcode) VALUES ('"+userid+"', '"+fullname+"', 'operator', '"+username+"', '"+password+"', '"+email+"', '"+houseno+"', '"+street+"', '"+city+"', '"+contactno+"', '"+postalcode+"')");

        //QSqlQuery register_quary;
        //register_quary.prepare();
        //ui->lbl_login_status -> setText("Username = "+username+" & Password = "+password);

        if(insert_quary.exec()){

             QMessageBox :: critical(this, tr("Save"), tr("Successfully saved data..."));

        }else{
             QMessageBox :: critical(this, tr("Error::"), insert_quary.lastError().text());
        }

    }else{
        //ui->lbl_login_status->setText("DB doesn't open...");
        qDebug() << "Fail to open DB";
        return;
    }

*/
}
