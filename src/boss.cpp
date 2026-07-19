#include "boss.h"

Boss::Boss(Load::BOSS& w)
    :BaseRole(w.base_param)
    , hp_ (w.hp)
{

}
int Boss::hp() const
{
    return hp_;
}
void Boss::change_hp(int hp)
{
    hp_ += hp;
}
void Boss::update(double fixed_step)
{
    if(on_ground_){
        jump_count_=0;
    }

    //was_on_ground=on_ground;
    if(on_ground_ && vy_ >= 0)
    {
        vy_ = 0;
    }
    else {
        vy_ += ga*fixed_step;
        y_ += vy_*fixed_step;
    }
    rect_.moveTo(x_, y_);

    //可以有--后来可以加上控制--控制有无上界限制
    if(y_<=0){
        y_=0;
        vy_=0;
    }
}