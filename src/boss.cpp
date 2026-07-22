#include "boss.h"

Boss::Boss(Load::BOSS& w)
    :BaseRole(w.base_param)
{}

void Boss::update(double fixed_step)
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

    if(y() <= 0){
        setXY(QPointF(x(), 0));
        setVy(0);
    }
}