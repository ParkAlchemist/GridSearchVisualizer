#include "helperfunctions.h"



float distance(Node *src, Node *dst)
{
    int dx = abs(dst->x - src->x);
    int dy = abs(dst->y - src->y);
    float dist = std::sqrt( dx*dx + dy*dy);
    return dist;
}

float manhattan(Node *src, Node *dst)
{
    int dx = abs(dst->x - src->x);
    int dy = abs(dst->y - src->y);
    return dx + dy;
}

float octal(Node *src, Node *dst)
{
    int dx = abs(dst->x - src->x);
    int dy = abs(dst->y - src->y);
    return 1 * (dx + dy) + (std::sqrt(2) - 2 * 1) * std::min(dx, dy);
}

float euclidian(Node *src, Node *dst)
{
    int dx = abs(dst->x - src->x);
    int dy = abs(dst->y - src->y);
    float dist = std::sqrt( dx*dx + dy*dy);
    return dist;
}

float chebyshev(Node *src, Node *dst)
{
    int dx = abs(dst->x - src->x);
    int dy = abs(dst->y - src->y);
    return 1 * (dx + dy) + (1 - 2 * 1) * std::min(dx, dy);
}

bool compGvalue(Node *n, Node *m)
{
    return n->dist < m->dist;
}

bool compHvalue(Node *n, Node *m)
{
    return n->heuristic < m->heuristic;
}

bool compFvalue(Node *n, Node *m)
{
    return n->dist + n->heuristic < m->dist + m->heuristic;
}

float distancePtL(float x1, float y1, float x2, float y2, float x0, float y0)
{
    float numerator = std::abs( (x2 - x1)*(y1 - y0) - (x1 - x0)*(y2 - y1) );
    float denumerator = std::sqrt( pow((x2 - x1), 2.0 ) + pow((y2 - y1), 2.0 ) );
    float dist = numerator/denumerator;
    return dist;
}

std::string precision(float num, int places)
{
    // round to desired precision
    int deca = std::pow(10, places);
    float value = (int)(num * deca + 0.5);
    value = (float)(value/deca);

    std::string s = std::to_string(value);
    std::size_t found = s.find(".");
    if(found != std::string::npos){
        s = s.substr(0, found + 1 + places);
        return s;
    }
    return s;
}

bool intersectsNode(float x1, float y1, float x2, float y2, float x3, float y3, Grid* g)
{
    float top = y3;
    float bottom = y3+1;
    float left = x3;
    float right = x3+1;

    Point p = line_line_intersect(x1, y1, x2, y2, left, top, right, top);

    if(checkCorners(p, left, right, top, bottom, g)){
        return true;
    }

    if(p.found){
        if(p.x > left && p.x < right){ // intersects top
            return true;
        }
    }

    p = line_line_intersect(x1, y1, x2, y2, left, bottom, right, bottom);

    if(checkCorners(p, left, right, top, bottom, g)){
        return true;
    }

    if(p.found){
        if(p.x > left && p.x < right){ // intersects bottom
            return true;
        }
    }

    p = line_line_intersect(x1, y1, x2, y2, left, top, left, bottom);

    if(checkCorners(p, left, right, top, bottom, g)){
        return true;
    }

    if(p.found){
        if(p.y < bottom && p.y > top){ // intersects left side
            return true;
        }
    }

    p = line_line_intersect(x1, y1, x2, y2, right, top, right, bottom);

    if(checkCorners(p, left, right, top, bottom, g)){
        return true;
    }

    if(p.found){
        if(p.y < bottom && p.y > top){ // intersects right side
            return true;
        }
    }

    p = line_line_intersect(x1, y1, x2, y2, left, bottom, right, top);

    if(checkCorners(p, left, right, top, bottom, g)){
        return true;
    }

    if(p.found){
        if(p.y < bottom && p.y > top && p.x > left && p.x < right){ // intersects falling diagonal
            return true;
        }
    }

    p = line_line_intersect(x1, y1, x2, y2, right, bottom, left, top);

    if(checkCorners(p, left, right, top, bottom, g)){
        return true;
    }

    if(p.found){
        if(p.y < bottom && p.y > top && p.x > left && p.x < right){ // intersects rising diagonal
            return true;
        }
    }

    return false;
}

Point line_line_intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    Point p;

    float x_denom = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);

    if(x_denom == 0){
        p.found = false;
        return p;
    }
    float x_nom = (x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4);
    float y_nom = (x1*y2-y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    float y_denom = x_denom;

    float p_x = x_nom/x_denom;
    float p_y = y_nom/y_denom;

    p.x = p_x;
    p.y = p_y;
    p.found = true;

    return p;
}

bool checkCorners(Point p, float left, float right, float top, float bottom, Grid* g)
{
    if(p.x == left && p.y == bottom){ // top left corner
        Node* n = g->at(bottom).at(left-1);
        if(n->state == State::Obstacle){
            return true;
        }
    }
    if(p.x == right && p.y == bottom){ // top right corner
        Node* n = g->at(bottom).at(right);
        if(n->state == State::Obstacle){
            return true;
        }
    }
    if(p.x == left && p.y == top){ // bottom left corner
        Node* n = g->at(top).at(left-1);
        if(n->state == State::Obstacle){
            return true;
        }
    }
    if(p.x == right && p.y == top){ // bottom right corner
        Node* n = g->at(top).at(right);
        if(n->state == State::Obstacle){
            return true;
        }
    }
    return false;
}
