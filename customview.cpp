#include "customview.h"

CustomView::CustomView()
{

}

void CustomView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){

        SquareNode* item =  static_cast<SquareNode*>(this->scene()->itemAt(event->pos(), QTransform()));

        if(typeid(item) != typeid(SquareNode*)) return;

        // set context
        if(cont == Context::C_none && item != nullptr){
            if(item->brush().color() == Qt::white){
                cont = Context::Draw;
            }
            if(item->brush().color() == Qt::black){
                cont = Context::Erase;
            }
            if(item->brush().color() == Qt::red || item->brush().color() == Qt::green){
                cont = Context::Move;
            }
        }

        // drawing of obstacles
        if(cont == Context::Draw){

            if(item != nullptr && item != prev_item_){
                qDebug() << "drag over item;" << "x:" << event->pos().x() << "y:" << event->pos().y();
                emit item->change(item->rect().topLeft().x(), item->rect().topLeft().y(), Qt::black);
                prev_item_ = item;
            }
            return;
        }

        //erasing of obstacles
        if(cont == Context::Erase){
            if(item != nullptr && item != prev_item_){
                qDebug() << "drag over item;" << "x:" << event->pos().x() << "y:" << event->pos().y();
                emit item->change(item->rect().topLeft().x(), item->rect().topLeft().y(), Qt::white);
                prev_item_ = item;
            }
            return;
        }

        // move start/goal node
        if(cont == Context::Move){

            if(end_node_ == nullptr){
                end_node_ = item;
            }

            if(item == nullptr) return;

            if(item->brush().color() == Qt::white){
                if(end_node_->brush().color() == Qt::green){
                    emit item->change(item->rect().topLeft().x(), item->rect().topLeft().y(), Qt::green);
                    end_node_ = item;
                    return;
                }
                if(end_node_->brush().color() == Qt::red){
                    emit item->change(item->rect().topLeft().x(), item->rect().topLeft().y(), Qt::red);
                    end_node_ = item;
                    return;
                }
            }
        }

    }
    else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
    prev_item_ = nullptr;
    end_node_ = nullptr;
    cont = Context::C_none;

    QGraphicsView::mouseReleaseEvent(event);
}
