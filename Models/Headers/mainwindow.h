//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H
#pragma once

#include "Grid.h"
#include <QMainWindow>
#include <QBoxLayout>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    QGraphicsView view;
    QGraphicsScene scene;
    Grid * grid;
    QGraphicsPixmapItem background;
    std::vector<QGraphicsPixmapItem*> obrazky;
    QGraphicsPixmapItem *obrazek;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QHBoxLayout *layout;

private:
};
//#endif // MAINWINDOW_H
