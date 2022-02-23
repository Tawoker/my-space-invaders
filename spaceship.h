#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "unit.h"
#include <QVector>
#include <QString>
#include <QLabel>

class Spaceship : public Unit
{
public:
    Spaceship(float speed = 1.5);
    void createMissile();
    void drawMissiles(QPainter *painter);
    void moveMissiles();
    QVector<QRectF> &getMissiles();
    void reloadTimer();
    void missileBoardCollision();
    void unitMove();
    int getLifes() const;
    void lossOneLife();
    int getScore() const;
    void addScore();
private:
    int size, bottomPadding, lifes = 5, score = 0;
    float sizeRatio = 0.1, heightRatio = 0.05, bottomPaddingRatio = 0.025;
    QVector<QRectF> missiles;
    const int reloadTime = 30;
    int missileHeight, missileWidth, xMissile, yMissile, reload = reloadTime;
    float mHeightRatio = 0.7, mWidthRatio = 0.2, missileSpeed = 7;
    QImage *missileImage = nullptr;
};

#endif // SPACESHIP_H
