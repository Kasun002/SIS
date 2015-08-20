#include "mainwindow.h"
#include <QApplication>
#include "login.h"
#include "change_password.h"
#include "controller.h"
#include "registor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    login l;
    l.show();

   change_password cp;
    //cp.show();

    controller c;
    //c.show();

    registor r;
    //r.show();

    return a.exec();
}
