#include "spaceship.h"
QImage defaultSpaceshipImage(":/images/ship.png");
QImage defaultMissileImage(":/images/missile.png");

Spaceship::Spaceship(float speed)
{
    unitImage = &defaultSpaceshipImage;
    unitSpeed = speed;
    size = GAMEWINDOW_SIZE * sizeRatio;
    bottomPadding = GAMEWINDOW_SIZE * bottomPaddingRatio;
    int x, y;
    x = ((GAMEWINDOW_SIZE - size)/2);
    y = GAMEWINDOW_SIZE - size - bottomPadding;
    unitRect = QRectF(x, y, size, size);
    missileImage = &defaultMissileImage;
    missileHeight = size * mHeightRatio;
    missileWidth = size * mWidthRatio;
}

void Spaceship::createMissile()
{
    if (reload == reloadTime){
        xMissile = unitRect.x() + (size - missileWidth)/2;
        yMissile = unitRect.y() - missileHeight;
        QRectF missle(xMissile, yMissile, missileWidth, missileHeight);
        missiles.append(missle);
        reload = 0;
    }
}

void Spaceship::drawMissiles(QPainter *painter)
{
    for(int i = 0; i < missiles.size(); i++)
        painter->drawImage(missiles[i], *missileImage);
}

void Spaceship::moveMissiles()
{
    for (int i = 0; i < missiles.size(); i++)
        missiles[i].translate(0, -missileSpeed);
}

QVector<QRectF> &Spaceship::getMissiles()
{
    return missiles;
}

void Spaceship::reloadTimer()
{
    if (reload < reloadTime)
        reload++;
}

void Spaceship::missileBoardCollision()
{
    for (int i = 0; i < missiles.size(); i++)
        if (missiles[i].intersects(upOutOfGamewindow))
            missiles.remove(i);
}

void Spaceship::unitMove()
{
    switch (unitDirection) {
    case LEFT:
        if(unitRect.left() >= LEFT_BOARD_X + unitSpeed)
            unitRect.translate(-unitSpeed, 0);
        break;
    case RIGHT:
        if(unitRect.right() <= RIGHT_BOARD_X - unitSpeed)
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

int Spaceship::getLifes() const
{
    return lifes;
}

void Spaceship::lossOneLife()
{
    lifes--;
}

int Spaceship::getScore() const
{
    return score;
}

void Spaceship::addScore()
{
    score += 500;
}


