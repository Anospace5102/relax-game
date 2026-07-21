#ifndef _BULLET_H
#define _BULLET_H
#include<QGraphicsEllipseItem>
//建议形式
enum BulletType
{
    Radius,
    Rect,
    Polygon
};

class Bullet_
{
public: 
    Bullet_(){};
public:
    // bool is_active()const;
 
public:
    // void set_active(bool active);
    

private:
    
    QRect rect_;
    QPolygonF polygon_;

    QPointF pos_;
    QPointF v_;
    BulletType type_;
    bool is_active_;

};
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