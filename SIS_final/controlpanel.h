#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QMainWindow>

namespace Ui {
class controlpanel;
}

class controlpanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit controlpanel(QWidget *parent = 0);
    ~controlpanel();

private:
    Ui::controlpanel *ui;
};

#endif // CONTROLPANEL_H
