#ifndef NCRTESTFORM_H
#define NCRTESTFORM_H

#include <QDialog>

namespace Ui {
class ncrtestform;
}

class ncrtestform : public QDialog
{
    Q_OBJECT

public:
    explicit ncrtestform(QWidget *parent = 0);
    ~ncrtestform();

private:
    Ui::ncrtestform *ui;
};

#endif // NCRTESTFORM_H
