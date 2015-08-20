#include "show_image.h"
#include "ui_show_image.h"

show_image::show_image(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_image)
{
    ui->setupUi(this);
     ui->lbl_showimage->setPixmap(QPixmap::fromImage(controller_new::qshowimage, Qt::ColorOnly));
}

show_image::~show_image()
{
    delete ui;
}
