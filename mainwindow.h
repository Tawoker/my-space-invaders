#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include "spaceship.h"
#include "alienarmy.h"
#include "game_constants.h"
#include <QKeyEvent>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool checkCollision(QRectF object1, QRectF object2);
    void collisionManager();
public slots:
    void update();
private:
    AlienArmy *army = nullptr;
    Spaceship *ship = nullptr;
    Ui::MainWindow *ui = nullptr;
    int textBorder = 10;
};
#endif // MAINWINDOW_H
