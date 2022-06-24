#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#endif // MAINWINDOW_H

#include <QWidget>
#include "battlefield.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QAction>
#include <QMenuBar>
#include <qapplication.h>
#include <QMainWindow>
class QGraphicsScene;
class QGraphicsView;

const int TILE_SIZE = 10;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    BattleField battle_field;
    QColor enemy_color;
    QColor safe_color;
    QColor path_color;
    int areaNum = 0;
    QPainterPath path;

public:
    MainWindow(QWidget *parent = nullptr);
    // use data in the file to init the battle field
    void load_data();
    void createActions();
    void createMenus();
    void initScene();
    void initSceneBackground();
   // void paint(QPainter *painter,QWidget *);

    QGraphicsScene *scene;
    QGraphicsView *view;
    QAction *loadFile;
    QRectF boundingRect(qreal x1, qreal y1, qreal x2,qreal y2);
    QPainterPath shape();


protected:
    // draw battle field
    void paintEvent(QPaintEvent *event) override;
    // listen to the key press event
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void load_file();

};
