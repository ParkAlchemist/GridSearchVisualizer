#include "searchastar.h"

SearchAStar::SearchAStar(int heur)
{

    switch(heur){
        case Heuristic::Manhattan:
            heur_func = &manhattan;
            break;
        case Heuristic::Octal:
            heur_func = &octal;
            break;
        case Heuristic::Euclidian:
            heur_func = &euclidian;
            break;
        case Heuristic::Chebyshev:
            heur_func = &chebyshev;
            break;
        default:
            heur_func = nullptr;
            break;
    }

}

SearchAStar::~SearchAStar()
{

}

void SearchAStar::start(Node *start, Node *goal)
{
    start->white = false;
    start->dist = 0;
    start->heuristic = heur_func(start, goal);

    pq_.push_back(start);

    while( !pq_.empty() ){

        std::sort(pq_.begin(), pq_.end(), &compFvalue);

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
                if(m->heuristic == INFINITY){
                    m->heuristic = heur_func(m, goal);
                }
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

std::vector<Node *> SearchAStar::getPath()
{
    return path_;
}
