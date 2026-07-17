#include "battlefield.h"
#include <iostream>
BattleField::BattleField(int width, int height, int player_height, int boss_height)
    :width_(width), height_(height)
{
    ground_line_.clear();   //地线
    ground_line_.push_back(QLine(50, height*0.8, width*0.8, height*0.8));

    player_ = new Player(width*0.1, height*0.2, player_height); //玩家
    
    boss_=new Boss(width*0.1, height*0.2, boss_height); //boss
}
void BattleField::update()
{
    // std::cout << player_->x()<< " " << player_->y() << " " 
    //<< player_->vy() << std::endl;
    player_ ->setOnGround(ground_line_);
    player_->update();
}

