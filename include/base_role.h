#ifndef _BASE_ROLE_H
#define _BASE_ROLE_H
#include <Qrect>
#include <vector>
#include "load.h"
const float ga=1000; //重力加速度
//此基类被boss和player继承

class BaseRole{
public://构造函数
    BaseRole(QRect role_rect,int max_jump_count=2);
    BaseRole(Load::BASR_ROLE& base_param);

public://虚函数
    virtual void update(double fixed_step)=0;
    ///////////////////////


public: //const函数
    int x() const;
    int y() const;
    int vy() const;
    bool isOnGround() const;
    QRect rect() const;

    int return_facing() const; //返回朝向
    bool can_jump(); //是否可以跳跃

public://Setter-修改器
    int deltaX(int dx);  //左右移动时改变x
    void setVy(int vy);  //跳跃时改变vy
    
    void setOnGround(bool is_on_ground); 
    void setXY(int x,int y);
    void setXY(QPoint pnt);

    void set_facing(int facing); //设置朝向
    void jump(float jump_vy); //跳跃

protected:
    int x_;
    int y_;
    QRect rect_;
    float vx_=0;
    float vy_=0;

    bool on_ground_;
    int facing_=-1; //-1为左 1为右
    int jump_count_;
    int max_jump_count_;

};


#endif //_BASE_ROLE_H