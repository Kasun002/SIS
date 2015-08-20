#include "controller_new.h"
#include "ui_controller_new.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>

#include "ncreport.h"
#include "ncreportoutput.h"
#include "ncreportpreviewoutput.h"
#include "ncreportpreviewwindow.h"
#include <QPrinter>
#include <QCompleter>

using namespace cv;
using namespace std;

QString qsdate; // user loging time
QString qstime; // user login date

QImage controller_new::qimg;
QImage controller_new::qshowimage;

controller_new::controller_new(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::controller_new)
{
    ui->setupUi(this);
    QString qs = login::public_username;  // get session variable
    login lg;


    //Auto search line edit in profile tab
    QStringList qs_username,qs_fullname;
    if(lg.connOpen()){
        QSqlQuery qs;
        if(qs.prepare("SELECT username,fullname FROM User")){
            if(qs.exec()){

                while (qs.next()) {
                    qDebug() << "user name list : " << qs.value(0).toString();
                    qs_username << qs.value(0).toString();
                    qs_fullname << qs.value(1).toString();
                }
                QLineEdit *l = ui->txt_pro_edit_uname;
                QCompleter *qc = new QCompleter(qs_username,this);
                l->setCompleter(qc);
                // set auto search value to abmin panel full name text box
                QLineEdit *l3 = ui->adminPanel_full_name;
                QCompleter *qc3 = new QCompleter(qs_fullname,this);
                //qc->setCaseSensitivity(caseSensitivity(Qt::CaseSensi
                l3->setCompleter(qc3);

                QLineEdit *l2 = ui->txt_pro_edit_uname_4;
                QCompleter *qc2 = new QCompleter(qs_username,this);
                l2->setCompleter(qc2);



            }
        }
    }else{
        qDebug() << "connection open(SIS_DB) fail.";
    }





    //qDebug() << "controll public uname ****" << login::public_username;

    qDebug() << "qs++++++++++++" << qs;

    QString puser = lg.getPublicUserName();

   // qDebug() << "controll public uname ****" ; //<< lg.public_username;
    ui->txt_home_username->setText(qs);
    ui-> dtedit_home_logindt->setDateTime(QDateTime::currentDateTime());
    //QDateTime qdt = ();
    QSqlQueryModel * model = new QSqlQueryModel();

    qstime=(QTime::currentTime()).toString("hh.mm.ss"); // user loging time
    qsdate= (QDate::currentDate()).toString("dd.MM.yyyy"); // user login date

    // check DB
    //if(){

    //}


    //set default value for map view date and time
    ui->dedit_map_date->setDate(QDate::currentDate());
    ui->tedit_map_end->setTime(QTime::currentTime());
    ui->tedit_map_start->setTime(QTime::currentTime());

    // set values for report view date and time
    ui->selectbox_report_dfrom->setDate(QDate::currentDate());
    ui->selectbox_report_dto->setDate(QDate::currentDate());
    ui->selectbox_report_tstart->setTime(QTime::currentTime());
    ui->selectbox_report_tend->setTime(QTime::currentTime());

    if(lg.connOpen()){

     QSqlQuery* qry2 = new QSqlQuery(lg.imgdb);


    // set visibility of components
    if(qry2->prepare("SELECT userid, usertype FROM User WHERE username='"+qs+"'")){
        if(qry2->exec()){
            qry2->next();
            QString position = qry2->value(1).toString();
            qDebug() << "position" << position;
            if(position == "admin"){
               // qDebug() << "in admin";
                ui->txt_pro_edit_uname->setEnabled(true);
                ui->txt_pro_edit_uname_4->setEnabled(true);
                ui->groupBox_adminpanel->setEnabled(true);  // enable admin panel
                ui->txt_adminPanel_Fname->setEnabled(false); // txt_adminPanel_Fname set disenable
                ui->txt_adminPanel_city->setEnabled(false);
                ui->txt_adminPanel_contact->setEnabled(false);
                ui->txt_adminPanel_postalcode->setEnabled(false);
                ui->txt_adminPanel_street->setEnabled(false);
                ui->txt__adminPanel_email->setEnabled(false);
                ui->txt__adminPanel_houseno->setEnabled(false);
                ui->txt__adminPane_uname->setEnabled(false);
                //ui->admin_groupbox->setEnabled(true);
                //ui->admin_groupbox
            }else{
                ui->txt_pro_edit_uname->setEnabled(false);
                ui->txt_pro_edit_uname_4->setEnabled(false);
               // ui->admin_groupbox->setEnabled(false);
            }
        }else {
            qDebug() << "primission given quart not execute well...";
        }
    }else{
        qDebug() << "primission given quart not prepare well...";
    }
    lg.connClose();
    }else{
        qDebug() << "Img DB not connection open.";
    }
lg.connClose();

if(lg.connOpenImg()){
 QSqlQuery* qry = new QSqlQuery(lg.imgdb);
//..................................................................
    //if(qry->prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_zone, ship_comment FROM img_details WHERE img_time>'08.45.42' AND img_date ='"+qsdate+"'")){
    if(qry->prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_zone, ship_comment FROM img_details WHERE img_time>'21.03.36' AND img_date ='01.08.2015'")){
        qDebug() << "image details prepare is ok";
        if(qry->exec()){
            qDebug() << "execute the quary get iamage details...";
        }else{
             qDebug() << "execute img details fail...";
        }
    }else{
        qDebug() << "perpare img details fail...";
    }

    model->setQuery(*qry);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Ship ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ship Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Ship Category"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Arrival Time to Zone"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Detected Zone"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Comment"));
    //.....................................................................................
    //.........................ui->table_controllnew_home->horizontal
    ui->table_controllnew_home->setModel(model);
    lg.connCloseImg();
    }else{
    qDebug() << "connection not open(giving piority)...";
}
lg.connCloseImg();

    // set vlues for Report view categoty comboox
    ui->dropbox_report_category->addItem("none");
    ui->dropbox_report_category->addItem("cargo");
    ui->dropbox_report_category->addItem("Passenger");
    ui->dropbox_report_category->addItem("bulk carriers");

    //set values for Report view zone combox
    ui->dropbox_report_zone->addItem("none");
    ui->dropbox_report_zone->addItem("A");
    ui->dropbox_report_zone->addItem("B");
    ui->dropbox_report_zone->addItem("C");
    ui->dropbox_report_zone->addItem("D");

    // set vlues for Map view categoty comboox
    ui->cbox_map_category->addItem("none");
    ui->cbox_map_category->addItem("cargo");
    ui->cbox_map_category->addItem("Passenger");
    ui->cbox_map_category->addItem("bulk carriers");

    //set values for Map view zone combox
    ui->cbox_map_zone->addItem("none");
    ui->cbox_map_zone->addItem("A");
    ui->cbox_map_zone->addItem("B");
    ui->cbox_map_zone->addItem("C");
    ui->cbox_map_zone->addItem("D");

    //set timer to update ship details...
    timer = new QTimer(this);
    qDebug() << "error...";

    connect(timer,SIGNAL(timeout()),this,SLOT(ShipDBUpadate()));
    timer->start(4000);

}

