#include "battlefield.h"
#include <iostream>
BattleField::BattleField(int width, int height, Load::world& world_config)
    :width_(width), height_(height)
    , bullets_param_(world_config.bullets)
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
        bulletsManagement(fixed_step);

        player_->update(fixed_step);
        if(!intersectWithGround(player_))
        { player_->setOnGround(false);};    //最好不要在碰撞检测里面判断地面，可以再做一个小区域地面接触检测
        
        boss_->update(fixed_step);
        if(!intersectWithGround(boss_ ))
        { boss_ ->setOnGround(false);}      //这一步 ！没有和任何地面交互则为离地

        accumulator -= fixed_step;
    }

    qDebug() << "[[PLAYER]]::"
        << "[position]:("<< player_->x() << player_->y() << ")" 
        <<" [v]:("<< player_->vx() << player_->vy() <<")"
        <<" [on ground]:"<< player_ ->isOnGround();

    qDebug() << "[[BOSS]]::"
        << "[position]:("<< boss_->x() << boss_->y() << ")" 
        <<" [vy]:"<< boss_ ->vy() 
        <<" [on ground]:"<< boss_ ->isOnGround();
    qDebug() << "--------------------------------------------";
}

void BattleField::bulletsManagement(double fixed_step)
{
    auto it = bullets_.begin();
    while (it != bullets_.end()) {
        Bullet* bullet = *it;

        if (!bullet->is_active()) {
            it = bullets_.erase(it);
            delete bullet;
            continue;///////////////////////////////////
        } 

        bullet->update(fixed_step);
        
        bool intersected = false;
        QPointF cter = bullet->pos() + QPointF(bullet->radius(), bullet->radius());

        //地面
        for(auto& gnd :ground_rects_)
        {
            if(LineSegmentCircleIntersect(gnd.topLeft() , gnd.bottomLeft(), cter, bullet->radius(), 0))  intersected = true;
            if(LineSegmentCircleIntersect(gnd.topLeft() , gnd.topRight()  , cter, bullet->radius(), 0))  intersected = true;
            if(LineSegmentCircleIntersect(gnd.topRight(), gnd.bottomRight(), cter, bullet->radius(), 0)) intersected = true;
            if(LineSegmentCircleIntersect(gnd.bottomLeft(), gnd.bottomRight(), cter, bullet->radius(), 0)) intersected = true;
        }
        if(intersected){
            bullet->set_active(false); 
            continue;
        }
        //boss攻击，玩家检测
        if(bullet->belonging() == Belonging::boss)
        {
            QRect player_rect = player_ ->rect();
            if(LineSegmentCircleIntersect(player_rect.topLeft() , player_rect.bottomLeft(), cter, bullet->radius(), 2))  intersected = true;
            if(LineSegmentCircleIntersect(player_rect.topLeft() , player_rect.topRight()  , cter, bullet->radius(), 2))  intersected = true;
            if(LineSegmentCircleIntersect(player_rect.topRight(), player_rect.bottomRight(), cter, bullet->radius(), 2)) intersected = true;
            if(LineSegmentCircleIntersect(player_rect.bottomLeft(), player_rect.bottomRight(), cter, bullet->radius(), 2)) intersected = true;
        
            if(intersected){
                bullet->set_active(false); 
                continue;
            }
        }
        
        //玩家攻击，boss检测
        if(bullet->belonging() == Belonging::player)
        {
            QRect boss_rect = boss_ ->rect();
            if(LineSegmentCircleIntersect(boss_rect.topLeft() , boss_rect.bottomLeft(), cter, bullet->radius(), 3))  intersected = true;
            if(LineSegmentCircleIntersect(boss_rect.topLeft() , boss_rect.topRight()  , cter, bullet->radius(), 3))  intersected = true;
            if(LineSegmentCircleIntersect(boss_rect.topRight(), boss_rect.bottomRight(), cter, bullet->radius(), 3)) intersected = true;
            if(LineSegmentCircleIntersect(boss_rect.bottomLeft(), boss_rect.bottomRight(), cter, bullet->radius(), 3)) intersected = true; 
            
            if(intersected){
                bullet->set_active(false); 
                boss_->change_hp(-1* bullet->damage());
                qDebug() << boss_->hp();
                continue;
            }
        }

        //出界了
        if (bullet->x() < 0 || bullet->x() > width_ || bullet->y() < 0 || bullet->y() > height_) {
            bullet->set_active(false);
        }
        ++it;
    }
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
    // 使用 role 的实际浮点坐标，避免 int 截断造成左右移不对称
    double rx = role->x();
    double ry = role->y();
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
            ry = ground.top() - rect.height()+1;
        }   
        else if(left_i < bottom_i && top_i == 0 )    //下面的
        {
            role -> setVy(0);
            ry = ground.bottom()+1;
        }
        else  //左侧
            rx = ground.left() - rect.width()- 1;

    }else if(right_i && !left_i){
        if(right_i < top_i && bottom_i==0 )   //上方
        {
            role ->setOnGround(true);
            role ->setVy(0);
            ry = ground.top() - rect.height()+1;
        }   
        else if(right_i < bottom_i && top_i == 0 )    //下面的
        {
            role -> setVy(0);
            ry = ground.bottom()+1;
        }
        else  //右侧
            rx = ground.right() + 1;
    }else {

        if( top_i && !bottom_i )   //上方
        {
            role ->setOnGround(true);
            role ->setVy(0);
            ry = ground.top() - rect.height() +1 ;
        }   
        else if( !top_i && bottom_i )    //下面的
        {
            role -> setVy(0);
            ry = ground.bottom()+1;
        }
        else{
            qDebug()<<"I DON'T KNOW";
        }  
    }
    role ->setXY(QPointF(rx, ry));
}
//Liang-Barskey，通过交线长短他是和上下左右那个边界接触更合适
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

