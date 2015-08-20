#include "register_new.h"
#include "ui_register_new.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QRegExp>

register_new::register_new(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_new)
{
    ui->setupUi(this);


    login login;
    if(login.connOpen()){
       //ui->lbl_reg_connect->setText("[+] Connect to Database file..");
       // QDebug ()<<("Connect to Database....");
       QSqlQuery select_idquary;
       if(select_idquary.prepare("SELECT userid FROM User ORDER BY userid DESC LIMIT 1")){
            if(select_idquary.exec()){
                select_idquary.next();
                qDebug() << "user id :" << select_idquary.value(0).toString();
                int i = select_idquary.value(0).toInt();
                i++;
                QString sd = QString::number(i);
                //sd[3].unicode()++;

                qDebug() << "sd++++++++++++++++++++++++ :" <<i;
                ui->txt_reg_userid->setText(sd);
            }else {
               qDebug() << "select id quary not execute...";
            }
       }else {
          qDebug() << "elect id quary not prepare well...";
       }

    }else{
        //ui->lbl_reg_connect->setText("[-]Connect to Database file does not exit..");
        // QDebug ()<<("Does not Connect to Database....");

    }
    login.connClose();



}

register_new::~register_new()
{
    delete ui;
}

void register_new::on_btn_reg_clear_2_clicked()
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
    ui->txt_reg_confirmpassword->setText("");
}

void register_new::on_btn_reg_register_2_clicked()
{
    login conn;
    QString fullname, username, password,confirmpassword, houseno, postalcode, street, city, email, userid, contactno, usertype;

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
    confirmpassword = ui->txt_reg_confirmpassword->text();
    usertype = ui -> txt_reg_usertype ->text();

    int check;



    if(!username.isEmpty() && !password.isEmpty() && !fullname.isEmpty() && !houseno.isEmpty() && !postalcode.isEmpty() && !street.isEmpty() && !city.isEmpty() && !email.isEmpty() && !contactno.isEmpty() && !usertype.isEmpty()){
        QRegExp rxfullname("^[a-zA-Z ]+$");
        QRegExp rxusername("^[a-z0-9_-]{5,10}$");
        QRegExp rxpassword("((?=.*[0-9])(?=.*[a-zA-Z])(?=.*[@#$%]).{6,20})");
        QRegExp rxcontect("^[0-9]{10}$");
        QRegExp rxemail("^([\\w-]+(?:\\.[\\w-]+)*)@((?:[\\w-]+\\.)*\\w[\\w-]{0,66})\\.([a-z]{2,6}(?:\\.[a-z]{2})?)$");
        QRegExp rxcity("^[a-zA-Z]+$");
        QRegExp rxpostal("^[0-9]{5}$");

        //mogify.................
        if(conn.connOpen()){

            QSqlQuery login_quary;
           // ui->lbl_login_status -> setText("Username = "+username+" & Password = "+password);

            //connOpen();
            login_quary.prepare("SELECT username FROM User WHERE username = '"+username+"'");

            if(login_quary.exec()){

                check = 0;
                //ui->lbl_login_status -> setText("check = "+check);
                while(login_quary.next()){
                    check ++;
                }

                if(check >= 1){
                    //ui->lbl_login_status -> setText("Username & Password duplicate....");
                }
                conn.connClose();

            }else{
                //ui->lbl_login_status->setText("wrrong quary...");
                 conn.connClose();
            }


        }else{
            //ui->lbl_login_status->setText("DB doesn't open..");
            qDebug() << "Fail to open DB";
            return;
        }


        //.........................................................
        if(check>=1){
            QMessageBox::warning(this,"Warning","Already exist User name");
        }
        else if(!rxfullname.exactMatch(fullname)){
            QMessageBox :: critical(this, tr("Error"), tr("Wrrong Full name..."));
        }
        else if(!rxusername.exactMatch(username)){
            QMessageBox :: critical(this, tr("Error"), tr("user name include only these characteristics.\n 1) symbols in the list, a-z, 0-9, underscore, hyphen. \n 2) Length at least 5 characters and maximum length of 10"));
        }else if(!rxpassword.exactMatch(password)){
            QMessageBox :: critical(this, tr("Error"), tr("Password must include these characteristics.\n 1) must contains one digit from 0-9. \n 2) must contains one lowercase | uppercase characters.\n 3) must contains one special symbols in the list '@#$%'. 4) length at least 6 characters and maximum of 20."));
        }else if(password != confirmpassword){

            QMessageBox :: critical(this, tr("Error"), tr("Password comfirmation was worrong..."));
        }
        else if(!rxcontect.exactMatch(contactno)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied contect number..."));
        }else if(!rxemail.exactMatch(email)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied Email Address..."));
        }else if(!rxcity.exactMatch(city)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied City name..."));
        }else if(!rxpostal.exactMatch(postalcode)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied Postal code..."));
        }

        else{


        conn.connOpen();
     if(conn.connOpen()){

         QSqlQuery insert_quary;
         insert_quary.prepare("INSERT INTO User (userid, fullname, usertype, username, password, email, homeno, street, city, contactno, postalcode) VALUES ('"+userid+"', '"+fullname+"', '"+usertype+"', '"+username+"', '"+password+"', '"+email+"', '"+houseno+"', '"+street+"', '"+city+"', '"+contactno+"', '"+postalcode+"')");

        //QSqlQuery register_quary;
        //register_quary.prepare();
        //ui->lbl_login_status -> setText("Username = "+username+" & Password = "+password);

        if(insert_quary.exec()){

            this-> hide();
            cheack_register_dialogbox crd;
            crd.setModal(true);
            crd.exec();

             //QMessageBox :: critical(this, tr("Save"), tr("Successfully saved data..."));

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
             ui->txt_reg_confirmpassword->setText("");




        }else{
             QMessageBox :: critical(this, tr("Error::"), insert_quary.lastError().text());
        }

        conn.connClose();

    }else{
        //ui->lbl_login_status->setText("DB doesn't open...");
        qDebug() << "Fail to open DB";
        return;
    }
        }
    }else{
        QMessageBox :: critical(this, tr("Error"), tr("Complete the all the feilds..."));
    }
}

void register_new::on_btn_reg_back_clicked()
{
    this -> hide();
    login lg;
    lg.setModal(true);
    lg.exec();
}
