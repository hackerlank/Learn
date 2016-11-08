#include "node.h"
#include "astart.h"

Node::Node(const Point &point,Node *parent):m_point(point),m_g(0),m_f(0),m_h(0),m_parent(parent)
{
}

Node::Node(const Node &node)
{
    m_point = node.getPt();
    m_g = node.getG();
    m_f = node.getF();
    m_h = node.getH();
    m_parent = node.getParent();
}


const Point& Node::getPt() const
{
    return m_point;
}

unsigned short Node::getG() const
{
    return m_g;
}

unsigned short Node::getH() const
{
    return m_h;
}

unsigned short Node::getF() const
{
    return m_f;
}

Node* Node::getParent() const
{
    return m_parent;
}

void Node::setX(const unsigned short x)
{
    m_point.m_x = x;
}

void Node::setY(const unsigned short y)
{
    m_point.m_y = y;
}

void Node::setG(const unsigned short g)
{
    m_g = g;
}

void Node::setF(const unsigned short f)
{
    m_f = f;
}

void Node::setParent(Node *parent)
{
    m_parent = parent;
}

void Node::countG(const unsigned short cost)
{
    m_g = m_parent ? m_parent->getG() + cost : cost;
}

void Node::countH(const Node *end)
{
    const Point &pt = end->getPt();
    unsigned short xSub = abs(m_point.m_x - pt.m_x);
    unsigned short ySub = abs(m_point.m_y - pt.m_y);
    unsigned short minXy = xSub < ySub ? xSub : ySub;
    unsigned short val = minXy * AStart::s_diagoalCost + abs(xSub - ySub) * AStart::s_straightCost;
    m_h = val;
}

void Node::countF()
{
    m_f = m_g + m_h;
}

void Node::count(const Node *end,const unsigned short cost)
{
    countG(cost);
    countH(end);
    countF();
}


