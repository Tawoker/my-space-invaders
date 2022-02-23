#include "unit.h"

Unit::Unit(){}

Unit::Unit(QRectF unitRect, float speed)
    :unitRect(unitRect),unitSpeed(speed)
{
}

void Unit::unitDraw(QPainter *painter)
{
    painter->drawImage(unitRect, *unitImage);
}

void Unit::unitMove()
{
    switch (unitDirection) {
    case LEFT:
        unitRect.translate(-unitSpeed, 0);
        break;
    case RIGHT:
        unitRect.translate(unitSpeed, 0);
        break;
    case UP:
        unitRect.translate(0, -unitSpeed);
        break;
    case DOWN:
        unitRect.translate(0, unitSpeed);
        break;
    default:
        break;
    }
}

Direction Unit::getUnitDirection() const
{
    return unitDirection;
}

void Unit::setUnitDirection(Direction newUnitDirection)
{
    unitDirection = newUnitDirection;
}

QRectF &Unit::getUnitRect()
{
    return unitRect;
}

