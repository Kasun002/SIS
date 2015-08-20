#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <QMainWindow>

namespace Ui {
class registeruser;
}

class registeruser : public QMainWindow
{
    Q_OBJECT

public:
    explicit registeruser(QWidget *parent = 0);
    ~registeruser();

private:
    Ui::registeruser *ui;
};

#endif // REGISTERUSER_H
