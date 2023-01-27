#ifndef SEARCHDFS_H
#define SEARCHDFS_H

#include <QObject>

#include "searchalgorithm.h"

class SearchDFS : public SearchAlgorithm
{
    Q_OBJECT
public:
    SearchDFS();
    ~SearchDFS();
    void start(Node* n, Node* goal);
    std::vector<Node*> getPath();

signals:
    void change(int x, int y, Qt::GlobalColor color);
private:
    bool end_ = false;
    std::vector<Node*> path_;
};

#endif // SEARCHDFS_H
