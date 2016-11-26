/************************************************************
	文件名：statuaryHero.cpp
	文件作用：StatuaryHero类的实现文件
	作者：chenzhen
	创建日期：2013.03.01
************************************************************/

#include"statuaryHero.h"
#include"map_src.h"
#include"nbox.h"
extern map<string,Map_Src*>mapId_connect_map;
extern set<Point> statuaryPtSet;
StatuaryHero::StatuaryHero(MemStatuaryHero* _memStatuaryHero)
{	
	set<Point>::iterator pt_it;
	
	memStatuaryHero = _memStatuaryHero;
	
	piexPt._x = memStatuaryHero->piex_x;
	
	piexPt._y = memStatuaryHero->piex_y;
	
	memset(inSeeMsg,'\0',sizeof(inSeeMsg));
	
	memset(outSeeMsg,'\0',sizeof(outSeeMsg));
	
	if(!initMapInform())
	{
		cout<<"StatuaryHero::StatuaryHero initMap is error:"<<endl;
	}
	
	if(statuaryPtSet.empty())
	{
		cout<<"StatuaryHero::StatuaryHero statuaryPtSet is empty is error:"<<endl;
	}
	
	/*设置坐标*/
	pt_it = statuaryPtSet.find(piexPt);
	if(pt_it == statuaryPtSet.end())
	{
		piexPt = *statuaryPtSet.begin();
		statuaryPtSet.erase(statuaryPtSet.begin());
	}
	else
	{
		statuaryPtSet.erase(pt_it);
	}
	
	memStatuaryHero->piex_x = piexPt._x;
	memStatuaryHero->piex_y = piexPt._y;
	
	formInSeeMsg();
	
	cout<<"inSeeMsg:"<<inSeeMsg<<endl;
	
	formOutSeeMsg();
	
}

/*获得关联角色id*/
char* StatuaryHero::getHeroId(void)
{
	return memStatuaryHero->heroId;
}

/*获得memStatuaryHero*/
MemStatuaryHero* StatuaryHero::getMemStatuaryHero(void)
{
	return memStatuaryHero;
}

/*析构函数*/
StatuaryHero::~StatuaryHero(void)
{
	delete memStatuaryHero;
	memStatuaryHero = NULL;
	map_now = NULL;
}


/*生成上线消息*/
void StatuaryHero::formInSeeMsg(void)
{
	snprintf(inSeeMsg,sizeof(inSeeMsg),"2,30,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d",memStatuaryHero->requre,memStatuaryHero->vocation,\
	memStatuaryHero->photoId,memStatuaryHero->heroId,memStatuaryHero->heroName,memStatuaryHero->level,memStatuaryHero->lifeUpperVal,\
	memStatuaryHero->lifeVal,memStatuaryHero->magicUpperVal,memStatuaryHero->magicVal,piexPt._x,piexPt._y);
}	

/*生成下线消息*/
void StatuaryHero::formOutSeeMsg(void)
{
	strncpy(outSeeMsg,"2,5,1",5);
}

/*获得上线消息*/
char* StatuaryHero::getInSeeMsg(void)
{
	return inSeeMsg;
}

/*获得下线消息*/
char* StatuaryHero::getOutSeeMsg(void)
{
	return outSeeMsg;
}

/*初始化地图实例指针*/
bool StatuaryHero::initMapInform(void)
{
	map<string,Map_Src*>::iterator map_it;
	map_it = mapId_connect_map.find(memStatuaryHero->mapId);
	
	if(map_it == mapId_connect_map.end())
	{
		cout<<"StatuaryHero::initMapInform is error :"<<memStatuaryHero->mapId<<endl;
		return false;
	}
	
	map_now = map_it->second;
	return true;
}

/*获得像素坐标*/
Point StatuaryHero::getPiexPt(void)
{
	return piexPt;
}

/*刷出雕像*/
void StatuaryHero::brushMsg(void)
{
	StyObj obj(memStatuaryHero->titleId,STATUARY_STYLE_TYPE);
	Nbox *box;               
	 
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}

	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(inSeeMsg);

#if 0	
	cout<<"STATUARY_STYLE_TYPE:"<<STATUARY_STYLE_TYPE<<endl;
	cout<<"memStatuaryHero->titleId:"<<memStatuaryHero->titleId<<endl;
	cout<<"inSeeMsg:"<<inSeeMsg<<endl;
#endif
}

/*摧毁雕像*/
void StatuaryHero::destoryMsg(void)
{
	StyObj obj(memStatuaryHero->titleId,STATUARY_STYLE_TYPE);
	Nbox *box;               
	 
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(outSeeMsg);
	
	map_now->deleteID(obj);
	
	/*回收坐标点*/
	statuaryPtSet.insert(piexPt);

#if 0	
	cout<<"STATUARY_STYLE_TYPE:"<<STATUARY_STYLE_TYPE<<endl;
	cout<<"memStatuaryHero->titleId:"<<memStatuaryHero->titleId<<endl;
	cout<<"outSeeMsg:"<<outSeeMsg<<endl;
#endif
}

/*修改坐标*/
void StatuaryHero::setPiex(Point _piexPt)
{
	piexPt = _piexPt;
}
	
	