//automatically DB table update

void controller_new::ShipDBUpadate(){
    qDebug() << "call for update ship details******************************";
    login lg;
    if(lg.connOpenImg()){
     QSqlQuery* qry = new QSqlQuery(lg.imgdb);
    //..................................................................
        //if(qry->prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_zone, ship_comment FROM img_details WHERE img_time>'08.45.42' AND img_date ='"+qsdate+"'")){
        if(qry->prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_zone, ship_comment FROM img_details WHERE img_time>='"+qstime+"' AND img_date ='"+qsdate+"'")){
            qDebug() << "image details prepare is ok";
            if(qry->exec()){
                qDebug() << "execute the quary get iamage details...";
            }else{
                 qDebug() << "execute img details fail...";
            }
        }else{
            qDebug() << "perpare img details fail...";
        }
        QSqlQueryModel * model = new QSqlQueryModel();

        model->setQuery(*qry);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Ship ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ship Name"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Ship Categoty"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Arrival Time to Zone"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Detected Zone"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("Comment"));
        ui->table_controllnew_home->setModel(model);

        lg.connCloseImg();
        }else{
        qDebug() << "connection not open(giving piority)...";
    }
    lg.connCloseImg();

}



controller_new::~controller_new()
{
    delete ui;
}

void controller_new::on_btn_pro_edit_search_clicked()
{
    QString uname;
    uname = ui->txt_pro_edit_uname->text();

    login conn;
    conn.connOpen();
    if(conn.connOpen()){

     QSqlQuery select_quary;
     select_quary.prepare("SELECT * FROM User WHERE username ='"+uname+"'");
    int count = 0;
    if(select_quary.exec()){
        //QMessageBox::impormation(this,"Sucess","Incorrect User name");
        qDebug() << "excecute the quary correctly.***";
        while (select_quary.next()) {
            count++;

        }
        QSqlQuery select_quary2;
        select_quary2.prepare("SELECT * FROM User WHERE username ='"+uname+"'");
        if(count == 1){
            select_quary2.exec();
            while(select_quary2.next()){
            ui->txt_pro_edit_city->setText(select_quary2.value(8).toString());
            //qDebug() <<"9"+select_quary.value(9).toString();
            ui->txt_pro_edit_contect->setText(select_quary2.value(9).toString());
            //qDebug() <<"10"+select_quary.value(10).toString();
            ui->txt_pro_edit_email->setText(select_quary2.value(5).toString());
            //qDebug() <<"6"+select_quary.value(6).toString();
            ui->txt_pro_edit_fname->setText(select_quary2.value(1).toString());
            //qDebug() <<"2"+select_quary.value(2).toString();
            ui->txt_pro_edit_hno->setText(select_quary2.value(6).toString());
            //qDebug() <<"7"+select_quary.value(7).toString();
            ui->txt_pro_edit_pcode->setText(select_quary2.value(10).toString());
            qDebug() <<"11"+select_quary.value(10).toString();
            ui->txt_pro_edit_street->setText(select_quary2.value(7).toString());
            //qDebug() <<"8"+select_quary.value(8).toString();
            ui->txt_pro_edit_utype->setText(select_quary2.value(2).toString());
            //qDebug() <<"3"+select_quary.value(3).toString();
            ui->txt_pro_edit_uname_2->setText(select_quary2.value(1).toString());
            }

        }else{
            QMessageBox::warning(this,"Warning","Incorrect User name.");
        }

        conn.connClose();
    }else{
        QMessageBox::warning(this,"Warning","Incorrect User name");
    }
}else{
       qDebug() << "Failed to open the database...";
    }
}

void controller_new::on_btn_pro_edit_update_clicked()
{

}

void controller_new::on_btn_pro_edit_update_2_clicked()
{

    login conn;
    QString username, fullname,street, hno, city, postacode, email, contect ;
    username = ui->txt_pro_edit_uname->text();
    fullname = ui->txt_pro_edit_fname->text();
    street = ui->txt_pro_edit_street ->text();
    hno = ui->txt_pro_edit_hno ->text();
    city = ui ->txt_pro_edit_city->text();
    postacode = ui->txt_pro_edit_pcode->text();
    email = ui ->txt_pro_edit_email ->text();
    contect = ui ->txt_pro_edit_contect->text();

    if(!username.isEmpty() && !fullname.isEmpty() && !street.isEmpty() && !hno.isEmpty() && !city.isEmpty() && !postacode.isEmpty() && !email.isEmpty() && !contect.isEmpty()){

        // methana sita code change kirimata atha.......................................
        //QRegExp rxpassword("((?=.*[0-9])(?=.*[a-zA-Z])(?=.*[@#$%]).{6,20})");
        QRegExp rxfullname("^[a-zA-Z ]+$");
        //QRegExp rxusername("^[a-z0-9_-]{5,10}$");
        //QRegExp rxpassword("((?=.*[0-9])(?=.*[a-zA-Z])(?=.*[@#$%]).{6,20})");
        QRegExp rxcontect("^[0-9]{10}$");
        QRegExp rxemail("^([\\w-]+(?:\\.[\\w-]+)*)@((?:[\\w-]+\\.)*\\w[\\w-]{0,66})\\.([a-z]{2,6}(?:\\.[a-z]{2})?)$");
        QRegExp rxcity("^[a-zA-Z]+$");
        QRegExp rxpostal("^[0-9]{5}$");

        if(!rxfullname.exactMatch(fullname)){
            QMessageBox :: critical(this, tr("Error"), tr("Wrrong full name..."));
        }
        else if(!rxcontect.exactMatch(contect)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied contect number..."));
        }else if(!rxemail.exactMatch(email)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied Email Address..."));
        }else if(!rxcity.exactMatch(city)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied City name..."));
        }else if(!rxpostal.exactMatch(postacode)){
            QMessageBox :: critical(this, tr("Error"), tr("Invalied Postal code..."));
        }
        else{
       // ui->lbl_change_password->setText("ok....");
        conn.connClose();

        if(conn.connOpen()){
            // ui->lbl_change_password->setText("connect to DB..");

            QSqlQuery update_quary;


            //connOpen();
            update_quary.prepare("UPDATE User SET fullname = '"+fullname+"', email= '"+email+"', homeno='"+hno+"', street='"+street+"', city='"+city+"', contactno='"+contect+"', postalcode='"+postacode+"' WHERE username = '"+username+"'");

            if(update_quary.exec()){

                //int check = 0;

                qDebug() << " ok...";

                update_quary.next();
                conn.connClose();
                QMessageBox::information(this,tr("Success"),tr("Update user profile successfuly!"));

                ui->txt_pro_edit_uname->setText("");
                ui->txt_pro_edit_fname->setText("");
                ui->txt_pro_edit_street ->setText("");
                ui->txt_pro_edit_hno ->setText("");
                ui ->txt_pro_edit_city->setText("");
                ui->txt_pro_edit_pcode->setText("");
                ui ->txt_pro_edit_email ->setText("");
                ui ->txt_pro_edit_contect->setText("");
                ui ->txt_pro_edit_uname_2 ->setText("");
                ui ->txt_pro_edit_utype->setText("");



            }else{
                //ui->lbl_change_password->setText("wrrong quary...");
                qDebug() << "wrrong quay";
            }


        }else{
            //ui->lbl_change_password->setText("DB doesn't open..");
            qDebug() << "Fail to open DB";
            return;
        }
        }
    }else{
            QMessageBox :: critical(this, tr("Error"), tr("Complete the all the feilds..."));
        }
}

