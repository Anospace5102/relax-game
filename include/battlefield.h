#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "player.h"
#include "boss.h"
#include "load.h"
#include <vector>
#include <QElapsedTimer>

class BattleField
{
public:
    BattleField(int width, int height, Load::world& world_config);
    void update();

public:
    Player *player_;    //玩家
    Boss *boss_;        //boss

private:
    //矩形rect和地面组相交接触检测
    QRect* intersectWithGround(BaseRole* role);
    //碰撞处理  //BaseRole* role类型兼容规则
    void collisionHandling(BaseRole* role, QRect ground);

private:
    int width_, height_;
    std::vector<QRect> ground_rects_;    //地面-矩形
    
    //物理引擎时钟计时器
    QElapsedTimer logical_timer_;

private:
    //LiangBarskey裁剪算法-求线段和矩形相交的长度
    qreal intersectedLength(const QRectF &rect, const QLineF &line);
    
};


#endif //