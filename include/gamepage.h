#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "battlefield.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>


class GamePage:public QWidget
{
public:
    GamePage(int x, int y);
    void start();
private://event
    void keyPressEvent(QKeyEvent *event)override;
    void keyReleaseEvent(QKeyEvent *event)override;

    void updateScene();
    void connections();
private:
    void load();
    void init();


private:
    QSet<int> pressed_keys_;
    QTimer* game_timer_;
    QVBoxLayout *layout_;
    QGraphicsView * view_;
    QGraphicsScene *scene_;

    QGraphicsLineItem * ground_;

    QPixmap* player_pict_;
    QGraphicsPixmapItem * player_item_;


private:
    BattleField *battle_field_;
private:
    int winx_;
    int winy_;
    int player_size_;

signals:

};

#endif // GAMEPAGE_H
