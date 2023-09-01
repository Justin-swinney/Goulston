#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Goulston");
   // QIcon icon(":/appimages/imgs/GIcon.jpg");
    //w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
