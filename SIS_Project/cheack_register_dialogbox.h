#ifndef CHEACK_REGISTER_DIALOGBOX_H
#define CHEACK_REGISTER_DIALOGBOX_H

#include <QDialog>
#include "login.h"
#include "register_new.h"

namespace Ui {
class cheack_register_dialogbox;
}

class cheack_register_dialogbox : public QDialog
{
    Q_OBJECT

public:
    explicit cheack_register_dialogbox(QWidget *parent = 0);
    ~cheack_register_dialogbox();

private slots:
    void on_reg_check_btn_yes_clicked();

    void on_reg_check_btn_no_clicked();

private:
    Ui::cheack_register_dialogbox *ui;
};

#endif // CHEACK_REGISTER_DIALOGBOX_H
