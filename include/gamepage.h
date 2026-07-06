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

//游戏页面
class GamePage:public QWidget
{
public:
    GamePage(int x, int y);
    void start();
    void init();
private://event
    void keyPressEvent(QKeyEvent *event)override;       //按键重写处理
    void keyReleaseEvent(QKeyEvent *event)override;

    void updateScene();
    void connections();
private:
    void load();

private:
    QSet<int> pressed_keys_;
    QTimer* game_timer_;            //更新定时器

    //QWidget <- layout_ <- view <- scene_
    QVBoxLayout *layout_;
    QGraphicsView * view_;
    QGraphicsScene *scene_;

    QGraphicsLineItem * ground_;    //地面-线

    QPixmap* player_pict_;          //人物图片
    QGraphicsPixmapItem * player_item_; //人物图片渲染


private:
    BattleField *battle_field_;     //纯逻辑游戏战场
private:
    int winx_;      //界面宽
    int winy_;      //界面高
    int player_size_;

signals:

};

#endif // GAMEPAGE_H
