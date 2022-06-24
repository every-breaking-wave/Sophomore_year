#include "battlefield.h"
#include <iostream>
using namespace std;
// find path in this function
// you can add other functions to solve this problem
// you should print the path if you can find one
// if you can find one, return true, otherwise false
bool BattleField::findPath(){
    int y;
    for(int i =0; i< 100; i++){
        if(field[i][0]) {
            y = i;
            break;
        }
    }
  //  cout<<y;
    //dfs(0,y);
    if(flag)
        for(int i = 0; i< keyPoints.size();i++){
            std::cout<<keyPoints[0].rx()<<' '<<keyPoints[0].ry()<<endl;
        }
    if(!flag)
    {
        cout<<"can not find path."<<endl;
    }
    return flag;
}

BattleField::BattleField(){
    for(int i = 0; i < N ; i++){
        for(int j = 0 ; j < N; j++){
            field[i][j] = 0; // 表示没有敌军
        }
    }
}


QRectF BattleField::boundingRect(int x1, int y1, int x2, int y2)
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


//    QPointF tl = mapFromScene(QPointF(minx, miny));
//    QPointF br = mapFromScene(QPointF(maxx, maxy));
    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + 10,      // width
                          br.y() - tl.y() + 10       //height
                          );
    return bound;
}

void BattleField::paint(QPainter *painter, QWidget *)
{

}

void BattleField::enemy(int x1, int y1, int x2, int y2)
{
    for(int i = y1; i < y2 + 1; i++){
        for(int j = x1; j < x2 +1 ; j++){
            field[i][j] = 1;  // 敌人
        }
    }
}

void BattleField::dfs(int x1, int y1)
{
    if(flag) return;
    if(x1 == 99) {flag = true; return;}
    if(field[y1][x1] == 1) return;
    if(x1 < 0 || x1 >99 || y1 < 0|| y1 > 99) return;
    QPoint p(x1, y1);
    keyPoints.push_back(p);
  //  std::cout<<keyPoints[0].x();
    dfs(x1-1, y1);
    dfs(x1 + 1,y1);
    dfs(x1 ,y1 -1);
    dfs(x1, y1+ 1);
    keyPoints.pop_back();
    return;
}
