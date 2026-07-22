#include "player.h"

Player::Player(Load::PLAYER& w)
    :BaseRole(w.base_param)
{}

void Player::request_fire()
{
    fire_requested_=true;
}

bool Player::return_fire_requestd_()
{
    bool tmp=fire_requested_;
    fire_requested_=false;
    return tmp;
}

void Player::request_jump()
{
    jump_requested_=true;
}

bool Player::return_jump_requestd_()
{
    bool tmp=jump_requested_;
    jump_requested_=false;
    return tmp;
}


void Player::update(double fixed_step)
{
    if(on_ground_){
        jump_count_=0;
    }

    if(on_ground_ && vy() >= 0)
    {
        setVy(0);
    }
    else {
        setVy(vy() + ga * fixed_step);
        moveBy(0, vy() * fixed_step);
    }

    moveBy(vx() * fixed_step, 0);

    if(y() <= 0){
        setXY(QPointF(x(), 0));
        setVy(0);
    }
}

