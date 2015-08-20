#include "map_view.h"
#include "ui_map_view.h"

map_view::map_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::map_view)
{

    ui->setupUi(this);
    ui->lbl_mapview_map->setPixmap(QPixmap::fromImage(controller_new::qimg, Qt::ColorOnly));
           // ui->lbl_image_view->setPixmap(QPixmap::fromImage(image2, Qt::ColorOnly));
}

map_view::~map_view()
{
    delete ui;

}
