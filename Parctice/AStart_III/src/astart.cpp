#include "astart.h"

AStart* AStart::s_instance = NULL;
AStart &AStart::getInstance()
{
    if(!s_instance)
    {
        s_instance = new AStart();
    }
    return *s_instance;
}

AStart::AStart() : m_row(0),m_col(0),m_straightCost(0),m_diagoalCost(0)
{
}

const Node* AStart::getPreNode(const Point &pt)
{
    auto iter = m_preNode.find(pt);
    return iter != m_preNode.end() ? &(iter->second) : NULL;
}

unsigned short AStart::getStraightCost()
{
    return m_straightCost;
}

unsigned short AStart::getDiagoalCost()
{
    return m_diagoalCost;
}

bool AStart::init(const std::vector<NodeType> &mapVec,const unsigned short row,const unsigned short col,const unsigned short straightCost,const unsigned short diagoalCost)
{
    m_mapVec.assign(mapVec.begin(),mapVec.end());
    m_row = row;
    m_col = col;
    m_straightCost = straightCost;
    m_diagoalCost = diagoalCost;
    return true;
}

bool AStart::ptOverBroad(const Point &pt)
{
    return pt.m_x >= m_row || pt.m_y >= m_col;
}

Node* AStart::findPtNode(const Point &pt)
{
    auto iter = m_openPtList.find(pt);
    return iter == m_openPtList.end() ? NULL : &(iter->second);
}

bool AStart::ptBarry(const Point &pt)
{
    bool ret = true;
    do
    {
        unsigned short index = pt.m_x + pt.m_y * m_row;
        if(m_mapVec.size() < index)
        {
            break;
        }
        ret = m_mapVec[index] == NT_Barry;
    }while(false);
    return ret;
}

void AStart::getPath(std::list<Node> &retList,const Node *node)
{
    if(node)
    {
        retList.push_back(*node);
        const Node *preNode = getPreNode(node->getPt());
        if(preNode)
        {
            getPath(retList,preNode);
        }
    }
}

bool AStart::inCloseList(const Point &pt)
{
    return m_closeList.find(pt) != m_closeList.end();
}

SearchRet AStart::search(const Point &pt1,const Point &pt2)
{
    SearchRet ret = SR_Error;
    do
    {
        if(ptOverBroad(pt1) || ptOverBroad(pt2))
        {
            break;
        }
        if(ptBarry(pt1) || ptBarry(pt2))
        {
            break;
        }
        ret = SR_NotFound;
        Node begin(pt1);
        Node end(pt2);
        m_openList.insert(std::pair<unsigned int,Node>(begin.getF(),begin));
        m_openPtList.insert(std::pair<Point,Node>(pt1,begin));
        std::list<Node> retList;
        searchNode(end,retList);
        if(retList.empty())
        {
            break;
        }
        printPath(pt1,pt2,retList);
        ret = SR_Find;
    }while(false);
    return ret;
}

void AStart::searchNode(const Node &end,std::list<Node> &retList)
{
    bool ret = false;
    Node *node = NULL;
    while(!m_openList.empty())
    {
        auto iter = m_openList.begin();
        node = &(iter->second);
        const Point &pt = node->getPt();
        if(pt == end.getPt())
        {
            ret = true;
            break;
        }
        if(ptOverBroad(pt))
        {
            break;
        }
        if(ptBarry(pt))
        {
            break;
        }
        //下
        if(pt.m_y - 1 >= 0)
        {
            Point temp(pt.m_x,pt.m_y - 1);
            checkPath(temp,node,end,m_straightCost);
        }
        //上
        if(pt.m_y + 1 >= 0)
        {
            Point temp(pt.m_x,pt.m_y + 1);
            checkPath(temp,node,end,m_straightCost);
        }
        //左
        if(pt.m_x - 1 >= 0)
        {
            Point temp(pt.m_x - 1,pt.m_y);
            checkPath(temp,node,end,m_straightCost);
        }
        //右
        if(pt.m_x + 1 >= 0)
        {
            Point temp(pt.m_x + 1,pt.m_y);
            checkPath(temp,node,end,m_straightCost);
        }
        //左下
        if(pt.m_y - 1 >= 0 && pt.m_x - 1 >= 0)
        {
            Point temp(pt.m_x - 1,pt.m_y - 1);
            checkPath(temp,node,end,m_diagoalCost);
        }
        //右下
        if(pt.m_y - 1 >= 0 && pt.m_x + 1 >= 0)
        {
            Point temp(pt.m_x + 1,pt.m_y - 1);
            checkPath(temp,node,end,m_diagoalCost);
        }
        //左上
        if(pt.m_y + 1 >= 0 && pt.m_x - 1 >= 0)
        {
            Point temp(pt.m_x - 1,pt.m_y + 1);
            checkPath(temp,node,end,m_diagoalCost);
        }
        //右上
        if(pt.m_y + 1 >= 0 && pt.m_x + 1 >= 0)
        {
            Point temp(pt.m_x + 1,pt.m_y + 1);
            checkPath(temp,node,end,m_diagoalCost);
        }
        m_closeList.insert(pt);
        m_openList.erase(iter);
        m_openPtList.erase(pt);
        //printPath(pt,end->getPt(),m_openList);
    }
    if(ret)
    {
        getPath(retList,node);
    }
    return ;
}

void AStart::printPath(const Point &begin,const Point &end,const std::list<Node> &retList)
{
    std::cout << "begin path(" << begin.m_x << "," << begin.m_y << ")"<< std::endl;
    for(auto iter = retList.begin();iter != retList.end();++iter)
    {
        const Node &node = *iter;
        const Point &pt = node.getPt();
        std::cout << "node(" << pt.m_x << "," << pt.m_y << "," << node.getF() << ")" << std::endl;
    }
    std::cout << "end path(" << end.m_x << "," << end.m_y << ")"<< std::endl;
}

bool AStart::checkPath(const Point &pt,const Node *parent,const Node &end,const unsigned short cost)
{
    bool ret = false;
    do
    {
        Node node(pt);
        if(ptOverBroad(pt) || ptBarry(pt))
        {
            m_closeList.insert(pt);
            break;
        }
        if(inCloseList(pt))
        {
            break;
        }
        m_preNode.insert(std::pair<Point,Node>(pt,*parent));
        node.count(end,cost);
        Node *pNode = findPtNode(pt);
        if(pNode)
        {
            if(pNode->getF() > node.getF())
            {
                *pNode = node;
            }
        }
        else
        {
            m_openPtList.insert(std::pair<Point,Node>(pt,node));
            m_openList.insert(std::pair<unsigned int,Node>(node.getF(),node));
        }
        ret = true;
    }while(false);
    return ret;
}

int main(void)
{
    std::vector<NodeType> vec;
    for(int col = 0;col < 5;++col)
    {
        for(int row = 0; row < 5;++row)
        {
            NodeType val = NT_Pass;
            if(col == 1 && row == 1)
            {
                val = NT_Barry;
            }
            vec.push_back(val);
        }
    }
    

    AStart::getInstance().init(vec,5,5,10,14);
    Point begin(0,0),end(2,2);
    SearchRet ret = AStart::getInstance().search(begin,end);
    switch(ret)
    {
        case SR_Error:
            {
                std::cout << "数据错误" << std::endl;
            }
            break;
        case SR_NotFound:
            {
                std::cout << "没找到" << std::endl;
            }
            break;
        case SR_Find:
            {
            }
            break;
        default:
            {
                break;
            }
    }
    return 0;
}

