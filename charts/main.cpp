#include "mainwindow.h"
#include "filesview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    FilesView win(0);
//    win.show();
    return a.exec();
}
