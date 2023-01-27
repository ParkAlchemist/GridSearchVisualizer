#include "searchbfs.h"

SearchBFS::SearchBFS()
{
    pq_ = new std::vector<Node*>;
}

SearchBFS::~SearchBFS()
{
    delete pq_;
}

void SearchBFS::start(Node *start, Node *goal)
{

    start->black = true;
    start->white = false;

    pq_->push_back(start);

    while( !pq_->empty() ){

        Node* v = pq_->front();
        pq_->erase(pq_->begin()); // remove first element

        if(v == goal){
            // back-track to start
            while(v != nullptr){

                path_.push_back(v);
                v = v->prev;
            }
            return;
        }

        v->black = true;
        v->gray = false;

        if(v != start){
            emit change(v->x, v->y, Qt::GlobalColor::darkGray);
        }

        for(Node* w : v->neighbours){

            if(w->white){

                w->white = false;
                w->gray = true;
                w->prev = v;
                pq_->push_back(w);

                if(w != goal){
                    emit change(w->x, w->y, Qt::GlobalColor::blue);
                }
            }
        }
    }
}

std::vector<Node *> SearchBFS::getPath()
{
    return path_;
}
