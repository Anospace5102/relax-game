#ifndef _BOSS_H
#define _BOSS_H
#include"base_role.h"
class Boss: public BaseRole{
public:
    Boss(int x,int y,int height=30,int width=20,int hp=30)
    :BaseRole(x,y,height,width,hp)
    {

    };

public:
    // int deltaX(int dx);  //左右移动时改变x
    // void setVy(int vy);  //跳跃时改变vy
    // void update();   //boss自身逻辑更新

};


#endif //_BOSS_H