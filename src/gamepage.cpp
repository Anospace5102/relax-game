#include "gamepage.h"

#include <QDebug>
GamePage::GamePage(int x, int y):
    winx_(x), winy_(y), player_size_(30)
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
    battle_field_  = new BattleField(winx_, winy_, player_size_);       //逻辑战场加载

    player_pict_ = new QPixmap(QString(":/img/imags/player_01.png"));   //图片加载
    // qDebug()<<"here" <<view_->width();
    player_item_ = new QGraphicsPixmapItem(
        player_pict_->scaled(player_size_,player_size_,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    player_item_ ->setPos(winx_*0.1, winy_*0.8 - player_size_);
    scene_ ->addItem(player_item_);
}

// 初始化-初始/重置
void GamePage::init()
{
    game_timer_ = new QTimer(this); 
    
    ground_ = scene_->addLine(50, winy_* 0.8, winx_*0.8, winy_*0.8 );
    ground_->setPen(QPen(Qt::black, 2));

    connections();
}

// 信号连接
void GamePage::connections()
{
    //game_timer_  <==> updateScene
    connect(game_timer_, &QTimer::timeout, this, &GamePage::updateScene);
}

//开始
void GamePage::start()
{
    game_timer_ ->start(16);
}

// 场景更新
void GamePage::updateScene()
{
    if(pressed_keys_.contains(Qt::Key_A)) battle_field_->player_->deltaX(-2);   //左
    if(pressed_keys_.contains(Qt::Key_D)) battle_field_->player_->deltaX(2);    //右
    if(pressed_keys_.contains(Qt::Key_W))
    {//还要有几段跳控制-留白
        
        battle_field_->player_ ->setVy(-6);
    }

    battle_field_->update();        //更新逻辑战斗场景
    player_item_ ->setPos(battle_field_->player_->x(), battle_field_->player_->y());
}

void GamePage::keyPressEvent(QKeyEvent *event)
{
    pressed_keys_.insert(event->key());     //如果按键=>加入按键集合
    QWidget::keyPressEvent(event);
}

void GamePage::keyReleaseEvent(QKeyEvent *event)
{
    pressed_keys_.remove(event->key());     //如果释放键=>移出按键集合
    QWidget::keyReleaseEvent(event);
}

