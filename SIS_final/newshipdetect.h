#ifndef NEWSHIPDETECT_H
#define NEWSHIPDETECT_H

#include <QDialog>

namespace Ui {
class NewShipDetect;
}

class NewShipDetect : public QDialog
{
    Q_OBJECT

public:
    explicit NewShipDetect(QWidget *parent = 0);
    ~NewShipDetect();

private:
    Ui::NewShipDetect *ui;
};

#endif // NEWSHIPDETECT_H
