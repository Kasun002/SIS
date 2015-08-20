#ifndef REGISTER_NEW_H
#define REGISTER_NEW_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QWidget>
#include "login.h"
#include "cheack_register_dialogbox.h"

namespace Ui {
class register_new;
}

class register_new : public QDialog
{
    Q_OBJECT

public:
    explicit register_new(QWidget *parent = 0);
    ~register_new();

private slots:
    void on_btn_reg_clear_2_clicked();

    void on_btn_reg_register_2_clicked();

    void on_btn_reg_back_clicked();

private:
    Ui::register_new *ui;
};

#endif // REGISTER_NEW_H
