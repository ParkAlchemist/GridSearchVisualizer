#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <cmath>
#include <algorithm>
#include <math.h>
#include <QPointF>

#include "gridgraph.h"

struct Point{
    float x = 0;
    float y = 0;
    bool found = false;
};

float distance(Node* src, Node* dst);
float distancePtL(float x1, float y1, float x2, float y2, float x0, float y0);
bool intersectsNode(float x1, float y1, float x2, float y2, float x0, float y0, Grid* g);
Point line_line_intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
bool checkCorners(Point p, float left, float right, float top, float bottom, Grid* g);

float manhattan(Node* src, Node* dst);
float octal(Node* src, Node* dst);
float euclidian(Node* src, Node* dst);
float chebyshev(Node* src, Node* dst);

std::string precision(float num, int places);

bool compGvalue(Node* n, Node* m);
bool compFvalue(Node* n, Node* m);
bool compHvalue(Node* n, Node* m);


#endif // HELPERFUNCTIONS_H
