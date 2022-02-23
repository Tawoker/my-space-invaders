#ifndef UNIT_H
#define UNIT_H
#include <QImage>
#include <QPainter>
#include <QRect>
#include "direction.h"
#include "game_constants.h"

class Unit
{
public:
    Unit();
    Unit(QRectF unitRect, float speed);
    void unitDraw(QPainter *painter);
    virtual void unitMove();
    Direction getUnitDirection() const;
    void setUnitDirection(Direction newUnitDirection);
    QRectF &getUnitRect();

protected:
    QRectF unitRect;
    float unitSpeed;
    QImage *unitImage = nullptr;
    Direction unitDirection = STATIC;
};

#endif // UNIT_H
