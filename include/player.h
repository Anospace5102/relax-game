#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QLine>
#include <vector>
const float ga=0.4;
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
    int jump_count_=0;
    int max_jump_count_=2;//最多二段跳,但是实际运行的时候可以跳三次，还不清楚为什么
    int player_height_;
    int player_width_;
    int x_;
    int y_;
    float vx_=0;
    float vy_=0;

    bool on_ground;
    //bool was_on_ground=false;
public:
    bool can_jump();
    void jump(float jump_vy);

    
public:
    void request_fire(); //确认发射
    bool return_fire_requestd_(); //返回是否请求发射
    void request_jump(); //确认跳跃
    bool return_jump_requestd_(); //返回是否请求跳跃
    int facing();
    void set_facing(int facing);
private:
    bool jump_requested_=false;    //是否请求跳跃
    bool fire_requested_=false;//是否请求发射
    int player_facing=1;//玩家朝向 1为右 -1为左
};

#endif // PLAYER_H