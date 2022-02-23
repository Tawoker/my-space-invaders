#ifndef ALIENARMY_H
#define ALIENARMY_H
#include "alienship.h"
#include "game_constants.h"
#include <QVector>
#include <QImage>

class AlienArmy
{
public:
    AlienArmy(int columns = 7);
    void spawnRows();
    void drawAlienArmy(QPainter *painter);
    void drawBombs(QPainter *painter);
    void move();
    void bombsMove();
    void boardCollision();
    void changeDirection();
    QVector<QVector<Alienship*>> &getAlienArmy();
    void spawnBomb(int num);
    void bombReloadTimer();
    bool lvlUpCheck();
    QVector<QRectF> &getBombs();
private:
    int level = 1;
    const int maxLevel = 5;

    QVector<QVector<Alienship*>> alienArmy;
    float columns, alienshipHeight, alienshipWidht, verticalPadding, horizontalPadding;
    const float maxFillRatio = 0.6, alienBoxRatio = 0.6, paddingBoxRatio = 0.175;

    QVector<QRectF> bombs;
    int bombHeight, bombWidth, xBomb, yBomb, bombReload = 50;
    const int bombReloadTime = 200;
    float bHeightRatio = 0.5, bWidthRatio = 0.3, bombSpeed = 4;
    QImage *bombImage = nullptr;

};

#endif // ALIENARMY_H
