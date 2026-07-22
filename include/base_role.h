#ifndef _BASE_ROLE_H
#define _BASE_ROLE_H
#include <Qrect>
#include "load.h"
const float ga=1000; //重力加速度

class BaseObject    //抽象出来最基础的类，还可以套子弹上
{
public:
    BaseObject(double x, double y);
    BaseObject(QPointF p);
public:
    double x() const;
    double y() const;
    double vx() const;
    double vy() const;
    QPointF pos() const;
    QPointF v() const;
public:
    void setVx(double vx);
    void setVy(double vy);
public:
    virtual void setV(QPointF v);
    virtual void setXY(QPointF pos);
    virtual void moveBy(double dx, double dy);

protected:
    QPointF pos_;
    QPointF v_;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class BaseRole:public BaseObject
{
public://构造函数
    BaseRole(QRect role_rect,int max_jump_count=2,int hp=20);
    BaseRole(Load::BASR_ROLE& base_param);

public://虚函数-纯
    virtual void update(double fixed_step)=0;
    ///////////////////////

public: //const函数
    
    bool isOnGround() const;
    QRect rect() const;
    int return_facing() const; //返回朝向
    bool can_jump(); //是否可以跳跃
    int hp() const;
    

public://Setter-修改器
    void setXY(QPointF pos) override;
    void moveBy(double dx, double dy) override;

    void change_hp(int hp);
    void setOnGround(bool is_on_ground);
    void set_facing(int facing); //设置朝向
    void jump(float jump_vy); //跳跃

protected:
    QRect rect_;

    int hp_;

    bool on_ground_;
    int facing_=-1; //-1为左 1为右
    int jump_count_;
    int max_jump_count_;

};


#endif //_BASE_ROLE_H