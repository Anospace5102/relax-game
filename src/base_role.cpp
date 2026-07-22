#include"base_role.h"

BaseObject::BaseObject(double x, double y)
    : pos_ (x, y), v_(0, 0)
{}
BaseObject::BaseObject(QPointF p)
    :BaseObject(p.x(), p.y())
{}

double BaseObject::x() const
{return pos_.x();}

double BaseObject::y() const
{return pos_.y();}

double BaseObject::vy() const
{return v_.y();}

double BaseObject::vx() const
{return v_.x();}

QPointF BaseObject::pos()const
{return pos_; }

QPointF BaseObject::v()const
{return v_;}

void BaseObject::setVx(double vx)
{ v_.rx() = vx; }

void BaseObject::setVy(double vy)
{ v_.ry() = vy; }

void BaseObject::setV(QPointF v)//virtual
{v_ = v; }

void BaseObject::setXY(QPointF pos)//virtual
{pos_ = pos;}

void BaseObject::moveBy(double dx, double dy)//virtual
{
    pos_.rx() += dx;
    pos_.ry() += dy;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BaseRole::BaseRole(QRect role_rect, int max_jump_count, int hp)
    : BaseObject(role_rect.topLeft())
    , on_ground_(false)
    , rect_(role_rect)
    , jump_count_(0)
    , max_jump_count_(max_jump_count)
    , hp_ (hp)
{}

BaseRole::BaseRole(Load::BASR_ROLE& base_param)
    : BaseObject(base_param.role_rect.topLeft())
    , rect_(base_param.role_rect) 
    , max_jump_count_(base_param.max_jump)
    , on_ground_(false)
    , jump_count_(0)
    , hp_ (base_param.hp)
{}

void BaseRole::setXY(QPointF pos)   //override
{
    BaseObject::setXY(pos);
    rect_.moveTo(pos.x(), pos.y());
}

void BaseRole::moveBy(double dx, double dy)//override
{
    BaseObject::moveBy(dx, dy);
    rect_.moveTo(pos_.x(), pos_.y());
}

bool BaseRole::isOnGround() const
{return on_ground_;}

QRect BaseRole::rect() const
{return rect_;}

int BaseRole::return_facing() const
{ return facing_;}

int BaseRole::hp() const
{return hp_;}

void BaseRole::change_hp(int hp)
{hp_ += hp;}

bool BaseRole::can_jump()
{
    return jump_count_ < max_jump_count_;
}

void BaseRole::setOnGround(bool is_on_ground)
{on_ground_ = is_on_ground;}

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