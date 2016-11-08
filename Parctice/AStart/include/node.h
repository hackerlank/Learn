#ifndef NODE_H
#define NODE_H 
#include <iostream>
#include <algorithm>
using namespace std;

//坐标点
typedef struct Point
{
    //x坐标
    unsigned short m_x;
    //y坐标
    unsigned short m_y;

    Point(const unsigned short x = 0,const unsigned short y = 0) : m_x(x),m_y(y)
    {
    }

    Point(const Point &pt)
    {
        m_x = pt.m_x;
        m_y = pt.m_y;
    }

    bool operator< (const Point &pt) const
    {
        bool ret = false;
        do
        {
            if(m_x != pt.m_x)
            {
                ret = m_x < pt.m_x;
                break;
            }
            if(m_y != pt.m_y)
            {
                ret = m_y < pt.m_y;
                break;
            }
        }while(false);
        return ret;
    }

    bool operator== (const Point &pt) const
    {
        return m_x == pt.m_x && m_y == pt.m_y;
    }
}Point;

class Node;

//节点
class Node
{
    private:
        //坐标
        Point m_point;
        //当前点到起点的移动耗费
        unsigned short m_g;
        //当前点到终点的移动耗费，即曼哈顿距离|x1-x2|+|y1-y2|(忽略障碍物)
        unsigned short m_h;
        //f(总耗费) = h + g
        unsigned short m_f;
        //父节点
        Node *m_parent;
    public:
        Node(const Point &point,Node *parent);
        Node(const Node &node);
        const Point& getPt() const;
        unsigned short getG() const;
        unsigned short getH() const;
        unsigned short getF() const;
        Node* getParent() const;
        void setX(const unsigned short x);
        void setY(const unsigned short y);
        void setG(const unsigned short g);
        void setF(const unsigned short f);
        void setParent(Node *parent);
        void countG(const unsigned short cost);
        void countH(const Node *end);
        void countF();
        void count(const Node *end,const unsigned short cost);
};

#endif
