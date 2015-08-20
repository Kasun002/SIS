#ifndef DI0ALOG_ADD_H
#define DI0ALOG_ADD_H

#include <QDialog>

namespace Ui {
class Di0alog_add;
}

class Di0alog_add : public QDialog
{
    Q_OBJECT

public:
    explicit Di0alog_add(QWidget *parent = 0);
    ~Di0alog_add();

private:
    Ui::Di0alog_add *ui;
};

#endif // DI0ALOG_ADD_H
