#include "searchdijkstra.h"

SearchDijkstra::SearchDijkstra()
{

}

SearchDijkstra::~SearchDijkstra()
{

}

void SearchDijkstra::start(Node *start, Node *goal)
{
    start->white = false;
    start->dist = 0;

    pq_.push_back(start);

    while( !pq_.empty() ){

        std::sort(pq_.begin(), pq_.end(), &compGvalue);

        Node* v = pq_.front();
        pq_.erase(pq_.begin());

        if(v == goal){

            while(v != nullptr){

                path_.push_back(v);
                v = v->prev;
            }
            return;
        }

        v->black = true;
        v->gray = false;

        if(v != start && v != goal){
            emit change(v->x, v->y, Qt::darkGray);
        }

        for(Node* m : v->neighbours){

            float dist = distance(v, m) + v->dist;

            if(dist < m->dist){

                m->dist = dist;
                m->prev = v;
            }

            if(m->white){
                m->white = false;
                m->gray = true;
                pq_.push_back(m);
                if(m != goal){
                    emit change(m->x, m->y, Qt::blue);
                }
            }
        }
    }
}

std::vector<Node *> SearchDijkstra::getPath()
{
    return path_;
}
