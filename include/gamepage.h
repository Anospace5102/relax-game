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
#include <vector>

//游戏页面
class GamePage:public QWidget
{
    Q_OBJECT
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
    void drawTexts();

private:
    QTimer* game_timer_;            //更新定时器

    //QWidget <- layout_ <- view <- scene_
    QVBoxLayout *layout_;
    QGraphicsView * view_;
    QGraphicsScene *scene_;

    std::vector<QGraphicsRectItem*> grounds_;   //地面矩形
    QGraphicsBulletsItem* bullets_ = nullptr;

    QPixmap* player_pict_;          //人物图片
    QGraphicsPixmapItem * player_item_; //人物图片渲染

    QPixmap* boss_pict_;          //boss图片
    QGraphicsPixmapItem * boss_item_; //boss图片渲染

    QGraphicsSimpleTextItem* boss_hp_text;

private:
    BattleField *battle_field_;     //纯逻辑游戏战场
    int winx_;      //界面宽
    int winy_;      //界面高

signals:
    void addKey(int key);
    void removeKey(int key);
    void keySpaceSignal();
    void keyWSignal();

};

#endif // GAMEPAGE_H