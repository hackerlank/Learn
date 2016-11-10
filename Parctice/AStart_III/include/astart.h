#ifndef ASTART_H
#define ASTART_H
#include "node.h"
#include <vector>
#include <list>
#include <set>
#include <map>

enum NodeType
{
    //障碍点
    NT_Barry = 0,
    //可通过
    NT_Pass = 1,
};

//寻路结果
enum SearchRet
{
    //出错
    SR_Error = -1,
    //没找到
    SR_NotFound = 0,
    //找到
    SR_Find = 1,
};


class AStart
{
    private:
        //地图每个点信息
        std::vector<NodeType> m_mapVec;
        //开放列表
        std::multimap<unsigned int,Node> m_openList;
        std::map<Point,Node> m_openPtList;
        //关闭列表
        std::set<Point> m_closeList;
        //地图行
        unsigned short m_row;
        //地图列
        unsigned short m_col;
        //直走代价
        unsigned short m_straightCost;
        //斜走代价
        unsigned short m_diagoalCost;
        //前置节点
        std::map<Point,Node> m_preNode;
        //单例模式
        static AStart *s_instance;
    private:
        Node* findPtNode(const Point &pt);
        //越界为true
        bool ptOverBroad(const Point &pt);
        //障碍true
        bool ptBarry(const Point &pt);
        //在关闭列表中为true
        bool inCloseList(const Point &pt);
        //获得路径
        void getPath(std::list<Node> &retList,const Node *node);
        //检查路径
        bool checkPath(const Point &pt,const Node *parent,const Node &end,const unsigned short cost);
        void printPath(const Point &begin,const Point &end,const std::list<Node> &retList);
        //构造函数
        AStart();
        void searchNode(const Node &end,std::list<Node> &retList);
    public:
        //初始化
        bool init(const std::vector<NodeType> &mapVec,const unsigned short row,const unsigned short col,const unsigned short straightCost,const unsigned short diagoalCost);
        //寻路
        SearchRet search(const Point &pt1,const Point &pt2);
        //获得直线斜线的代价
        unsigned short getStraightCost();
        unsigned short getDiagoalCost();
        //获得单例
        static AStart& getInstance();
        //获得前置节点
        const Node* getPreNode(const Point &pt);
};

#endif
