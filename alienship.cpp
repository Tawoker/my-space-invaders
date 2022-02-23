#include "alienship.h"
QImage defaultAlienshipImage(":/images/alien.png");

Alienship::Alienship(QRectF spaceshipRect, float  speed)
    :Unit(spaceshipRect, speed)
{
    unitImage = &defaultAlienshipImage;
    unitDirection = RIGHT;
}
