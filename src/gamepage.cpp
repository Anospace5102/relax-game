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

    //人物图片
    QRect rt = world_config.player[0].base_param.role_rect;
    player_pict_ = new QPixmap(QString(":/img/imags/player_01.png"));   //图片加载
    player_item_ = new QGraphicsPixmapItem(
        player_pict_->scaled(rt.width(), rt.height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    player_item_ ->setPos(battle_field_->player_->x(), battle_field_->player_->y());
    scene_ ->addItem(player_item_);

    //bosss
    rt = world_config.boss[0].base_param.role_rect;
    boss_pict_ = new QPixmap(QString(":/img/imags/boss.png"));   //图片加载
    boss_item_ = new QGraphicsPixmapItem(
        boss_pict_->scaled(rt.width(), rt.height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    boss_item_ ->setPos(battle_field_->boss_->x(), battle_field_->boss_->y());
    scene_ ->addItem(boss_item_);

    //直接做的子弹组Item,然后addItem了
    bullets_ = new QGraphicsBulletsItem(battle_field_->bullets_);
    scene_->addItem(bullets_);

    //boss文字
    QFont font("Arial", 10, QFont::Bold);
    double hp=battle_field_->boss_->hp();
    boss_hp_text = new QGraphicsSimpleTextItem();
    boss_hp_text->setFont(font);
    boss_hp_text->setBrush(Qt::black);
    boss_hp_text->setText(QString("hp:%1").arg(hp));
    boss_hp_text->setPos(350, 20);
    scene_ -> addItem(boss_hp_text);

    qDebug() << "load successful";
}

// 初始化-初始/重置
void GamePage::init()
{
    game_timer_ = new QTimer(this); 
    
    connections();
}

void GamePage::drawTexts()
{

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

// 场景更新
void GamePage::updateScene()
{
    battle_field_->update();        //更新逻辑战斗场景

    double hp=battle_field_->boss_->hp();
    boss_hp_text->setText(QString("hp:%1").arg(hp));

    player_item_->setPos(battle_field_->player_->x(), battle_field_->player_->y());
    boss_item_->setPos(battle_field_->boss_->x(), battle_field_->boss_->y());
    if (bullets_) {
        bullets_->update();
    }
    scene_->update();
}

void GamePage::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W && !event->isAutoRepeat()){
        emit keyWSignal();
    }
    if(event->key()==Qt::Key_Space && !event->isAutoRepeat()){
        emit keySpaceSignal();
    }
    
    emit addKey(event->key());//如果按键=>加入按键集合
    QWidget::keyPressEvent(event);
}

void GamePage::keyReleaseEvent(QKeyEvent *event)
{   
    emit removeKey(event->key());//如果释放键=>移出按键集合
    QWidget::keyReleaseEvent(event);
}


