#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include "login.h"

namespace Ui {
class controller;
}

class controller : public QWidget
{
    Q_OBJECT

public:
    explicit controller(QWidget *parent = 0);
    ~controller();

private:
    Ui::controller *ui;
};

#endif // CONTROLLER_H
