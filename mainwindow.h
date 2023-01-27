#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTime>
#include <QStyleOptionGraphicsItem>
#include <QAbstractGraphicsShapeItem>
#include <QLayout>
#include <QDebug>
#include <QEventLoop>
#include <QDebug>
#include <QAbstractButton>
#include <cmath>
#include <algorithm>
#include <QLineF>
#include <QGraphicsLineItem>
#include <QFont>
#include <string>

#include "gridgraph.h"
#include "squarenode.h"
#include "customview.h"
#include "searchalgorithm.h"
#include "searchbfs.h"
#include "searchdfs.h"
#include "searchdijkstra.h"
#include "searchastar.h"
#include "searchgbfs.h"
#include "helperfunctions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_start(int x, int y);
    void set_goal(int x, int y);
    void drawPath(std::vector<Node*> path);
    void drawLine(QLineF line);

    void pathSmoothing();
    void newPathSmoothing();

private slots:
    void on_action32x16_triggered();

    void on_action64x32_triggered();

    void tick();

    void change_color(int x, int y, Qt::GlobalColor color);

    void search_update(int x, int y, Qt::GlobalColor color);

    void on_RunButton_clicked();

    void on_CleanButton_clicked();

    void on_action4_Neighbours_triggered();

    void on_action8_Neighbours_triggered();

    void on_ClearButton_clicked();

    void on_AlgcomboBox_currentIndexChanged(int index);

    void set_Heuristic(QAbstractButton* b);

    void on_action128x64_triggered();


    void on_smoothButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    CustomView* cv_;

    void draw_grid();
    void init();
    void setInfoLabel();
    void showInfo();

    GridGraph* grid_ = nullptr;
    SearchAlgorithm* alg_ = nullptr;
    int heuristic_ = Heuristic::H_none;
    std::vector<std::vector<SquareNode*>> nodes_;

    std::vector<Node*> path_;
    std::vector<Node*> ps_path_;
    std::vector<QGraphicsLineItem*> lines_;

    QTimer* timer_;
    QTime time_;

    QTimer* stall_timer_;
    QEventLoop* stall_loop_;
    int stall_time_ = 1;

    int grid_width_ = 0;
    int grid_heigth_ = 0;
    int neighbours_ = 4;

    int node_width_ = 0;
    int node_heigth_ = 0;

    int left_margin = 20;
    int top_margin = 50;
    int window_width = 1024;
    int window_heigth = 512;
};
#endif // MAINWINDOW_H
