#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QLine>
#include <vector>
const float ga=0.25;
class Player
{
public:
    Player(int x, int y, 
        int player_height=30,int player_width=20);

public:
    void deltaX(int dx);    //左右移动的时候delta_x
    void setVy(int vy);     //跳-速度设置vy
    void update();          //玩家自身逻辑更新
    void setOnGround(std::vector<QLine>& ground_line);  //地面检测

public:
    int x() const;
    int y() const;
    int vy() const;

private:
    void setXY(int x, int y);
private:
    int player_height_;
    int player_width_;
    int x_;
    int y_;
    float vx_=0;
    float vy_=0;

    bool on_ground;
};

#endif // PLAYER_H



