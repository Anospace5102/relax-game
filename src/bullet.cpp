#include "bullet.h"
#include <QPainter>

Bullet::Bullet(Belonging belonging, BulletType type, QPointF& pos,
     double radius,double damage, bool is_active)
    : BaseObject(pos)
    , belonging_(belonging)
    , type_(type)
    , is_active_(is_active)
    , radius_(radius)
    , rect_(pos.x(), pos.y(), radius * 2, radius * 2)
    , damage_(damage)
{}
Bullet::Bullet(Belonging belonging, BulletType type, QPointF& pos, 
     double width, double height,double damage, bool is_active)
    : BaseObject(pos)
    , belonging_(belonging)
    , type_(type)
    , is_active_(is_active)
    , rect_(pos.x(), pos.y(), width, height)
    , radius_(0)
    , damage_(damage)
{}
Bullet::Bullet(Belonging belonging, BulletType type, QPointF& pos,
     QPolygonF& polygon, double damage, bool is_active)
    : BaseObject(pos)
    , belonging_(belonging)
    , type_(type)
    , is_active_(is_active)
    , polygon_(polygon)
    , radius_(0)
    , damage_(damage)
{}

void Bullet::update(double fixed_step)
{
    moveBy(fixed_step * vx(), fixed_step * vy());
}

bool Bullet::is_active() const
{
    return is_active_;
}

double Bullet::damage() const
{
    return damage_;
}

Belonging Bullet::belonging() const
{
    return belonging_;
}

BulletType Bullet::type() const
{
    return type_;
}

double Bullet::radius() const
{
    return radius_;
}

QRect Bullet::rect() const
{
    if (type_ == BulletType::Rect) {
        return QRect(pos().toPoint(), rect_.size());
    }
    if (type_ == BulletType::Circle) {
        return QRect(pos().toPoint(), QSize(rect_.width(), rect_.height()));
    }
    return QRect();
}

QPolygonF Bullet::polygon() const
{
    if (type_ == BulletType::Polygon) {
        return polygon_.translated(pos());
    }
    return QPolygonF();
}

void Bullet::set_active(bool active)
{
    is_active_ = active;
}

void Bullet::set_damage(double damage)
{
    damage_ = damage;
}


////////////////////////////////////////////////
////////////////////////////////////////////////
QGraphicsBulletsItem::QGraphicsBulletsItem(QList<Bullet*>& bulletList)
    : QGraphicsItem()
    , bullets_(bulletList)
{
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption, true);
}

QRectF QGraphicsBulletsItem::boundingRect() const
{
    // 使用固定场景范围，避免每帧重新计算 geometry
    return QRectF(0, 0, 800, 600);
}

void QGraphicsBulletsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing, true);

    for (const Bullet* bullet : bullets_) {
        if (!bullet || !bullet->is_active())
            continue;

        switch (bullet->type()) {
        case BulletType::Circle: {
                            //   左上角
            QRectF circleRect(bullet->pos(), QSizeF(bullet->radius() * 2, bullet->radius() * 2));
            painter->setPen(Qt::NoPen);
            painter->setBrush(QBrush(Qt::red));
            painter->drawEllipse(circleRect);
            break;
        }
        case BulletType::Rect: {
            painter->setPen(Qt::NoPen);
            painter->setBrush(QBrush(Qt::yellow));
            painter->drawRect(bullet->rect());
            break;
        }
        case BulletType::Polygon: {
            painter->setPen(Qt::NoPen);
            painter->setBrush(QBrush(Qt::green));
            painter->drawPolygon(bullet->polygon());
            break;
        }
        }
    }
}

