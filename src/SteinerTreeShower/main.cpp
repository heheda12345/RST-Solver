#include <fstream>
#include <QApplication>
#include "mainwindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ifstream f;
    f.open("C:/Users/admin/Desktop/problem1/testcase/LRST1.out");
    MainWindow w(f);
    f.close();

    w.show();

    return a.exec();
}
