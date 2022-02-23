#ifndef ALIENSHIP_H
#define ALIENSHIP_H
#include "unit.h"

class Alienship : public Unit
{
public:
    Alienship();
    Alienship(QRectF spaceshipRect, float speed = 0.65);
};

#endif // ALIENSHIP_H
