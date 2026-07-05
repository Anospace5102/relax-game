#include "gamepage.h"

#include <QDebug>
GamePage::GamePage(int x, int y):
    winx_(x), winy_(y), player_size_(30)
{
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
    init();
}

void GamePage::load()
{
    battle_field_  = new BattleField(winx_, winy_, player_size_);

    player_pict_ = new QPixmap(QString(":/img/imags/player_01.png"));
    qDebug()<<"here" <<view_->width();
    player_item_ = new QGraphicsPixmapItem(
        player_pict_->scaled(player_size_,player_size_,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    player_item_ ->setPos(winx_*0.1, winy_*0.8 - player_size_);
    scene_ ->addItem(player_item_);
}

void GamePage::init()
{
    game_timer_ = new QTimer(this);
    connect(game_timer_, &QTimer::timeout, this, &GamePage::updateScene);
    game_timer_ ->start(16);

    connections();
}

void GamePage::connections()
{
    connect(game_timer_, &QTimer::timeout, this, &GamePage::updateScene);
}
void GamePage::start()
{
    ground_ = scene_->addLine(50, winy_* 0.8, winx_*0.8, winy_*0.8 );
    ground_->setPen(QPen(Qt::black, 2));
}

void GamePage::updateScene()
{
    if(pressed_keys_.contains(Qt::Key_A)) battle_field_->player_->deltaX(-1);
    if(pressed_keys_.contains(Qt::Key_D)) battle_field_->player_->deltaX(1);
    if(pressed_keys_.contains(Qt::Key_W))
    {
        battle_field_->player_ ->setVy(-3);
    }

    battle_field_->update();
    player_item_ ->setPos(battle_field_->player_->x(), battle_field_->player_->y());
}

void GamePage::keyPressEvent(QKeyEvent *event)
{
    pressed_keys_.insert(event->key());
    QWidget::keyPressEvent(event);
}

void GamePage::keyReleaseEvent(QKeyEvent *event)
{
    pressed_keys_.remove(event->key());
    QWidget::keyReleaseEvent(event);
}

