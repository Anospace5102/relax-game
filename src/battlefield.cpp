#include "battlefield.h"
#include <iostream>
BattleField::BattleField(int width, int height, Load::world& world_config)
    :width_(width), height_(height)
{
    ground_rects_.clear();   //地线
    ground_rects_ = world_config.grounds;

    player_ = new Player(world_config.player[0]); //玩家
    boss_ = new Boss(world_config.boss[0]);

    //逻辑时钟开始
    if(!logical_timer_.isValid()) logical_timer_.start();
}


void BattleField::update()
{
    double delta_time=logical_timer_.elapsed()/1000.0; //单位：秒
    logical_timer_.restart();

    //>0.1超时
    if(delta_time > 0.1) delta_time = 0.1;
    static double accumulator = 0.0;
    const double fixed_step = 1.0 / 100.0;    //固定时间步长

    //把外界60帧间隔调用的时间间隔加上
    accumulator += delta_time;
    while(accumulator >= fixed_step)        //以固定时间步长为单位处理
    {
        //按键处理
        keySetHandle();

        player_->update(fixed_step);
        if(!intersectWithGround(player_))
        { player_->setOnGround(false);};    //最好不要在碰撞检测里面判断地面，可以再做一个小区域地面接触检测
        
        boss_->update(fixed_step);
        if(!intersectWithGround(boss_ ))
        { boss_ ->setOnGround(false);}      //这一步 ！没有和任何地面交互则为离地
        
        accumulator -= fixed_step;
    }


    // qDebug() << "[[PLAYER]]::"
    //     << "[position]:("<< player_->x() << player_->y() << ")" 
    //     <<" [vy]:"<< player_ ->vy() 
    //     <<" [on ground]:"<< player_ ->isOnGround();

    // qDebug() << "[[BOSS]]::"
    //     << "[position]:("<< boss_->x() << boss_->y() << ")" 
    //     <<" [vy]:"<< boss_ ->vy() 
    //     <<" [on ground]:"<< boss_ ->isOnGround();
    // qDebug() << "--------------------------------------------";
}
//
QRect* BattleField::intersectWithGround(BaseRole* role)
{
    for(int i=0; i<ground_rects_.size();i++)
    {
        if(ground_rects_[i].intersected(role->rect()).isValid())
        {
            collisionHandling(role, ground_rects_[i]);
            return &ground_rects_[i];
        }
    }

    return nullptr;
}

void BattleField::collisionHandling(BaseRole* role, QRect ground)
{
    QRect rect = role->rect();
    QPoint pnt= rect.topLeft();
    //玩家为矩形，地面为四条线相交
    qreal top_i, bottom_i, left_i, right_i;
    top_i   = intersectedLength(rect, QLine(ground.topLeft(),  ground.topRight()));
    bottom_i= intersectedLength(rect, QLine(ground.bottomLeft(),ground.bottomRight()));
    left_i  = intersectedLength(rect, QLine(ground.topLeft(),  ground.bottomLeft()));
    right_i = intersectedLength(rect, QLine(ground.topRight(), ground.bottomRight()));
    
    //碰撞处理
    if(left_i && !right_i)
    {
        if(left_i < top_i && bottom_i==0 )   //上方
        {
            role ->setOnGround(true);
            role ->setVy(0);
            pnt.setY(ground.top() - rect.height()+1);
        }   
        else if(left_i < bottom_i && top_i == 0 )    //下面的
        {
            role -> setVy(0);
            pnt.setY(ground.bottom()+1);
        }
        else  //左侧
            pnt.setX(ground.left() - rect.width()- 1);

    }else if(right_i && !left_i){
        if(right_i < top_i && bottom_i==0 )   //上方
        {
            role ->setOnGround(true);
            role ->setVy(0);
            pnt.setY(ground.top() - rect.height()+1);
        }   
        else if(right_i < bottom_i && top_i == 0 )    //下面的
        {
            role -> setVy(0);
            pnt.setY(ground.bottom()+1);
        }
        else  //右侧
            pnt.setX(ground.right() + 1);
    }else {

        if( top_i && !bottom_i )   //上方
        {
            role ->setOnGround(true);
            role ->setVy(0);
            pnt.setY(ground.top() - rect.height() +1) ;
        }   
        else if( !top_i && bottom_i )    //下面的
        {
            role -> setVy(0);
            pnt.setY(ground.bottom()+1);
        }
        else{
            qDebug()<<"I DON'T KNOW";
        }  
    }
    role ->setXY(pnt);
}
//Liang-Barskey
qreal BattleField::intersectedLength(const QRectF &rect, const QLineF &line) 
{
    QPointF p1 = line.p1();
    QPointF p2 = line.p2();
    QPointF d = p2 - p1; // 方向向量
    
    // 1. 初始化参数 t1=0, t2=1（表示线段起点到终点）
    qreal t1 = 0.0;
    qreal t2 = 1.0;
    
    // 2. 分别处理矩形的四条边（左、右、上、下）
    // 边的参数方程：p = -d.x 或 d.x 等
    qreal p, q;
    auto clip = [&](qreal p, qreal q) -> bool {
        if (p == 0) {
            // 线段与边平行
            if (q < 0) return false; // 完全在外部
        } else if (p < 0) {
            // 计算进入点
            qreal t = q / p;
            if (t > t1) t1 = t;
        } else { // p > 0
            // 计算离开点
            qreal t = q / p;
            if (t < t2) t2 = t;
        }
        return true;
    };
    
    // 左边界 (x = rect.left())
    if (!clip(-d.x(), p1.x() - rect.left())) return 0.0;
    // 右边界 (x = rect.right())
    if (!clip(d.x(), rect.right() - p1.x())) return 0.0;
    // 上边界 (y = rect.top())
    if (!clip(-d.y(), p1.y() - rect.top())) return 0.0;
    // 下边界 (y = rect.bottom())
    if (!clip(d.y(), rect.bottom() - p1.y())) return 0.0;
    
    // 3. 检查裁剪后的参数是否有效
    if (t1 > t2 || t2 < 0 || t1 > 1) {
        return 0.0; // 无交集
    }
    
    // 4. 计算交集线段的两端点
    QPointF enterPoint = p1 + t1 * d;
    QPointF exitPoint = p1 + t2 * d;
    
    // 5. 返回两点间的距离（即相交部分的长度）
    return QLineF(enterPoint, exitPoint).length();
}

void BattleField::keySetHandle()
{
    int speed=1;
    if(key_set_.contains(Qt::Key_Shift)) speed=3;//shift加速
    if(key_set_.contains(Qt::Key_A)) {
        player_->deltaX(-2*speed);   //左
        player_->set_facing(-1);
    }
    if(key_set_.contains(Qt::Key_D)) {
        player_->deltaX(2*speed);    //右
        player_->set_facing(1);
    }
    if(key_set_.contains(Qt::Key_W) && player_->return_jump_requestd_()) //长按也只能跳一次
    {//二段跳控制
        player_ ->jump(-400);
    }
}

void BattleField::addKey(int key)
{
    key_set_.insert(key);
}

void BattleField::removeKey(int key)
{
    key_set_.remove(key);
}

void BattleField::keySpaceHandle()
{
    player_->request_fire();
}

void BattleField::keyWHandle()
{
    player_->request_jump();
}
