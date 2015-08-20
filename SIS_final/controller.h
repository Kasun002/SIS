#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>

namespace Ui {
class controller;
}

class controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit controller(QWidget *parent = 0);
    ~controller();

private:
    Ui::controller *ui;
};

#endif // CONTROLLER_H
