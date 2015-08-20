#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QDialog>
#include "login.h"
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QWidget>

namespace Ui {
class change_password;
}

class change_password : public QDialog
{
    Q_OBJECT

public:
    explicit change_password(QWidget *parent = 0);
    ~change_password();

private slots:
    void on_btn_changepass_clear_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::change_password *ui;
};

#endif // CHANGE_PASSWORD_H
