#include"base_role.h"

BaseRole::BaseRole(int x,int y,int height,int width,int hp)
    :x_(x),y_(y)
    ,on_ground(true)
    ,height_(height)
    ,width_(width)
    ,hp_(hp)
{

}

int BaseRole::deltaX(int dx)
{
    x_+=dx;
    return x_;
}

void BaseRole::setVy(int vy)
{
    vy_=vy;
    on_ground=false;
}

void BaseRole::update()
{
    if(on_ground){
        jump_count=0;
    }
    if(on_ground && vy_ >= 0)
    {
        vy_ = 0;
    }
    else {
        vy_ += ga;
        y_ += vy_;
    }

    //可以有--后来可以加上控制--控制有无上界限制
    if(y_<=0){
        y_=0;
        vy_=-1*vy_;
    }
}

void BaseRole::setOnGround(std::vector<QLine>& ground_line)
{
    for(int i=0; i<ground_line.size(); ++i)
    {   
        QLine line=ground_line[i];
        auto fx = [line](int x) -> float{
            return line.y1()+(x-line.x1())*(line.y2()-line.y1())/(line.x2()-line.x1());
        };
        if((x_ < line.x2()&& x_+ width_ >line.x1())
            ||(x_ < line.x1()&& x_+ width_ >line.x2())) //在这段线上
        {
            if(y_ < fx(x_) - height_)  
                on_ground = false;
            else 
            {   
                //保证在地平线上
                setXY(x_, fx(x_) - height_);
                on_ground = true;
            }
        }
        else on_ground = false;
        
    }
}
int BaseRole::x() const
{return x_;}

int BaseRole::y() const
{return y_;}

int BaseRole::vy() const
{return vy_;}

void BaseRole::setXY(int x,int y)
{
    x_=x; y_=y;
}

int BaseRole::return_facing() const
{
    return facing_;
}

void BaseRole::set_facing(int facing)
{
    facing_=facing;
}

bool BaseRole::can_jump()
{
    return jump_count<max_jump_count;
}

void BaseRole::jump(float jump_vy)
{
    if(can_jump())
    {
        setVy(jump_vy);
        jump_count++;
    }
}

int BaseRole::hp() const
{
    return hp_;
}

void BaseRole::change_hp(int hp)
{
    hp_+=hp;
}