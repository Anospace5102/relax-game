#include"base_role.h"

BaseRole::BaseRole(QRect role_rect, int max_jump_count)
    : on_ground_(false)
    , rect_(role_rect)
    , jump_count_(0)
    , max_jump_count_(max_jump_count)
{
    x_ = role_rect.left();
    y_ = role_rect.top();
}

BaseRole::BaseRole(Load::BASR_ROLE& base_param)
    :rect_(base_param.role_rect) 
    , max_jump_count_(base_param.max_jump)
    , on_ground_(false)
    , jump_count_(0)
{
    x_ = rect_.left();
    y_ = rect_.top();
}
int BaseRole::x() const
{return x_;}

int BaseRole::y() const
{return y_;}

int BaseRole::vy() const
{return vy_;}

bool BaseRole::isOnGround() const
{return on_ground_;}

QRect BaseRole::rect() const
{return rect_;}

int BaseRole::return_facing() const
{ return facing_;}

bool BaseRole::can_jump()
{
    return jump_count_ < max_jump_count_;
}

/////////////////////////////////////////

int BaseRole::deltaX(int dx)
{
    x_+=dx;
    return x_;
}

void BaseRole::setVy(int vy)
{vy_=vy;}

void BaseRole::setOnGround(bool is_on_ground)
{on_ground_ = is_on_ground;}

void BaseRole::setXY(int x,int y)
{
    x_=x; y_=y;
    rect_.moveTo(x, y);
}

void BaseRole::setXY(QPoint pnt)
{
    x_ = pnt.x();
    y_ = pnt.y();
    rect_.moveTo(pnt);
}

void BaseRole::set_facing(int facing)
{
    facing_=facing;
}

void BaseRole::jump(float jump_vy)
{
    if(can_jump())
    {
        setVy(jump_vy);
        setOnGround(false);//不在地上
        jump_count_ ++;
    }
}

///////////////////////////////////////////////


