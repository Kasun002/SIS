#include "controller.h"
#include "ui_controller.h"

controller::controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controller)
{
    ui->setupUi(this);

    login lg;
    QSqlQueryModel * model = new QSqlQueryModel();
    lg.connOpen();
    QSqlQuery* qry = new QSqlQuery(lg.db);

    qry->prepare("SELECT * FROM Ship_Details");
    qry->exec();
    model->setQuery(*qry);
    ui->tab_controll_home->setModel(model);
    lg.connClose();

}

controller::~controller()
{
    delete ui;
}
