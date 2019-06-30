#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <vector>

#include "layout.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::istream &is, QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);

private:
    RECTILINEAR_STEINER_TREE::Layout layout;
};
#endif // MAINWINDOW_H