bool BattleField::LineSegmentCircleIntersect(QPointF p1, QPointF p2, QPointF center, double radius, int tolerance)
{
    double r = radius - tolerance;  //抠点边界
    QPointF d1 = center - p1;
    if(d1.x()*d1.x()+d1.y()*d1.y()<=r*r) return true;

    QPointF d2 = center - p2;
    if(d2.x()*d2.x()+d2.y()*d2.y()<=r*r) return true;

    QPointF ab = p2 - p1;
    QPointF ac = center - p1;

    //投影比例
    //vector(a) * vector(b)  = |vector(a)| * |vector(b)| *cos<a, b>
    //cos<a, b> * |vector(b)| = [vector(a)*vector(b)] / |vector(a)| * |vector(b)|
    //                        = [vector(a)*vector(b)] / |vector(a)|             //向量b在向量a上的投影
    //在此基础上再除以|vector(a)|得到向量b在向量a上的投影比例,即t,  doProduct--点乘
    double t = QPointF::dotProduct(ab, ac) / QPointF::dotProduct(ab, ab);

    //端点离圆心更近，而端点在圆内已经被排除了
    if(t>1 || t<0) return false;

    QPointF foot = p1 + t * ab;
    QPointF dis = center - foot;
    if(dis.x()*dis.x()+dis.y()*dis.y()<=r*r) return true;
    else return false;
}

void BattleField::keySetHandle()//按键的映射搬到了这里
{
    int speed=1;
    if(key_set_.contains(Qt::Key_Shift)) speed=3;//shift加速
    
    //左右移动
    bool contain_a = key_set_.contains(Qt::Key_A);
    bool contain_d = key_set_.contains(Qt::Key_D);

    if(contain_a && !contain_d) {   // <-
        player_->setVx(-150 * speed) ;   //左
        player_->set_facing(-1);
    }
    else if(!contain_a && contain_d) {   // ->
        player_->setVx(150 * speed);
        player_->set_facing(1);
    }
    else{
        player_->setVx(0) ;
    }

    //二段跳控制
    if(key_set_.contains(Qt::Key_W) && player_->return_jump_requestd_()) //长按也只能跳一次
    {
        player_ ->jump(-400);
    }

    //空格发射
    if(key_set_.contains(Qt::Key_Space) 
        && player_->return_fire_requestd_())
    {
        double bullet_radius=bullets_param_[0].radius;
        //这里的点是左上角，和矩形一样！！！！！！
        QPointF p(player_->x(), player_->y() + player_->rect().height()/2.0 - bullet_radius);
        int facing =player_->return_facing();

        //朝向和人物宽度问题
        if(facing == -1){
            p.setX(p.x() - bullet_radius * 2) ;
        } else {
            p.setX(p.x() + player_->rect().width() );
        }   
        double vx = bullets_param_[0].velocity;
        QPointF pv(100 * vx * facing, 0);
        //传的参数尽量通过外部配置(json)
        Bullet* bullet=new Bullet(Belonging::player, BulletType::Circle
                            , p, bullet_radius, player_->basicDamage() , true );
        
        bullet->setV(pv);

        bullets_.append(bullet);//加入子弹列表
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

