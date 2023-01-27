#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsItem>

#include "squarenode.h"

enum Context{C_none, Draw, Erase, Move};

class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomView();
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    SquareNode* prev_item_ = nullptr;
    SquareNode* end_node_ = nullptr;
    int cont = Context::C_none;
};

#endif // CUSTOMVIEW_H
