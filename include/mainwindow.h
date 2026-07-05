#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamepage.h"


#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsView>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int width, int height, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupGamePage();
    void connection();


private:
    int width_, height_;
    Ui::MainWindow *ui;
    QStackedWidget *stacked = nullptr;

    GamePage *gamePage_;
};
#endif // MAINWINDOW_H
