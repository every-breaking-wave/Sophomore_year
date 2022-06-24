#ifndef BOARD_H
#define BOARD_H
#endif // BOARD_H

// Don't change, width = N, height = N

#include <QRectF>
#include <qpainter.h>
#define N 100
#include <vector>
class BattleField
{
public:
    int field[N][N];
    std::vector<QPoint> keyPoints;  //记录连线的点
    enum Direction {
        Left,
        Right,
        Up,
        Down
    };
    bool flag = false;
    // find path in this function
    bool findPath();
    BattleField();
    QRectF boundingRect(int x1, int y1, int x2, int y2);
    void paint(QPainter *painter, QWidget *);
    void enemy(int x1, int y1,int x2, int y2);
    void dfs(int x1, int y1);
   // QPainterPath shape() const;
};
