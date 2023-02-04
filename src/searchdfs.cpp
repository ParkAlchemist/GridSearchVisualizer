#include "searchdfs.h"

SearchDFS::SearchDFS()
{

}

SearchDFS::~SearchDFS()
{

}

void SearchDFS::start(Node *n, Node *goal)
{
    if(n == goal){

        while(n != nullptr){

            path_.push_back(n);
            n = n->prev;
        }
        end_ = true;
        return;
    }

    if(n->state == State::Free){
        emit change(n->x, n->y, Qt::darkGray);
    }

    n->black = true;
    n->white = false;
    n->gray = false;

    std::random_shuffle(n->neighbours.begin(), n->neighbours.end());

    for(Node* m : n->neighbours){

        if(end_) break;

        if(m->white){
            m->prev = n;
            m->white = false;
            m->gray = true;
            if(m->state != State::Start && m->state != State::Goal){
                emit change(m->x, m->y, Qt::blue);
            }
            this->start(m, goal);
        }
    }
}

std::vector<Node *> SearchDFS::getPath()
{
    return path_;
}
