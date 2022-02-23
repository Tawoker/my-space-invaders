#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    army = new AlienArmy();
    ship = new Spaceship(7);
    ui->label->setGeometry(TEXT_PADDING, 0, STATUS_TEXT_WIDTH, DEFAULT_VERTICAL_PADDING);
    ui->label_2->setGeometry(GAMEWINDOW_SIZE - STATUS_TEXT_WIDTH - TEXT_PADDING, 0, STATUS_TEXT_WIDTH, DEFAULT_VERTICAL_PADDING);
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer ->start(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent( QPaintEvent *event )
{
    QPainter painter(this);
    army->drawAlienArmy(&painter);
    army->drawBombs(&painter);
    ship->unitDraw(&painter);
    ship->drawMissiles(&painter);
}

void MainWindow::keyPressEvent( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Left){
        ship->setUnitDirection(LEFT);
    }
    if(event->key() == Qt::Key_Right){
        ship->setUnitDirection(RIGHT);
    }
    if(event->key() == Qt::Key_Space){
        ship->createMissile();
    }
}

void MainWindow::keyReleaseEvent( QKeyEvent * event )
{
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        ship->setUnitDirection(STATIC);
}

void MainWindow::update()
{
    army->move();
    army->bombsMove();
    ship->moveMissiles();
    ship->reloadTimer();
    ship->unitMove();
    collisionManager();
    army->lvlUpCheck();
    army->bombReloadTimer();
    ui->label->setText("Число жизней: " + QString::number(ship->getLifes()));
    ui->label_2->setText("Количество очков : " + QString::number(ship->getScore()));
    repaint();
}

bool MainWindow::checkCollision(QRectF object1, QRectF object2)
{
    return object1.intersects(object2);
}

void MainWindow::collisionManager()
{
    bool flag = false;
    for (int i = 0; i < ship->getMissiles().size(); i++) {
        for (int j = 0; j < army->getAlienArmy().size(); j++ ) {
            flag = false;
            for (int k = 0; k < army->getAlienArmy()[j].size(); k++){
                if (checkCollision(ship->getMissiles()[i], army->getAlienArmy()[j][k]->getUnitRect())){
                    flag = true;
                    ship->getMissiles().remove(i);
                    i--;
                    army->getAlienArmy()[j].remove(k);
                    k--;
                    ship->addScore();
                    break;
                }
            }
            if (flag)
                break;
        }

    }
    for(int l = 0; l < army->getBombs().size(); l++)
        if (checkCollision(ship->getUnitRect(), army->getBombs()[l])){
            army->getBombs().remove(l);
            ship->lossOneLife();
            if (ship->getLifes() == 0)
                qApp->exit();
        }
    army->boardCollision();
    ship->missileBoardCollision();
}
