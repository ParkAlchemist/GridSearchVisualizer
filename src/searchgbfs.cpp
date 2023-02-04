#include "searchgbfs.h"

SearchGBFS::SearchGBFS(int heur)
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

SearchGBFS::~SearchGBFS()
{

}

void SearchGBFS::start(Node *start, Node *goal)
{
    start->white = false;
    start->heuristic = heur_func(start, goal);

    pq_.push_back(start);

    while( !pq_.empty() ){

        std::sort(pq_.begin(), pq_.end(), &compHvalue);

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

            if(m->white){
                m->white = false;
                m->gray = true;
                m->prev = v;
                m->heuristic = heur_func(m, goal);
                pq_.push_back(m);
                if(m != goal){
                    emit change(m->x, m->y, Qt::blue);
                }
            }
        }
    }
}

std::vector<Node *> SearchGBFS::getPath()
{
    return path_;
}
