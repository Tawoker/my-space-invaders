#include "alienarmy.h"
#include <QDebug>
#include <ctime>

QImage defaultBombImage(":/images/bomb.png");

AlienArmy::AlienArmy(int columns)
    :columns(columns)
{
    alienshipWidht = (GAMEWINDOW_SIZE/columns) * alienBoxRatio;
    alienshipHeight = ((GAMEWINDOW_SIZE * maxFillRatio)/maxLevel) * alienBoxRatio;
    verticalPadding = ((GAMEWINDOW_SIZE * maxFillRatio)/maxLevel) * paddingBoxRatio;
    horizontalPadding = (GAMEWINDOW_SIZE/columns) * paddingBoxRatio;
    bombHeight = alienshipHeight * bHeightRatio;
    bombWidth = alienshipWidht * bWidthRatio;
    bombImage = &defaultBombImage;
    spawnRows();
}

void AlienArmy::spawnRows()
{
    for (int i = 0; i < columns; i++){
        if (alienArmy.size() < columns)
            alienArmy.append(QVector<Alienship*>());
        for (int j = 0; j < level; j++){
            QRectF *alienRect = nullptr;
            alienRect = new QRectF(horizontalPadding*(1+i) + alienshipWidht*i, DEFAULT_VERTICAL_PADDING + verticalPadding*(1+2*j) + alienshipHeight*j, alienshipWidht, alienshipHeight);
            Alienship *alien = nullptr;
            alien = new Alienship(*alienRect);
            alienArmy[i].append(alien);
        }
    }
}

void AlienArmy::drawAlienArmy(QPainter *painter)
{
    for(int i = 0; i < alienArmy.size(); i++)
        for(int j = 0; j < alienArmy[i].size(); j++)
            alienArmy[i][j]->unitDraw(painter);
}

void AlienArmy::drawBombs(QPainter *painter)
{
    for(int i = 0; i < bombs.size(); i++)
        painter->drawImage(bombs[i], *bombImage);
}

void AlienArmy::move()
{
    for(int i = 0; i < alienArmy.size(); i++)
        for(int j = 0; j < alienArmy[i].size(); j++)
            alienArmy[i][j]->unitMove();
}

void AlienArmy::bombsMove()
{
    for(int i = 0; i < bombs.size(); i++)
        bombs[i].translate(0, bombSpeed);
}

void AlienArmy::boardCollision()
{
    bool flag = false;
    for(int i = 0; i < alienArmy.size(); i++){
        for(int j = 0; j < alienArmy[i].size(); j++){
            if (alienArmy[i][j]->getUnitRect().intersects(rightOutOfGamewindow) || alienArmy[i][j]->getUnitRect().intersects(leftOutOfGamewindow)){
                changeDirection();
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }
}

void AlienArmy::changeDirection()
{
    for(int i = 0; i < alienArmy.size(); i++)
        for(int j = 0; j < alienArmy[i].size(); j++){
            if (alienArmy[i][j]->getUnitDirection() == LEFT)
                alienArmy[i][j]->setUnitDirection(RIGHT);
            else
                alienArmy[i][j]->setUnitDirection(LEFT);
            alienArmy[i][j]->getUnitRect().translate(0, alienshipHeight);
        }
}

QVector<QVector<Alienship *>> &AlienArmy::getAlienArmy()
{
    return alienArmy;
}

void AlienArmy::spawnBomb(int num)
{
        int j = alienArmy[num].size()-1;
        xBomb = alienArmy[num][j]->getUnitRect().left() + (alienshipWidht - bombWidth)/2;
        yBomb = alienArmy[num][j]->getUnitRect().bottom();
        QRectF missle(xBomb, yBomb, bombWidth, bombHeight);
        bombs.append(missle);
        bombReload = 0;
}



void AlienArmy::bombReloadTimer()
{
    srand(time(NULL));
    if (bombReload < bombReloadTime)
        bombReload++;
    if (bombReload == bombReloadTime){
        int randColumn = rand()%alienArmy.size();
        while (true) {
            randColumn = rand()%alienArmy.size();
            if (!alienArmy[randColumn].empty()){
                spawnBomb(randColumn);
                break;
            }
        }
    }
}

bool AlienArmy::lvlUpCheck()
{
    for (int i = 0; i < alienArmy.size(); i++)
        if (!alienArmy[i].empty())
            return false;
    if (level < maxLevel)
        level++;
    spawnRows();
    return true;
}

QVector<QRectF> &AlienArmy::getBombs()
{
    return bombs;
}
