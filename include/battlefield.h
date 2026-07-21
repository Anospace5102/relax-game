#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "player.h"
#include "boss.h"
#include "load.h"
#include <vector>
#include <QElapsedTimer>
#include <QObject>
#include <QSet>

class BattleField:public QObject
{
    Q_OBJECT
public:
    BattleField(int width, int height, Load::world& world_config);
    void update();

public:
    Player *player_;    //玩家
    Boss *boss_;        //boss

public://按键与消息
    void addKey(int key);
    void removeKey(int key);

    void keySpaceHandle();
    void keyWHandle();

    

private:
    int width_, height_;
    std::vector<QRect> ground_rects_;    //地面-矩形
    
    //物理引擎时钟计时器
    QElapsedTimer logical_timer_;
    //按键集合，迁移到逻辑层
    QSet<int> key_set_;

private:
    //按键集合处理，迁移到逻辑层
    void keySetHandle();
    //矩形rect和地面组相交接触检测
    QRect* intersectWithGround(BaseRole* role);
    //碰撞处理  //BaseRole* role类型兼容规则
    void collisionHandling(BaseRole* role, QRect ground);
    //LiangBarskey裁剪算法-求线段和矩形相交的长度
    qreal intersectedLength(const QRectF &rect, const QLineF &line);
    
};


#endif //