#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#include <QObject>
#include <algorithm>
#include <vector>

#include "gridgraph.h"

enum Algorithm{DFS, BFS, Dijkstra, A_star, GBFS};
enum Heuristic{Manhattan, Octal, Euclidian, Chebyshev, H_none};

// abstract base class for other searchalgoritms
class SearchAlgorithm : public QObject
{
    Q_OBJECT
public:
    SearchAlgorithm();
    ~SearchAlgorithm();
    virtual void start(Node* start, Node* goal);
    virtual std::vector<Node*> getPath();

signals:
    void change();

private:
    std::vector<Node*> pq_; // priority queue
    std::vector<Node*> path_;
};

#endif // SEARCHALGORITHM_H
