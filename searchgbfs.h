#ifndef SEARCHGBFS_H
#define SEARCHGBFS_H

#include <QObject>

#include "searchalgorithm.h"
#include "gridgraph.h"
#include "helperfunctions.h"

class SearchGBFS : public SearchAlgorithm
{
    Q_OBJECT
public:
    SearchGBFS(int heur);
    ~SearchGBFS();
    void start(Node* start, Node* goal);
    std::vector<Node*> getPath();

signals:
    void change(int x, int y, Qt::GlobalColor color);

private:
    std::vector<Node*> pq_;
    std::vector<Node*> path_;
    float (*heur_func)(Node*, Node*);
};

#endif // SEARCHGBFS_H
