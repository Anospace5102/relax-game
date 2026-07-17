#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "battlefield.h"
#include "bullet.h"

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

    QPixmap* boss_pict_;          //boss图片
    QGraphicsPixmapItem * boss_item_; //boss图片渲染
public:
    int get_player_width();
    int get_boss_width();

private:
    BattleField *battle_field_;     //纯逻辑游戏战场
private:
    int winx_;      //界面宽
    int winy_;      //界面高
    int player_size_;
    int boss_size_;


private:
    QList<Bullet*>bullets_;  //子弹列表
signals:

};

#endif // GAMEPAGE_H