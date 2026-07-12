#include "player.h"

Player::Player(int x, int y, int player_height, int player_width)
    :x_(x), y_(y)
    , on_ground(true)
    , player_height_(player_height)
    , player_width_(player_width)
{

}

int Player::x()const
{return x_; }

int Player::y()const
{return y_; }

int Player::vy() const
{return vy_; }

void Player::deltaX(int dx)
{x_ += dx; }

void Player::setVy(int vy)
{
    vy_ = vy;
    on_ground = false;
    //was_on_ground = false;
}

void Player::setXY(int x, int y)
{
    x_ = x; y_ = y;
}

bool Player::can_jump(){
    return jump_count_<max_jump_count_;
}

void Player::jump(float jump_vy){
    if(!can_jump()){
        qDebug() << "can't jump,jump_count_:" << jump_count_;
        return;
    } 
    setVy(jump_vy);
    jump_count_++;
    qDebug() << "jump_count_:" << jump_count_;
}

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

int Player::facing()
{
    return player_facing;
}

void Player::set_facing(int facing)
{
    player_facing = facing;
}

void Player::setOnGround(std::vector<QLine>& ground_line)
{
    for(int i=0; i<ground_line.size(); ++i)
    {   
        QLine line=ground_line[i];
        auto fx = [line](int x) -> float{
            return line.y1()+(x-line.x1())*(line.y2()-line.y1())/(line.x2()-line.x1());
        };
        if((x_ < line.x2()&& x_+ player_width_ >line.x1())
            ||(x_ < line.x1()&& x_+ player_width_ >line.x2())) //在这段线上
        {
            if(y_ < fx(x_) - player_height_)  
                on_ground = false;
            else 
            {   
                //保证在地平线上
                setXY(x_, fx(x_) - player_height_);
                on_ground = true;
            }
        }
        else on_ground = false;
        
    }
}

void Player::update()
{
    if(on_ground){
        jump_count_=0;
    }
    //was_on_ground=on_ground;
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







