#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <QDialog>

namespace Ui {
class registerUser;
}

class registerUser : public QDialog
{
    Q_OBJECT

public:
    explicit registerUser(QWidget *parent = 0);
    ~registerUser();

private:
    Ui::registerUser *ui;
};

#endif // REGISTERUSER_H
