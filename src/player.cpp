#include "player.h"


Player::Player(Load::PLAYER& w)
    :BaseRole(w.base_param)
    , hp_ (w.hp)
{
   
    
}

int Player::hp() const
{
    return hp_;
}

void Player::change_hp(int hp)
{
    hp_ += hp;
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


void Player::update(double fixed_step)
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

// void Player::setOnGround(std::vector<QLine>& ground_line)
// {
//     for(int i=0; i<ground_line.size(); ++i)
//     {   
//         QLine line=ground_line[i];
//         auto fx = [line](int x) -> float{
//             return line.y1()+(x-line.x1())*(line.y2()-line.y1())/(line.x2()-line.x1());
//         };
//         if((x_ < line.x2()&& x_+ player_width_ >line.x1())
//             ||(x_ < line.x1()&& x_+ player_width_ >line.x2())) //在这段线上
//         {
//             if(y_ < fx(x_) - player_height_)  
//                 on_ground = false;
//             else 
//             {   
//                 //保证在地平线上
//                 setXY(x_, fx(x_) - player_height_);
//                 on_ground = true;
//             }
//         }
//         else on_ground = false;
//     }
// }
// QRect* Player::intersected(std::vector<QRect>& ground_rects_)
// {
//     for(int i=0; i<ground_rects_.size();i++)
//     {qDebug()<<"detected"<<player_rect_.y();
//         if(ground_rects_[i].intersected(player_rect_ ).isValid())
//         {
//             collisionHandling(&ground_rects_[i]);
//             return &ground_rects_[i];
//         }
//     } 
//     on_ground = false;
//     return nullptr;
// }
// void Player::collisionHandling(QRect* ground)
// {
//     if(ground == nullptr) return;
//     QPainterPath path;
//     path.clear();
//     path.moveTo(ground->topLeft());
//     path.lineTo(ground->bottomLeft());
//     if (path.intersects(player_rect_)) //地面矩形左面
//     {
//         x_ = ground->left() - player_rect_.width()- 1;
//     }
//     path.clear();
//     path.moveTo(ground->topRight());
//     path.lineTo(ground->bottomRight());
//     if (path.intersects(player_rect_)) //地面矩形右面
//     {
//         x_ = ground->right()+1;
//     }
//     path.clear();
//     path.moveTo(ground->topLeft());
//     path.lineTo(ground->topRight());
//     if (path.intersects(player_rect_)) //地面矩形上面
//     {
//         on_ground = true;
//         vy_ = 0;
//         y_ = ground->top() - player_rect_.height();
//     }
//     path.clear();
//     path.moveTo(ground->bottomLeft());
//     path.lineTo(ground->bottomRight());
//     if (path.intersects(player_rect_)) //地面矩形下面
//     {
//         vy_ = 0;
//         y_ = ground->bottom()+1;
//     }
// }