void controller_new::on_btn_pro_edit_clear1_clicked()
{
    ui->txt_pro_edit_uname->setText("");
}

void controller_new::on_btn_pro_edit_clear_2_clicked()
{
    ui->txt_pro_edit_fname->setText("");
    ui->txt_pro_edit_street ->setText("");
    ui->txt_pro_edit_hno ->setText("");
    ui ->txt_pro_edit_city->setText("");
    ui->txt_pro_edit_pcode->setText("");
    ui ->txt_pro_edit_email ->setText("");
    ui ->txt_pro_edit_contect->setText("");
    ui ->txt_pro_edit_uname_2 ->setText("");
    ui ->txt_pro_edit_utype->setText("");
}

void controller_new::on_btn_pro_edit_reset_2_clicked()
{
    QString uname;
    uname = ui->txt_pro_edit_uname_2->text();

    login conn;
    conn.connOpen();
    if(conn.connOpen()){

     QSqlQuery select_quary2;
     select_quary2.prepare("SELECT * FROM User WHERE username ='"+uname+"'");
   // int count = 0;
    if(select_quary2.exec()){
        //QMessageBox::impormation(this,"Sucess","Incorrect User name");
        qDebug() << "excecute the quary correctly.***";


        while (select_quary2.next()) {
           // count++;
            ui->txt_pro_edit_city->setText(select_quary2.value(8).toString());
            //qDebug() <<"9"+select_quary.value(9).toString();
            ui->txt_pro_edit_contect->setText(select_quary2.value(9).toString());
            //qDebug() <<"10"+select_quary.value(10).toString();
            ui->txt_pro_edit_email->setText(select_quary2.value(5).toString());
            //qDebug() <<"6"+select_quary.value(6).toString();
            ui->txt_pro_edit_fname->setText(select_quary2.value(1).toString());
            //qDebug() <<"2"+select_quary.value(2).toString();
            ui->txt_pro_edit_hno->setText(select_quary2.value(6).toString());
            //qDebug() <<"7"+select_quary.value(7).toString();
            ui->txt_pro_edit_pcode->setText(select_quary2.value(10).toString());
            //qDebug() <<"11"+select_quary.value(10).toString();
            ui->txt_pro_edit_street->setText(select_quary2.value(7).toString());
            //qDebug() <<"8"+select_quary.value(8).toString();
            ui->txt_pro_edit_utype->setText(select_quary2.value(2).toString());
            //qDebug() <<"3"+select_quary.value(3).toString();
            ui->txt_pro_edit_uname_2->setText(select_quary2.value(1).toString());

        }



        conn.connClose();
    }else{
        QMessageBox::warning(this,"Warning","Incorrect User name");
    }
}else{
       qDebug() << "Failed to open the database...";
    }
}

void controller_new::on_btn_pro_edit_search_3_clicked()
{

    QString uname;
    uname = ui->txt_pro_edit_uname_4->text();

    login conn;
    conn.connOpen();
    if(conn.connOpen()){

     QSqlQuery select_quary;
     select_quary.prepare("SELECT * FROM User WHERE username ='"+uname+"'");
    int count = 0;
    if(select_quary.exec()){
        //QMessageBox::impormation(this,"Sucess","Incorrect User name");
        qDebug() << "excecute the quary correctly.***";
        while (select_quary.next()) {
            count++;

        }
        QSqlQuery select_quary2;
        select_quary2.prepare("SELECT * FROM User WHERE username ='"+uname+"'");
        if(count == 1){
            select_quary2.exec();
            while(select_quary2.next()){
            ui->txt_pro_view_city->setText(select_quary2.value(8).toString());
            //qDebug() <<"9"+select_quary.value(9).toString();
            ui->txt_pro_view_contact->setText(select_quary2.value(9).toString());
            //qDebug() <<"10"+select_quary.value(10).toString();
            ui->txt_pro_view_email->setText(select_quary2.value(5).toString());
            //qDebug() <<"6"+select_quary.value(6).toString();
            ui->txt_pro_view_fname->setText(select_quary2.value(1).toString());
            //qDebug() <<"2"+select_quary.value(2).toString();
            ui->txt_pro_view_hno->setText(select_quary2.value(6).toString());
            //qDebug() <<"7"+select_quary.value(7).toString();
            ui->txt_pro_view_postalcode->setText(select_quary2.value(10).toString());
            qDebug() <<"11"+select_quary.value(10).toString();
            ui->txt_pro_view_street->setText(select_quary2.value(7).toString());
            //qDebug() <<"8"+select_quary.value(8).toString();
            ui->txt_pro_view_utype->setText(select_quary2.value(2).toString());
            //qDebug() <<"3"+select_quary.value(3).toString();
            ui->txt_pro_view_uname->setText(select_quary2.value(1).toString());
            }

        }else{
            QMessageBox::warning(this,"Warning","Incorrect User name.");
        }

        conn.connClose();
    }else{
        QMessageBox::warning(this,"Warning","Incorrect User name");
    }
}else{
       qDebug() << "Failed to open the database...";
    }

}

