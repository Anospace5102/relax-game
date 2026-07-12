#ifndef _BULLET_H
#define _BULLET_H
#include<QGraphicsEllipseItem>

class Bullet{
public:
    Bullet(QGraphicsEllipseItem* item, float vx, float vy, bool is_active, float radius);

public:
    QGraphicsEllipseItem* item;
private:
    float vx_;
    float vy_;
    bool is_active_;
    float radius;
public:
    float vx() const;
    float vy() const;
    bool is_active() const;
    void set_active(bool active);

};


#endif //_BULLET_H