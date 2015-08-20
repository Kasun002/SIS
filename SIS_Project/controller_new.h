#ifndef CONTROLLER_NEW_H
#define CONTROLLER_NEW_H

#include <QDialog>
#include "login.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "map_view.h"
#include "show_image.h"

namespace Ui {
class controller_new;
}

class controller_new : public QDialog
{
    Q_OBJECT

public:
    explicit controller_new(QWidget *parent = 0);
    ~controller_new();

    static QImage qimg;
    static QImage qshowimage;
     QTimer *timer; // timer pointer

private slots:
    void on_btn_pro_edit_search_clicked();

    void on_btn_pro_edit_update_clicked();

    void on_btn_pro_edit_update_2_clicked();

    void on_btn_pro_edit_clear1_clicked();

    void on_btn_pro_edit_clear_2_clicked();

    void on_btn_pro_edit_reset_2_clicked();

    void on_btn_pro_edit_search_3_clicked();

    void on_btn_pro_view_clear_clicked();

    void on_table_controllnew_home_activated(const QModelIndex &index);

    void on_btn_home_repress_clicked();

    void on_table_controllnew_home_clicked(const QModelIndex &index);

    void on_btn_home_update_clicked();

    void on_btn_home_clear_clicked();

    void on_btn_home_reset_clicked();

    void on_btn_map_genarate_clicked();

    void on_btn_home_show_clicked();

    //inline cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true );

    void on_btn_report_genarate_clicked();

    void on_btn_report_clear_clicked();

    void on_btn_report_gen_clicked();

    void ShipDBUpadate();

    void on_btn_adminpanel_search_clicked();

    void on_adminPanel_usertable_clicked(const QModelIndex &index);

    void on_btn_adminpanel_update_clicked();

    void on_btn_map_clear_clicked();

    void on_btn_adminpanel_clear_clicked();

private:
    Ui::controller_new *ui;
};

#endif // CONTROLLER_NEW_H

//void controller_new::on_btn_report_genarate_clicked();