void controller_new::on_btn_pro_view_clear_clicked()
{
    ui->txt_pro_edit_uname_4->setText("");
}

void controller_new::on_table_controllnew_home_activated(const QModelIndex &index)
{

}

void controller_new::on_btn_home_repress_clicked()
{

    login lg2 ;
    QDateTime qdt = (QDateTime::currentDateTime());

    if(lg2.connOpenImg()){
        QSqlQuery *get_ship_details = new QSqlQuery(lg2.imgdb);
        qDebug() << "qsdate =***" << qsdate;
        qDebug() << "qstime =***" << qstime;
        //qsdate = "21.47.00";
       // if(get_ship_details -> prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_comment FROM img_details WHERE img_time>'"+qstime+"' AND img_date ='"+qsdate+"'")){
    if(get_ship_details -> prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_zone, ship_comment FROM img_details WHERE img_time>'08.45.42' AND img_date ='"+qsdate+"'")){
            qDebug() << "select ship details quary prepare sucess...";
            if(get_ship_details->exec()){

                QSqlQueryModel *model2 = new QSqlQueryModel();

                model2->setQuery(*get_ship_details);
                ui->table_controllnew_home->setModel(model2);
                //qDebug() << "index of table" << ui->table_controllnew_home-> columnAt();
                lg2.connCloseImg();
                qDebug() << "select ship details quary execute success...";
            }else{
                qDebug() << "select ship details quary execute fails...";
                lg2.connCloseImg();
            }
        }else{
            lg2.connCloseImg();
            qDebug() << "select ship details quary prepare fails...";
        }
    }else{
        qDebug() << "image DB connection fail.";
    }

    //get_ship_details.prepare()


}

void controller_new::on_table_controllnew_home_clicked(const QModelIndex &index)
{
     int i = ui->table_controllnew_home->selectionModel()->currentIndex().row();
     qDebug() << "index i : " << i;
     //TableModel *sqm = new QSqlQueryModel();
    // QTableView qt = new QTableView();
     QString s = ui->table_controllnew_home->model()->index(i,0).data().toString();
     ui->txt_home_shipid->setText(s);
     ui->txt_home_shopname->setText(ui->table_controllnew_home->model()->index(i,1).data().toString());

     QString qsdate = ui->table_controllnew_home->model()->index(i,4).data().toString();
     qDebug() << "index date..: " << qsdate;
     QDate qd = QDate::fromString(qsdate,"MM-dd-yyyy");
     //ui->dtedite_home_date->setDate(ui->table_controllnew_home->model()->index(i,4).data().toDate());
    // qDebug() << " date..: " << qd;
    // QDateEdit e;
     //e.setDate(qd);
     //e.show();
     ui->dtedite_home_date->setDate(QDate::currentDate());
     ui->dtedite_home_dt->setTime(ui->table_controllnew_home->model()->index(i,3).data().toTime());
     ui->txt_home_shiptype->setText(ui->table_controllnew_home->model()->index(i,2).data().toString());
     ui->txtarea_home_comment->setText(ui->table_controllnew_home->model()->index(i,6).data().toString());
     ui->txt_home_shipzone->setText(ui->table_controllnew_home->model()->index(i,5).data().toString());
     //qt.in
    // QString s= sqm->index(i,1).data().toString();
     qDebug() << "s= : " << s;
}

void controller_new::on_btn_home_update_clicked()
{


    login conn;
    QString shipname, shipid,comment; //  hno, city, postacode, email, contect ;
    shipname = ui->txt_home_shopname->text();
    shipid = ui->txt_home_shipid->text();

    // need to comments................................
    comment = ui->txtarea_home_comment->toPlainText();

    if(!shipname.isEmpty() && !shipid.isEmpty()){
        if(conn.connOpenImg()){
            // ui->lbl_change_password->setText("connect to DB..");

            QSqlQuery update_quary;

            qDebug() << "shipid ===" << shipid;
            //connOpen();
            if(update_quary.prepare("UPDATE img_details SET ship_name = '"+shipname+"',ship_comment='"+comment+"' WHERE img_id = '"+shipid+"'")){

            if(update_quary.exec()){

                //int check = 0;

                qDebug() << " ok...";

                update_quary.next();
                conn.connCloseImg();
                QMessageBox::information(this,tr("Success"),tr("Update Ship Details successfuly!"));

                ui->txt_home_shipid->setText("");
                ui->txt_home_shopname->setText("");
                ui->txtarea_home_comment ->setText("");
                //ui->dtedite_home_dt->setText("");


            }else{
                //ui->lbl_change_password->setText("wrrong quary...");
                qDebug() << "wrrong quay";
            }
}else{
       qDebug() << "update quary not prepare...";
}
        }else{
            //ui->lbl_change_password->setText("DB doesn't open..");
            qDebug() << "Fail to open DB";
            return;
        }
        }// not complete feild
    else{
            QMessageBox :: critical(this, tr("Error"), tr("Complete the all the feilds..."));
        }



}



void controller_new::on_btn_home_clear_clicked()
{
    ui->txt_home_shipid->setText("");
    ui->txt_home_shopname->setText("");
    ui->txtarea_home_comment ->setText("");
    ui->txt_home_shipid->setText("");
    ui->txt_home_shiptype->setText("");
    ui->txt_home_shipzone->setText("");
    ui->dtedite_home_dt->setTime(QTime::currentTime());
    ui->dtedite_home_date->setDate(QDate::currentDate());
}

void controller_new::on_btn_home_reset_clicked()
{

    QString sid;
    sid = ui->txt_home_shipid->text();

    login conn;
    conn.connOpenImg();
    if(conn.connOpenImg()){

     QSqlQuery select_quary3;
     select_quary3.prepare("SELECT * FROM img_details WHERE img_id ='"+sid+"'");
   // int count = 0;
    if(select_quary3.exec()){
        //QMessageBox::impormation(this,"Sucess","Incorrect User name");
        qDebug() << "excecute the quary correctly.***";


        while (select_quary3.next()) {
           // count++;
            ui->txt_home_shipid->setText(select_quary3.value(0).toString());
            //qDebug() <<"9"+select_quary.value(9).toString();
            ui->txt_home_shiptype->setText(select_quary3.value(8).toString());
            //qDebug() <<"10"+select_quary.value(10).toString();
            ui->txt_home_shopname->setText(select_quary3.value(1).toString());
            //qDebug() <<"6"+select_quary.value(6).toString();
            ui->dtedite_home_date->setDate(select_quary3.value(4).toDate());
            //qDebug() <<"2"+select_quary.value(2).toString();
            ui->dtedite_home_dt->setTime(select_quary3.value(2).toTime());
            //qDebug() <<"7"+select_quary.value(7).toString();
            ui->txtarea_home_comment->setText(select_quary3.value(7).toString());
            ui->txt_home_shipzone->setText(select_quary3.value(8).toString());
            //qDebug() <<"11"+select_quary.value(10).toString();


        }


        conn.connCloseImg();
    }else{
        QMessageBox::warning(this,"Warning","Fail to reset ship detais...");
    }
}else{
       qDebug() << "Failed to open the database...";
        conn.connCloseImg();
    }

}

