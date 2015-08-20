#ifndef SHOW_IMAGE_H
#define SHOW_IMAGE_H

#include <QDialog>
#include "controller_new.h"

namespace Ui {
class show_image;
}

class show_image : public QDialog
{
    Q_OBJECT

public:
    explicit show_image(QWidget *parent = 0);
    ~show_image();

private:
    Ui::show_image *ui;
};

#endif // SHOW_IMAGE_H
