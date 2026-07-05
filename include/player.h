#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QLine>
#include <vector>
const float ga=0.08;
class Player
{
public:
    Player(int x, int y, 
        int player_height=30,int player_width=20);

public:
    void deltaX(int dx);
    void setVy(int vy);
    void update();
    void setOnGround(std::vector<QLine>& ground_line);

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



