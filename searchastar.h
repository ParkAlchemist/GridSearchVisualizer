#ifndef SEARCHASTAR_H
#define SEARCHASTAR_H

#include <QObject>

#include "searchalgorithm.h"
#include "gridgraph.h"
#include "helperfunctions.h"

class SearchAStar : public SearchAlgorithm
{
    Q_OBJECT
public:
    SearchAStar(int heur);
    ~SearchAStar();
    void start(Node* start, Node* goal);
    std::vector<Node*> getPath();

signals:
    void change(int x, int y, Qt::GlobalColor color);

private:

    std::vector<Node*> pq_;
    std::vector<Node*> path_;
    float (*heur_func)(Node*, Node*);
};

#endif // SEARCHASTAR_H
