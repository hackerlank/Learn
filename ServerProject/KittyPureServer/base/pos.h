#ifndef POS_H
#define POS_H

#include "zType.h"


struct Point
{
    int x;
    int y;
    Point(const int _x = 0,const int _y = 0) : x(_x),y(_y)
    {
    }
    
    Point(const Point &point) : x(point.x),y(point.y)
    {
    }

#if 0
    Point(const HelloKittyMsgData::Point &point) : x(point.x()),y(point.y())
    {
    }

    bool save(HelloKittyMsgData::Point *point)
    {
        point->set_x(x);
        point->set_y(y);
        return true;
    }
#endif
    Point& operator= (const Point &point)
    {
        x = point.x;
        y = point.y;
        return *this;
    }
    
    bool operator < (const Point &point) const
    {
        if(x < point.x)
        {
            return true;
        }
        if(x == point.x)
        {
            return y < point.y;
        }
        return false;
    }

    bool operator == (const Point &point) const
    {
        return x == point.x && y == point.y;
    }

    bool operator != (const Point &point) const
    {
        return !(*this == point);
    }

    int hashKey() const
    {
        return ((x >> 16) + y);
    }

};

class AreaGrid
{
    public:
        Point m_point;
        bool m_isOpen;
        AreaGrid(const Point &point = Point(),const bool isOpen = false) : m_point(point),m_isOpen(isOpen)
        {
        }
#if 0
        AreaGrid(const HelloKittyMsgData::AreaGrid &areaGrid) : m_point(areaGrid.point()),m_isOpen(areaGrid.isopen())
        {
        }
#endif
        AreaGrid(const AreaGrid &areaGrid) : m_point(areaGrid.m_point),m_isOpen(areaGrid.m_isOpen)
        {
        }

#if 0
        bool save(HelloKittyMsgData::AreaGrid *areaGrid)
        {
            if(!areaGrid)
            {
                return false;
            }

            HelloKittyMsgData::Point *point = areaGrid->mutable_point();
            m_point.save(point);
            areaGrid->set_isopen(m_isOpen);
            return true;
        }
#endif
};

class GateGrid
{
    public:
        Point m_point;
        GateGrid(const Point &point = Point()) : m_point(point)
        {
        }
#if 0
        GateGrid(const HelloKittyMsgData::GateGrid &gateGrid) : m_point(gateGrid.point())
        {
        }
#endif
        GateGrid(const GateGrid& gateGrid) : m_point(gateGrid.m_point)
        {
        }

#if 0
        bool save(HelloKittyMsgData::GateGrid *gateGrid)
        {
            if(!gateGrid)
            {
                return false;
            }

            HelloKittyMsgData::Point *point = gateGrid->mutable_point();
            m_point.save(point);
            return true;
        }
#endif
};

#endif