void controller_new::on_btn_map_genarate_clicked()
{
    QString sn = ui->txt_map_sname->text();
    QString zn = ui->cbox_map_zone->currentText();
    QString catagary = ui->cbox_map_zone->currentText();
    QString d = ui->dedit_map_date->date().toString("dd.MM.yyyy");
    QString st =ui->tedit_map_start->time().toString("hh.mm.ss");
    QString et = ui->tedit_map_end->time().toString("hh.mm.ss");

    // current date......................................................................./////
    QString c_date = QDate::currentDate().toString("dd.MM.yyyy");
    QString c_date_y = QDate::currentDate().toString("yyyy");
    QString c_date_M = QDate::currentDate().toString("MM");
    QString c_date_d = QDate::currentDate().toString("dd");

    //selected _date
    QString s_date_y = ui->dedit_map_date->date().toString("yyyy");
    QString s_date_M =ui->dedit_map_date->date().toString("MM");
    QString s_date_d = ui->dedit_map_date->date().toString("dd");

    // current time

    QString c_time_h = QTime::currentTime().toString("hh");
    QString c_time_m = QTime::currentTime().toString("mm");

    //selected end time
    QString e_time_h = ui->tedit_map_end->time().toString("hh");
    QString e_time_m = ui->tedit_map_end->time().toString("mm");

    //selected start time
    QString s_time_h = ui->tedit_map_start->time().toString("hh");
    QString s_time_m = ui->tedit_map_start->time().toString("mm");

    int errorcount=0; // count the errors

    if(errorcount==0){
    if(s_date_y.compare(c_date_y) > 0){

            QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(year)."));
      errorcount++;
        }else if (s_date_y.compare(c_date_y) == 0) {
                  if(s_date_M.compare(c_date_M) > 0){
                      errorcount++;
                   QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(month)."));
                  }else if (s_date_M.compare(c_date_M) ==0) {
                     if(s_date_d.compare(c_date_d) >0){
                         errorcount++;
                         QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(day)."));
                     }
                  }

        }
}

    if(errorcount==0){
            if (d.compare(c_date)==0) {
               if(e_time_h.compare(c_time_h) >0){
                   errorcount++;
                   QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(h)."));
               }else if (e_time_m.compare(c_time_m) >0) {
                   errorcount++;
                   QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
               }else if(s_time_h.compare(c_time_h) >0){
                   errorcount++;
                   QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(h)."));
                }else if (s_time_m.compare(c_time_m) >0) {
                   errorcount++;
                    QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
                }

           }
    }
    if(errorcount==0){
        if(s_time_h.compare(e_time_h) >0){
            errorcount++;
            QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(hh)."));
        }else if (s_time_m.compare(e_time_m) >0) {
            errorcount++;
            QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
        }

    }

    if(errorcount==0){

        if(catagary == "none"){
            qDebug() << "ship type is none";
            catagary ="";
        }
        if(zn == "none"){
            qDebug() << "zone is none";
            zn ="";
        }
        if(sn == ""){
             qDebug() << "ship name is empty";
            sn = "";
        }

    login lg;

    qDebug()<<"zone.....***" << zn;

    if(lg.connOpenImg()){

     QSqlQuery qsd ;//= new QSqlQuery(lg.imgdb);
       //if(qsd.prepare("SELECT img_id, ship_name, img_x, img_y FROM img_details WHERE ship_name LIKE '%"+sn+"' AND ship_zone LIKE '"+zn+"' AND ship_type LIKE '%"+catagary+"' AND img_date='"+d+"' AND img_time>='"+st+"' AND img_time<='"+et+"'")){

     //need to edit zone
        if(qsd.prepare("SELECT img_id, ship_name, img_x, img_y FROM img_details WHERE ship_name LIKE '%_ship' AND ship_zone LIKE '"+zn+"%' AND ship_type='Passenger' AND img_date='"+d+"' AND img_time>='"+st+"' AND img_time<='"+et+"'")){


            // if(qsd.prepare("SELECT img_id, ship_name, img_x, img_y FROM img_details WHERE ship_name LIKE '"+sn+"%' AND img_time >='"+st+"'  AND img_time <='"+et+"' AND img_date>='"+d+"' AND ship_zone = '"+zn+"' AND ship_type LIKE '%"+catagary+"'")) {
            qDebug() << "plot quary prepare success...";
            if(qsd.exec()){

                //Mat image;
                        //string filename = "/home/janaka/map.jpg";
                        qDebug() << "ploat quary execute success...";
                       string map_path = "/home/janaka/SIS_Project/images/map.jpg";
                        Mat map;
                           map = imread(map_path, CV_LOAD_IMAGE_COLOR);   // Read the file

                           if(! map.data)                              // Check for invalid input
                           {
                               cout <<  "Could not open or find the image" << std::endl ;
                              // return -1;
                           }else{


                               // new code plot in new grip

                               line( map, Point( 320, 0 ), Point( 320, 360), Scalar( 110, 220, 0 ),  2, 8 );
                               line( map, Point( 0, 180 ), Point( 640, 180), Scalar( 110, 220, 0 ),  2, 8 );
                               putText(map,"A", Point(160,90), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,200,200), 4);
                               putText(map,"B", Point(480,90), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,200,200), 4);
                               putText(map,"C", Point(160,270), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,200,200), 4);
                               putText(map,"D", Point(480,270), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,200,200), 4);
                               int x;
                               int y;

                               while (qsd.next()) {
                                    x = qsd.value(2).toInt();
                                    y = qsd.value(3).toInt();
                                    qDebug() << "x = " << x << "y = " << y;
                                    circle(map, Point((x),(y)), 3.0, Scalar(0,0,255),1,8);
                               }

                               QImage image2; //( image.data, image.cols, image.rows, image.step, QImage::Format_RGB32 );


                               //QImage img;
                               image2 = QImage((const unsigned char*)(map.data),
                                        map.cols,map.rows,QImage::Format_RGB888);

                               controller_new::qimg = image2;

                               //this->hide();
                               map_view mview;
                               mview.setModal(true);
                               mview.exec();

                               lg.connCloseImg();

                           }


            }else{
                qDebug() << "ploat quary execution fail...";
            }
        }else{
            qDebug() << "Polt quary not prepare...";
       }
    }
