#ifndef REGISTOR_H
#define REGISTOR_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>

#include <QWidget>

//#include "login.h"

namespace Ui {
class registor;
}

class registor : public QWidget
{
    Q_OBJECT


public:

    explicit registor(QWidget *parent = 0);
    ~registor();

private slots:
    void on_btn_reg_clear_2_clicked();
    void on_btn_reg_register_2_clicked();

private:
    Ui::registor *ui;
     QSqlDatabase db;


};

#endif // REGISTOR_H
