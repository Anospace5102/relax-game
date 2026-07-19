#ifndef PLAYER_H
#define PLAYER_H
#include"base_role.h"
#include <QDebug>
#include <QLine>
#include <QRect>
#include <QPainterPath>
#include <vector>
#include "base_role.h"
#include "load.h"
class Player: public BaseRole
{
public:
    // Player(int x, int y, 
    //     int player_height=30,int player_width=20);
    Player(Load::PLAYER& w);

public: //覆写
    void update(double fixed_step) override;  

public:
    int hp() const;
    void change_hp(int hp);

    void request_fire(); //确认发射
    bool return_fire_requestd_(); //返回是否请求发射
    void request_jump(); //确认跳跃
    bool return_jump_requestd_(); //返回是否请求跳跃

private:
    int hp_;

    bool jump_requested_=false;    //是否请求跳跃
    bool fire_requested_=false;//是否请求发射

};

#endif // PLAYER_H