else{
        qDebug() << "connection not open...";
   }
    }

}

void controller_new::on_btn_home_show_clicked()
{
    QString shipid = ui->txt_home_shipid->text();
    qDebug() << "ship_id" << shipid;
    login lg;
    if(lg.connOpenImg()){
    QSqlQuery* qry = new QSqlQuery(lg.imgdb);
//..................................................................
    //if(qry->prepare("SELECT img_id, ship_name, img_time,img_value FROM img_details WHERE img_id='"+shipid+"'")){
    if(qry->prepare("SELECT img_id, ship_name,img_value FROM img_details WHERE img_id='"+shipid+"'")){
        qDebug() << "image details prepare is ok";
        if(qry->exec()){
            qDebug() << "execute the quary get iamage details...";
           // while (qry->next()) {
            qry->next();
            QString s = qry->value(0).toString();
            qDebug() << "s.." << s;
            qDebug() << "s.." << qry->value(2).toByteArray();
            QByteArray getimage;



            getimage = qry->value(2).toByteArray();

            if(!getimage.isNull()){


            QImage qimage;  //=QPixmap::loadFromData(getimage,"JPG");
           // QPixmap qimage;


            if(qimage.loadFromData(getimage,"PNG")){
               qDebug() << "ok.....................................";
                controller_new::qshowimage = qimage;

                //this->hide();
                show_image simage;
                simage.setModal(true);
                simage.exec();




            }else{
                qDebug() << "not ok.....................................";
            }

            }else{
                    qDebug()<< "byte array is empty.......";
            }
        }else{
             qDebug() << "execute img details fail...";
        }
    }else{
        qDebug() << "perpare img details fail...";
    }
    lg.connCloseImg();
}else{
        qDebug() << "fail to connect image DB...";
        lg.connCloseImg();
    }

}


void controller_new::on_btn_report_genarate_clicked()
{
    qDebug() << " ..****************";
    login lg;
    QString s_name = ui->txt_report_sname->text();
    int errorcount=0;
       //QString s_date =ui->dropbox_report_category->currentText();
       QString s_starttime= ui->selectbox_report_tstart->time().toString("hh.mm.ss");
       QString s_endtime= ui->selectbox_report_tend->time().toString("hh.mm.ss");
       QString s_zone = ui->dropbox_report_zone->currentText();
       QString s_datefrom= ui->selectbox_report_dfrom->date().toString("dd.MM.yyyy");
       QString s_dateto= ui->selectbox_report_dto->date().toString("dd.MM.yyyy");
       QString s_type = ui->dropbox_report_category->currentText();

       // current date
       QString c_date = QDate::currentDate().toString("dd.MM.yyyy");
       QString c_date_y = QDate::currentDate().toString("yyyy");
       QString c_date_M = QDate::currentDate().toString("MM");
       QString c_date_d = QDate::currentDate().toString("dd");
       //selected from_date
       QString s_date_y = ui->selectbox_report_dfrom->date().toString("yyyy");
       QString s_date_M =ui->selectbox_report_dfrom->date().toString("MM");
       QString s_date_d = ui->selectbox_report_dfrom->date().toString("dd");
       //selected to_date
       QString e_date_y = ui->selectbox_report_dto->date().toString("yyyy");
       QString e_date_M =ui->selectbox_report_dto->date().toString("MM");
       QString e_date_d = ui->selectbox_report_dto->date().toString("dd");

       // current time

       QString c_time_h = QTime::currentTime().toString("hh");
       QString c_time_m = QTime::currentTime().toString("mm");

       //selected start time
       QString e_time_h = ui->selectbox_report_tend->time().toString("hh");
       QString e_time_m = ui->selectbox_report_tend->time().toString("mm");

       //selected end time
       QString s_time_h = ui->selectbox_report_tstart->time().toString("hh");
       QString s_time_m = ui->selectbox_report_tstart->time().toString("mm");

       if(errorcount==0){
       if(s_date_y.compare(c_date_y) > 0){

               QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(yyyy)."));
         errorcount++;
           }else if (s_date_y.compare(c_date_y) == 0) {
                     if(s_date_M.compare(c_date_M) > 0){
                         errorcount++;
                      QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(MM)."));
                     }else if (s_date_M.compare(c_date_M) ==0) {
                        if(s_date_d.compare(c_date_d) >0){
                            errorcount++;
                            QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(dd)."));
                        }
                     }

           }
}
       //else if(s_date_d.compare(c_date_d) > 0){
         //  QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(dd)."));
       //}

       if(errorcount==0){
       if (e_date_y.compare(c_date_y) > 0) {
           errorcount++;
           QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(yyyy)."));
       }else if (e_date_y.compare(c_date_y) == 0) {
           if(e_date_M.compare(c_date_M)>0){
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(MM)."));
           }else if (e_date_M.compare(c_date_M) == 0) {
              if(e_date_d.compare(c_date_d) > 0){
                  errorcount++;
                  QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(dd)."));
              }
           }

       }
       }

if(errorcount == 0){
       if(s_date_y.compare(e_date_y)>0){
           errorcount++;
           QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(Year)."));
       }else if (s_date_y.compare(e_date_y)==0) {
          if(s_date_M.compare(e_date_M)>0){
              errorcount++;
              QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(Month)."));
          }else if (s_date_M.compare(e_date_M)==0) {
             if(s_date_d.compare(e_date_d)>0){
                 errorcount++;
                 QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(Day)."));
             }
          }
       }
}
      // else if (e_date_d.compare(c_date_d) > 0) {
        //  QMessageBox :: critical(this, tr("Error"), tr("Invalied Date(Day)."));
       //}
if(errorcount==0){
        if (s_datefrom.compare(c_date)==0) {
           if(e_time_h.compare(c_time_h) >0){
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(H)."));
           }else if (e_time_m.compare(c_time_m) >0) {
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
           }else if(s_time_h.compare(c_time_h) >0){
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(H)."));
            }else if (s_time_m.compare(c_time_m) >0) {
               errorcount++;
                QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
            }

       }
}

if(errorcount==0){
       if (s_dateto.compare(c_date)==0) {
           if(s_time_h.compare(c_time_h) >0){
               errorcount++;
              QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(H)."));
           }else if (s_time_m.compare(c_time_m) >0) {
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
           }else if(e_time_h.compare(c_time_h) >0){
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(H)."));
           }else if (e_time_m.compare(c_time_m) >0) {
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
           }

       }
}
if(errorcount==0){
       if (s_datefrom.compare(s_dateto) ==0) {
           if(s_time_h.compare(e_time_h) >0){
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(H)."));
           }else if (s_time_m.compare(e_time_m) >0) {
               errorcount++;
               QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(min)."));
           }

           //QMessageBox :: critical(this, tr("Error"), tr("Invalied Time(H)."));
       }
}

if(errorcount==0){
qDebug() << "in else part***********************";
       if(s_type == "none"){
           qDebug() << "ship type is none";
           s_type ="";
       }
       if(s_zone == "none"){
           qDebug() << "zone is none";
           s_zone ="";
       }
       if(s_name == ""){
            qDebug() << "ship name is empty";
           s_name = "";
       }

       if(lg.connOpenImg()){
           qDebug() << " connection open..****************";
           QSqlQuery report_quary;
          // if(report_quary.prepare("SELECT * FROM img_details WHERE ship_name='"+s_name+"' AND img_time >='"+s_starttime+"' AND img_time<='"+s_endtime+"' AND img_date>='"+s_datefrom+"' AND img_date<='"+s_dateto+"' AND ship_zone='"+s_zone+"' AND ship_type='"+s_type+"'")){
          // if(report_quary.prepare("SELECT * FROM img_details WHERE ship_name='81_ship' AND img_time >='21.03.36'  AND img_time >='21.03.36' AND img_date>='01.08.2015' AND img_date<='01.08.2015' AND ship_zone='A' AND ship_type='cargo'")) {
           if(report_quary.prepare("SELECT * FROM img_details WHERE ship_name LIKE '"+s_name+"%' AND img_time >='"+s_starttime+"'  AND img_time <='"+s_endtime+"' AND img_date>='"+s_datefrom+"' AND img_date<='"+s_dateto+"' AND ship_zone LIKE '%"+s_zone+"' AND ship_type LIKE '%"+s_type+"'")) {
           qDebug() << "report genaration quary perpare ok...";
               if(report_quary.exec()){
                   qDebug() << "report genaration quary execution ok..";
                   QStringList list;


                   while (report_quary.next()) {
                       QString name = report_quary.value(1).toString();
                       QString time = report_quary.value(2).toString();
                       QString date = report_quary.value(4).toString();
                       QString zone = report_quary.value(9).toString();
                       QString type = report_quary.value(8).toString();
                       QString comment = report_quary.value(7).toString();

                       if(comment ==""){
                           comment ="";
                       }

                       QString s;
                       s.append(name+";");
                       s.append(type+";");
                       s.append(date+";");
                       s.append(time+";");
                       s.append(zone+";");
                       s.append(comment);

                       list << s;
                       qDebug() << "s.........." << s;
                   }

                   if(list.isEmpty()){
                       qDebug() << "list is empty....";
                       QMessageBox :: critical(this, tr("Error"), tr("Empty data source."));
                   }else {



                   NCReport *report = new NCReport();

                   report->setReportSource( NCReportSource::File );
                   report->setReportFile(":/report/report.xml");
                   report->addStringList(list, "model1");
                   report->runReportToPreview();

                   if (report->hasError()) {

                       qDebug() << "ERROR:" << report->lastErrorMsg();
                        //QMessageBox :: critical(this, tr("Error"), tr((report->lastErrorMsg())+"");
                   } else {

                       NCReportPreviewWindow *pv = new NCReportPreviewWindow();
                       pv->setOutput( (NCReportPreviewOutput*)report->output() );
                       pv->setWindowModality( Qt::ApplicationModal );
                       pv->setAttribute( Qt::WA_DeleteOnClose );
                       pv->show();
                   }
                   }


               }else {
                   qDebug() << "report genaration quary execution fail..";
               }

           }else{
               qDebug() << "report genaration quary perpare fail...";
           }
       lg.connCloseImg();
       }else {
           qDebug() << "could not open the image DB connection..";
       }
       }
}
//}

