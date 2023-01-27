#include "gridgraph.h"

GridGraph::GridGraph(int width, int height)
{
    grid_ = new Grid;

    for(int y = 0; y < height; ++y){

       std::vector<Node*> node_vec;

       for(int x = 0; x < width; ++x){

           Node* n = new Node;
           n->x = x;
           n->y = y;
           node_vec.push_back(n);
       };

       grid_->push_back(node_vec);
    };
};

GridGraph::~GridGraph()
{
    for(int y = 0; y < (int)grid_->size(); ++y){
        for(int x = 0; x < (int)grid_->at(0).size(); ++x){
            delete grid_->at(y).at(x);
        }
    }
    delete grid_;
}

std::vector<Node *> GridGraph::operator [](int y)
{
    return grid_->at(y);
}

Grid* GridGraph::get()
{
    return grid_;
}

void GridGraph::set_start(int x, int y)
{
    if(start_ != nullptr) start_->state = State::Free;
    Node* s = grid_->at(y).at(x);
    s->state = State::Start;
    start_ = s;
}

void GridGraph::set_goal(int x, int y)
{
    if(goal_ != nullptr) goal_->state = State::Free;
    Node* g = grid_->at(y).at(x);
    g->state = State::Goal;
    goal_ = g;
}

Node *GridGraph::get_start()
{
    return start_;
}

Node *GridGraph::get_goal()
{
    return goal_;
}

void GridGraph::init()
{
    for(int y = 0; y < (int)grid_->size(); ++y){
        for(int x = 0; x < (int)grid_->at(0).size(); ++x){

            Node* n = grid_->at(y).at(x);
            n->dist = INFINITY;
            n->heuristic = INFINITY;
            n->white = true;
            n->gray = false;
            n->black = false;
            n->prev = nullptr;
            if(!n->neighbours.empty()){
                n->neighbours.clear();
            }
        }
    }
}

void GridGraph::setNeighbours(int config)
{
    int grid_heigth = grid_->size();
    int grid_width = grid_->at(0).size();

    for(int j = 0; j < grid_heigth; ++j){
        for(int i = 0; i < grid_width; ++i){

            std::vector<Node*> vec;
            bool top_added = false;
            bool bottom_added = false;
            bool left_added = false;
            bool right_added = false;

            // vertical and horizontal neighbours
            if( j > 0 ){
                if( grid_->at(j-1).at(i)->state != State::Obstacle ){
                    vec.push_back(grid_->at(j-1).at(i)); // top
                    top_added = true;
                }
            }
            if( j < grid_heigth-1 ){
                if( grid_->at(j+1).at(i)->state != State::Obstacle ){
                    vec.push_back(grid_->at(j+1).at(i)); // bottom
                    bottom_added = true;
                }
            }
            if( i > 0 ){
                if( grid_->at(j).at(i-1)->state != State::Obstacle ){
                    vec.push_back(grid_->at(j).at(i-1)); // left
                    left_added = true;
                }
            }
            if( i < grid_width-1 ){
                if( grid_->at(j).at(i+1)->state != State::Obstacle ){
                    vec.push_back(grid_->at(j).at(i+1)); // right
                    right_added = true;
                }
            }

            if(config == 8){

                //diagonal neighbours
                if( top_added || right_added ){
                    if( j > 0 && i < grid_width-1 ){
                        if( grid_->at(j-1).at(i+1)->state != State::Obstacle ){
                            vec.push_back(grid_->at(j-1).at(i+1)); // top-right
                        }
                    }
                }
                if( top_added || left_added ){
                    if( j > 0 && i > 0 ){
                        if( grid_->at(j-1).at(i-1)->state != State::Obstacle ){
                            vec.push_back(grid_->at(j-1).at(i-1)); // top-left
                        }
                    }
                }
                if( bottom_added || right_added ){
                    if( j < grid_heigth - 1 && i < grid_width-1 ){
                        if( grid_->at(j+1).at(i+1)->state != State::Obstacle ){
                            vec.push_back(grid_->at(j+1).at(i+1)); // bottom-right
                        }
                    }
                }
                if( bottom_added || left_added ){
                    if(j < grid_heigth - 1 && i > 0 ){
                        if( grid_->at(j+1).at(i-1)->state != State::Obstacle ){
                            vec.push_back(grid_->at(j+1).at(i-1)); // bottom-left
                        }
                    }
                }
            }
            grid_->at(j).at(i)->neighbours = vec;
        }
    }
};
