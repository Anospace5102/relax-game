#include "bullet.h"

Bullet::Bullet(QGraphicsEllipseItem* item, float vx, float vy, bool is_active, float radius)
    : item(item), vx_(vx), vy_(vy), is_active_(is_active), radius(radius)
{
}

float Bullet::vx() const
{
    return vx_;
}

float Bullet::vy() const
{
    return vy_;
}

bool Bullet::is_active() const
{
    return is_active_;
}

void Bullet::set_active(bool active)
{
    is_active_ = active;
}
