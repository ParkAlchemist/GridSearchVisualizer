#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include <vector>
#include <QGraphicsItem>
#include <cmath>

enum State {Obstacle, Free, Start, Goal};

struct Node{
    int x;
    int y;

    float dist = INFINITY;
    float heuristic = INFINITY;

    int state = State::Free;

    std::vector<Node*> neighbours;

    Node* prev = nullptr;

    bool white = true;
    bool gray = false;
    bool black = false;
};

using Grid = std::vector<std::vector<Node*>>;

class GridGraph
{
public:
    GridGraph(int width, int height);
    ~GridGraph();
    std::vector<Node*> operator [] (int y);
    Grid* get();
    void set_start(int x, int y);
    void set_goal(int x, int y);
    void setNeighbours(int config);
    Node* get_start();
    Node* get_goal();
    void init();

private:
    Grid* grid_ = nullptr;
    Node* start_ = nullptr;
    Node* goal_ = nullptr;
};

#endif // GRIDGRAPH_H
