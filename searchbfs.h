#ifndef SEARCHBFS_H
#define SEARCHBFS_H

#include <QObject>

#include "searchalgorithm.h"

class SearchBFS : public SearchAlgorithm
{
    Q_OBJECT
public:
    SearchBFS();
    ~SearchBFS();
    void start(Node* start, Node* goal);
    std::vector<Node*> getPath();

signals:
    void change(int x, int y, Qt::GlobalColor color);

private:
    std::vector<Node*>* pq_;
    std::vector<Node*> path_;
};

#endif // SEARCHBFS_H
