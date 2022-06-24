#include "mainWindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <iostream>
#include <QFileDialog>
#include <QtDebug>
#include <fstream>
#include <sstream>
#include <string.h>
#include <QString>
#include <QGraphicsView>
#include <QPointF>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this))
{
    // set window title
    setWindowTitle(tr("Find Way To Exit!!!"));
    // @TODO write your codes here
    setCentralWidget(view);
    setFixedSize(1000, 1000);
    createActions();
    createMenus();
    initScene();
    initSceneBackground();

}

void MainWindow::load_data(){
    // @TODO write your codes here
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    // @TODO write your codes here
}

void MainWindow::load_file()  // slot 函数
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("文件对话框！"),
                                                        "F:",
                                                        tr("文本文件(*txt)"));
        qDebug()<<"filename : "<<fileName;
        std::string str = fileName.toStdString();
        std::ifstream file(str);
        std::string line;
        getline(file, line);
        this->areaNum = line[0] - '0';  // 敌人区域个数
    std::cout<<areaNum;
        int pos1,pos2 ;
        int x[4];
        for(int i = 0; i < areaNum; i++){
            getline(file ,line);
            pos1 = 0;

            for(int j = 0; j < 4; j++)  {
                   pos2 = line.find(' ', pos1 + 1);
            std::string str = (line.substr(pos1, pos2 - pos1));
            x[j] = stoi(str);
            pos1 = pos2 + 1;
        }
           path.addRect(boundingRect(x[0],x[1],x[2],x[3]));
           QPixmap bg(TILE_SIZE, TILE_SIZE);
           QPainter p(&bg);
           p.setBrush(QBrush(Qt::red));
           this->battle_field.enemy(x[0],x[1],x[2],x[3]);   // 设置敌人
           update();
        }
        this->battle_field.findPath();  // 输出路径
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // @TODO write your codes here
    painter.save();
    painter.fillPath(shape(), Qt::yellow);
    painter.restore();
}

void MainWindow::createMenus(){
    QMenu *options = menuBar()->addMenu(tr("&Options"));
    options->addAction(loadFile);
}

void MainWindow::createActions(){
    loadFile = new QAction(tr("&Load File"), this);
    loadFile->setShortcuts(QKeySequence::New);
    loadFile->setStatusTip(tr("Start a new game"));
    connect(loadFile, SIGNAL(triggered()), this, SLOT(load_file()));
}

void MainWindow::initScene(){
      scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground(){
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    view->setBackgroundBrush(QBrush(bg));
}

//void MainWindow::paint(QPainter *painter, QWidget *)
//{
//    painter->save();
//    painter->fillPath(shape(), Qt::yellow);
//    painter->restore();
//}

QRectF MainWindow::boundingRect(qreal x1, qreal y1, qreal x2,qreal y2)
{
    qreal minx= x1;
    qreal miny = y1;
    qreal maxx= x2;
    qreal maxy = y2;
    QPointF tl,br;
    tl.rx() = minx;
    tl.ry() = miny;
    br.rx() = maxx;
    br.ry() = maxy;

    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + 10,      // width
                          br.y() - tl.y() + 10       //height
                          );
    return bound;
}

QPainterPath MainWindow::shape()
{
    return path;
}


