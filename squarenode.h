#ifndef SQUARENODE_H
#define SQUARENODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QEvent>
#include <QDebug>
#include <QPen>
#include <QRectF>

class SquareNode : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    SquareNode(QRectF r);
signals:
    void change(int, int, Qt::GlobalColor);
};

#endif // SQUARENODE_H
