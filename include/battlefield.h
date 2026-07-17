#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "player.h"
#include "boss.h"
#include <vector>

class BattleField
{
public:
    BattleField(int width, int height, int player_height=30, int boss_height=30);
    void update();

public:
    Player *player_;    //玩家
    Boss *boss_;        //boss

private:
    

private:
    int width_, height_;
    std::vector<QLine> ground_line_;    //地面-线段

};


#endif