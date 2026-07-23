#ifndef _BULLET_H
#define _BULLET_H
#include <QGraphicsItem>
#include <QList>
#include "base_role.h"
//建议形式
enum BulletType
{
    Circle,
    Rect,
    Polygon
};

enum Belonging { player, boss };

class Bullet : public BaseObject
{
public:
    Bullet(Belonging belonging, BulletType type, QPointF& pos,
         double radius, double damage, bool is_active=true);
    Bullet(Belonging belonging, BulletType type, QPointF& pos,
         double width, double height, double damage, bool is_active=true);
    Bullet(Belonging belonging, BulletType type, QPointF& pos,
         QPolygonF& polygon, double damage,bool is_active=true);
public:
    void update(double fixed_step);
    bool is_active() const;
    double damage() const;
    Belonging belonging() const;
    BulletType type() const;
    double radius() const;
    QRect rect() const;
    QPolygonF polygon() const;
public:
    void set_active(bool active);
    void set_damage(double damage);

private:
    double radius_;
    QRect rect_;
    QPolygonF polygon_;

    BulletType type_;
    Belonging belonging_;
    bool is_active_;

    double damage_;
};
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// 新写了一个QGraphicsItem直接加到scene_里面，这个是把所有的子弹当作一个整体一起画的
class QGraphicsBulletsItem : public QGraphicsItem {
public:
    explicit QGraphicsBulletsItem(QList<Bullet*>& bulletList);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QList<Bullet*>& bullets_;
};

#endif //_BULLET_H