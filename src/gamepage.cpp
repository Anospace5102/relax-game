#include "gamepage.h"
#include "load.h"
#include <QDebug>
#include <vector>
GamePage::GamePage(int x, int y):
    winx_(x), winy_(y)
{
    //搭建：QWidget <- layout_ <- view <- scene_
    view_ = new QGraphicsView(this);
    scene_ = new QGraphicsScene(view_);
    this->resize(x,y);
    this->setStyleSheet("background-color:rgb(200,230,250)");

    view_ ->setScene(scene_);
    view_ ->setBackgroundBrush(QColor(200,230,250));
    view_ ->setSceneRect(0, 0, 800, 600);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    load();
}

// 初始化-加载
void GamePage::load()
{
    Load::world world_config = Load::getWorldInformation(); 

    for(auto it: world_config.grounds)
    {
        auto grd = scene_-> addRect(it);
        grd -> setPen(QPen(Qt::black, 2));
        grounds_ .push_back(grd);
    }
    battle_field_  = new BattleField(winx_, winy_, world_config);       //逻辑战场加载

    QRect rt = world_config.player[0].base_param.role_rect;
    player_pict_ = new QPixmap(QString(":/img/imags/player_01.png"));   //图片加载
    player_item_ = new QGraphicsPixmapItem(
        player_pict_->scaled(rt.width(), rt.height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    player_item_ ->setPos(battle_field_->player_->x(), battle_field_->player_->y());
    scene_ ->addItem(player_item_);

    rt = world_config.boss[0].base_param.role_rect;
    boss_pict_ = new QPixmap(QString(":/img/imags/boss.png"));   //图片加载
    boss_item_ = new QGraphicsPixmapItem(
        boss_pict_->scaled(rt.width(), rt.height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    boss_item_ ->setPos(battle_field_->boss_->x(), battle_field_->boss_->y());
    scene_ ->addItem(boss_item_);
    
}

// 初始化-初始/重置
void GamePage::init()
{
    game_timer_ = new QTimer(this); 
    
    connections();
}

// 信号连接
void GamePage::connections()
{
    //game_timer_  <==> updateScene
    connect(game_timer_, &QTimer::timeout, this, &GamePage::updateScene);
    connect(this, &GamePage::addKey, battle_field_, &BattleField::addKey);
    connect(this, &GamePage::removeKey, battle_field_, &BattleField::removeKey);
    connect(this, &GamePage::keySpaceSignal, battle_field_, &BattleField::keySpaceHandle);
    connect(this, &GamePage::keyWSignal, battle_field_, &BattleField::keyWHandle);

}

//开始
void GamePage::start()
{
    game_timer_ ->start(16);
}

int GamePage::get_player_width()
{
    return player_item_->pixmap().width();
}

int GamePage::get_boss_width()
{
    return boss_item_->pixmap().width();
}
// 场景更新
void GamePage::updateScene()
{

    if(pressed_keys_.contains(Qt::Key_Space)&& battle_field_->player_->return_fire_requestd_()){ //空格发射子弹，长按只能发射一次
        int px=battle_field_->player_->x();
        int py=battle_field_->player_->y()+battle_field_->player_->rect().height()/2;
        int facing=battle_field_->player_->return_facing();

        float bullet_radius=5;
        QGraphicsEllipseItem* bullet_item=new QGraphicsEllipseItem(0, 0, bullet_radius*2, bullet_radius*2);
        bullet_item->setBrush(QBrush(Qt::red));
        bullet_item->setPen(QPen(Qt::NoPen));
        if(facing==-1){
            bullet_item->setPos(px-bullet_radius, py-bullet_radius);
        } else {
            int player_width=player_item_->pixmap().width();
            bullet_item->setPos(px+player_width+bullet_radius, py-bullet_radius);
        }

        scene_->addItem(bullet_item);

        float bullet_speed=8;
        float bullet_vx=bullet_speed*facing;
        float bullet_vy=0;

        Bullet* bullet=new Bullet{bullet_item, bullet_vx, bullet_vy, true, bullet_radius};
        bullets_.append(bullet);
    }

    for(int i=bullets_.size()-1;i>=0;--i){
        Bullet* bullet=bullets_[i];
        if(!bullet->is_active()){
            scene_->removeItem(bullet->item);
            delete bullet->item;
            delete bullet;
            bullets_.removeAt(i);
            continue;
        }

        QPointF pos=bullet->item->pos();
        pos.rx()+=bullet->vx();
        pos.ry()+=bullet->vy();
        bullet->item->setPos(pos);

        if(pos.x() < 0 || pos.x() > winx_ || pos.y() < 0 || pos.y() > winy_){
            bullet->set_active(false);
        }
    }


    battle_field_->update();        //更新逻辑战斗场景
    player_item_ ->setPos(battle_field_->player_->x(), battle_field_->player_->y());
    boss_item_ -> setPos(battle_field_->boss_->x(), battle_field_->boss_->y());
}

void GamePage::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W && !event->isAutoRepeat()){
        emit keyWSignal();
    }
    if(event->key()==Qt::Key_Space && !event->isAutoRepeat()){
        emit keySpaceSignal();
    }
    pressed_keys_.insert(event->key());     
    emit addKey(event->key());//如果按键=>加入按键集合
    QWidget::keyPressEvent(event);
}

void GamePage::keyReleaseEvent(QKeyEvent *event)
{
    pressed_keys_.remove(event->key());     
    emit removeKey(event->key());//如果释放键=>移出按键集合
    QWidget::keyReleaseEvent(event);
}


