#include "mainwindow.h"
#include <QPainter>
#include <QDebug>
using namespace std;
using namespace RECTILINEAR_STEINER_TREE;

MainWindow::MainWindow(istream &is, QWidget *parent)
    : QMainWindow(parent)
{
    is >> layout;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    const PointSet& pointSet=layout.getPointSet();
    const std::vector<Layout::Wire> wires=layout.getWires();
    const double mul=10;
    const int R=4;
    const int der=20;
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    for (const Point &p: pointSet)
    {
        painter.drawEllipse(p.x*mul-R/2+der,p.y*mul-R/2+der,R,R);
        //painter.drawText(p.x*mul-R/2+der,p.y*mul-R/2+der,QString::number(p.x)+","+QString::number(p.y));
        qDebug() << p.x << " " << p.y;
    }
    for (const Layout::Wire &l: wires)
    {
        painter.drawLine(l.a.x*mul+der,l.a.y*mul+der,l.b.x*mul+der,l.b.y*mul+der);
        qDebug() << l.a.x << " "  << l.a.y << " " << l.b.x << " " << l.b.y <<endl;
    }
}

MainWindow::~MainWindow()
{

}
