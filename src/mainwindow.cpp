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
    setupGamePage();

    stacked ->addWidget(gamePage_);

    stacked ->setCurrentWidget(gamePage_);
    gamePage_ ->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connection()
{

}

void MainWindow::setupGamePage()
{

    gamePage_ = new GamePage(width_, height_ );

}



