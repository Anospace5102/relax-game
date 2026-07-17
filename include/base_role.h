#ifndef _BASE_ROLE_H
#define _BASE_ROLE_H
#include<QLine>
#include<vector>
const float ga=0.4; //重力加速度
//此基类被boss和player继承

class BaseRole{
public:
    BaseRole(int x,int y,int height=30,int width=20,int hp=30);

public:
    int deltaX(int dx);  //左右移动时改变x
    void setVy(int vy);  //跳跃时改变vy
    void update();   //boss自身逻辑更新
    void setOnGround(std::vector<QLine>&ground_line); //地面检测
public:
    int x() const;
    int y() const;
    int vy() const;

protected:
    void setXY(int x,int y);
protected:
    int jump_count=0;
    int max_jump_count=2;//最多二段跳,但是实际运行的时候可以跳三次，还不清楚为什么
    int height_;
    int width_;
    int x_;
    int y_;
    float vx_=0;
    float vy_=0;

    bool on_ground;
    int facing_=-1; //-1为左 1为右

public:
    int return_facing() const; //返回朝向
    void set_facing(int facing); //设置朝向

public:
    bool can_jump(); //是否可以跳跃
    void jump(float jump_vy); //跳跃
    
protected:
    int hp_; //血量
public:
    int hp() const;
    void change_hp(int hp); //改变血量（可正可负）

};


#endif //_BASE_ROLE_H