void controller_new::on_btn_report_clear_clicked()
{
    ui->txt_report_sname->setText("");
    ui->selectbox_report_tstart->setTime(QTime::currentTime());
    ui->selectbox_report_tend->setTime(QTime::currentTime());
    ui->dropbox_report_zone->setCurrentIndex(0);
    ui->selectbox_report_dfrom->setDate(QDate::currentDate());
    ui->selectbox_report_dto->setDate(QDate::currentDate());
    ui->dropbox_report_category->setCurrentIndex(0);

}

void controller_new::on_btn_report_gen_clicked()
{
     ui->txt_report_sname->setText("");
}

void controller_new::on_btn_adminpanel_search_clicked()
{
    QString ufullname = ui->adminPanel_full_name->text();


    QString chcknormaluser="";
     QString chckoperator="";

    if(ui->chckbox_Normaluser->isChecked() && !(ui->chckbox_operater->isChecked())){
        chcknormaluser = "Normal User";
        chckoperator = "Normal User";
        //qDebug() << "normal User++++++++++";
    }
    else if(ui->chckbox_operater->isChecked() && !(ui->chckbox_Normaluser->isChecked())){
        chckoperator = "Operator";
        chcknormaluser = "Operator";
                   // qDebug() << "Operator++++++++++";
    }
    else if(ui->chckbox_operater->isChecked() && (ui->chckbox_Normaluser->isChecked())){
        chcknormaluser = "Normal User";
        chckoperator = "Operator";
         // qDebug() << "Operator and Normal User++++++++++"  ;
    }else {
        chcknormaluser = "admin";
        chckoperator = "admin";
      //  qDebug() << "admin+++++++++++++++";
    }

    login lg;
    if(lg.connOpen()){
     QSqlQuery *qry =new QSqlQuery(lg.db);
     qDebug() << "quary open///////////////";
    //..................................................................
        //if(qry->prepare("SELECT img_id, ship_name,ship_type, img_time, img_date,ship_zone, ship_comment FROM img_details WHERE img_time>'08.45.42' AND img_date ='"+qsdate+"'")){
        if(qry->prepare("SELECT userid, fullname,usertype,username,email,homeno,street,city,contactno,postalcode FROM User WHERE fullname LIKE '%"+ufullname+"%' AND (usertype ='"+chcknormaluser+"' OR usertype ='"+chckoperator+"')")){
            qDebug() << "details prepare is ok*****************";
            if(qry->exec()){
                qry->next();
                qDebug() << "execute the quary get details...*****************";
                QString id=qry->value(1).toString();
                qDebug() << "id " <<id;
                if(id == ""){
                    QMessageBox :: information(this, tr("System Infor"), tr("Empty Data Source!"));
                   // qDebug() << "table is empty++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

                }else{
                    QSqlQueryModel * model = new QSqlQueryModel();

                    model->setQuery(*qry);

                    model->setHeaderData(0,Qt::Horizontal,QObject::tr("User ID"));
                    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Full Name"));
                    model->setHeaderData(2,Qt::Horizontal,QObject::tr("User Type"));
                    model->setHeaderData(3,Qt::Horizontal,QObject::tr("User Name"));
                    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
                    model->setHeaderData(5,Qt::Horizontal,QObject::tr("House No."));
                    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Street"));
                    model->setHeaderData(7,Qt::Horizontal,QObject::tr("City"));
                    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Postal Code"));
                    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Contact No."));

                    ui->adminPanel_usertable->setModel(model);

                    lg.connClose();
                }
            }else{
                 qDebug() << "execute details fail...***********************";
            }
        }else{
            qDebug() << "perpare details fail...*************************";
        }

        }else{
        qDebug() << "connection not open(giving piority)...";
    }
    lg.connClose();

}


