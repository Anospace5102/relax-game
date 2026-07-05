#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "player.h"

#include <vector>

class BattleField
{
public:
    BattleField(int width, int height, int player_height=30);
    void update();

public:
    Player *player_;

private:
    

private:
    int width_, height_;
    std::vector<QLine> ground_line_;

};


#endif