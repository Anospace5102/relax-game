#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , width_(width), height_(height)
{
    ui->setupUi(this);
    this->resize(width, height);

    stacked = new QStackedWidget(this);
    setCentralWidget(stacked);

    setupGamePage();        //初始化游戏页面

    stacked ->addWidget(gamePage_);     //游戏页面加到切换容器

    stacked ->setCurrentWidget(gamePage_);      //先设置成游戏界面方便处理，后续要有开始界面等等
    gamePage_ ->init();
    gamePage_ ->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connection()
{

}

//初始化游戏页面
void MainWindow::setupGamePage()
{

    gamePage_ = new GamePage(width_, height_ );

}



