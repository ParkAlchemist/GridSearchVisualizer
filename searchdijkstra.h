#ifndef SEARCHDIJKSTRA_H
#define SEARCHDIJKSTRA_H

#include <QObject>
#include <cmath>

#include "searchalgorithm.h"
#include "gridgraph.h"
#include "helperfunctions.h"

bool compGvalue(Node* n, Node* m);

class SearchDijkstra : public SearchAlgorithm
{
    Q_OBJECT
public:
    SearchDijkstra();
    ~SearchDijkstra();
    void start(Node* start, Node* goal);
    std::vector<Node*> getPath();

signals:
    void change(int x, int y, Qt::GlobalColor color);

private:
    std::vector<Node*> pq_;
    std::vector<Node*> path_;
};

#endif // SEARCHDIJKSTRA_H