void controller_new::on_adminPanel_usertable_clicked(const QModelIndex &index)
{
    int i = ui->adminPanel_usertable->selectionModel()->currentIndex().row();
    qDebug() << "index i : " << i;
    //TableModel *sqm = new QSqlQueryModel();
   // QTableView qt = new QTableView();
    QString fname = ui->adminPanel_usertable->model()->index(i,1).data().toString();
    ui->txt_adminPanel_Fname->setText(fname);
    ui->txt_adminPanel_city->setText(ui->adminPanel_usertable->model()->index(i,8).data().toString());

    ui->txt_adminPanel_contact->setText(ui->adminPanel_usertable->model()->index(i,9).data().toString());
    //ui->txt_adminPanel_postalcode->setText(ui->adminPanel_usertable->model()->index(i,10).data().toString());
    ui->txt_adminPanel_street->setText(ui->adminPanel_usertable->model()->index(i,7).data().toString());
    ui->txt__adminPanel_email->setText(ui->adminPanel_usertable->model()->index(i,5).data().toString());
    ui->txt__adminPanel_houseno->setText(ui->adminPanel_usertable->model()->index(i,6).data().toString());
    ui->txt__adminPane_uname->setText(ui->adminPanel_usertable->model()->index(i,3).data().toString());
    ui->txt_adminPanel_postalcode->setText(ui->adminPanel_usertable->model()->index(i,10).data().toString());
    // user type to combo box
    if((ui->adminPanel_usertable->model()->index(i,2).data().toString())=="Operator"){
        //ui->radiobtn_adminPanel_normaluser->setChecked("false");
        ui->radiobtn_adminPanel_operator->setChecked("true");
        qDebug() << "Operator------..: ";
    }
    if((ui->adminPanel_usertable->model()->index(i,2).data().toString())=="Normal User"){
        ui->radiobtn_adminPanel_normaluser->setChecked("true");
        //ui->radiobtn_adminPanel_operator->setChecked("false");
        qDebug() << "Normal User------..: ";
    }
    if((ui->adminPanel_usertable->model()->index(i,2).data().toString())=="admin"){
        //ui->radiobtn_adminPanel_normaluser->setChecked("false");
        ui->radiobtn_adminPanel_admin->setChecked("true");
        qDebug() << "admin------..: ";
    }

}

void controller_new::on_btn_adminpanel_update_clicked()
{
    login conn;
    QString uname = ui->txt__adminPane_uname->text();
    QString chckoperator="";
    QString chcknormaluser="";

   if(ui->radiobtn_adminPanel_normaluser->isChecked()){
       chcknormaluser = "Normal User";
       chckoperator = "Normal User";
       qDebug() << "normal User+++++++++*************************************************";
   }
   else if(ui->radiobtn_adminPanel_operator->isChecked()){
       chckoperator = "Operator";
       chcknormaluser = "Operator";
                   qDebug() << "Operator++++++++++//////////////////////////////////////////";
   }
    if(conn.connOpen()){
        // ui->lbl_change_password->setText("connect to DB..");

        QSqlQuery update_quary;


        //connOpen();
        //update_quary.prepare("UPDATE User SET usertype = '"+chckoperator+"' WHERE username = '"+uname+"'");
        //QMessageBox :: information(this, tr("Error"), tr("urrent date  Invalied Time(hh)."));
        update_quary.prepare("UPDATE User SET usertype = '"+chcknormaluser+"' WHERE username = '"+uname+"'");

        if(update_quary.exec()){

            //int check = 0;

            qDebug() << " ok...";

            update_quary.next();
            conn.connClose();
            QMessageBox::information(this,tr("Success"),tr("Update user profile successfuly!"));

            ui->txt_adminPanel_city->setText("");
            ui->txt_adminPanel_contact->setText("");
            ui->txt_adminPanel_Fname ->setText("");
            ui->txt_adminPanel_postalcode->setText("");
            ui ->txt_adminPanel_street->setText("");
            ui->txt__adminPane_uname->setText("");
            ui ->txt__adminPanel_email ->setText("");
            ui ->txt__adminPanel_houseno->setText("");
            ui ->txt_adminPanel_postalcode ->setText("");
            ui->radiobtn_adminPanel_normaluser->setChecked("false");
            ui->radiobtn_adminPanel_operator->setChecked("false");


        }else{
            //ui->lbl_change_password->setText("wrrong quary...");
            qDebug() << "wrrong quay";
        }


    }else{
        //ui->lbl_change_password->setText("DB doesn't open..");
        qDebug() << "Fail to open DB";
        return;
    }
    }


void controller_new::on_btn_map_clear_clicked()
{
    ui->txt_map_sname->setText("");

    ui->tedit_map_start->setTime(QTime::currentTime());
    ui->tedit_map_end->setTime(QTime::currentTime());

    ui->dedit_map_date->setDate(QDate::currentDate());
    //ui->selectbox_report_dto->setDate(QDate::currentDate());
    ui->cbox_map_zone->setCurrentIndex(0);
    ui->cbox_map_category->setCurrentIndex(0);
}

void controller_new::on_btn_adminpanel_clear_clicked()
{
    ui->adminPanel_full_name->setText("");
}
