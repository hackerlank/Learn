#include "pick.h"
#include"boxAsist.h"
#include"map_inform.h"
extern map<string,Pick*> goods_to_hero;  //拾取物品 jolly add
extern struct ev_loop *loops;
extern char g_out_buf[20480];
static void threeMinutes(struct ev_loop *loop,ev_timer *think,int revents)
{	
	ev_timer_stop(loop,think);	
	Pick *pick=(Pick*)think->target;
	if (pick==NULL)
	{
		cout<<"jolly:Three timer has no pick pick 30"<<endl;
		return;
	}
	else
	{	
		memset(g_out_buf,0,sizeof(g_out_buf));//added by benliao	
		pick->msg_threeMinutes(g_out_buf,sizeof(g_out_buf));
		pick->send_nbox(g_out_buf);
		pick->setBound(1);
	}
}

static void fiveMinutes(struct ev_loop *loop,ev_timer *think,int revents)
{	
	Map_Inform *map_now;
	
	ev_timer_stop(loop,think);
	
	Pick *pick=(Pick*)think->target;
	
	if (pick==NULL)
	{
		cout<<"jolly:Five timer has no pick pick 57"<<endl;
		return;
	}
	else
	{			
		memset(g_out_buf,0,sizeof(g_out_buf));
		pick->msg_fiveMinutes();
	}
	
	map_now = pick->getMap();
	if(map_now == NULL)
	{
	
		cout<<"it is NUll of the pick map:"<<pick->getFlag()<<endl;
		return;
	}
	
	map_now->deleteDropInst(pick->getFlag());

	// goods_to_hero.erase(pick->getIdentity());

	// delete pick; //by benliao 2012.12.7
}

Pick::Pick(char *_flag,char *_killHeroId,int _num,Map_Inform *_dropmap,int _bound,Point _deadPoint)
{
	strncpy(flag,_flag,sizeof(flag));
	strncpy(killHeroId,_killHeroId,sizeof(killHeroId));
	// cout<<"_killHeroId is:"<<_killHeroId<<endl;
	// cout<<"killHeroId is:"<<killHeroId<<endl;
	num=_num;
	dropmap=_dropmap;
	pt_to_goodsid.clear();
	bound=_bound;
	deadPoint=_deadPoint;
	three_timer=new ev_timer;
	five_timer=new ev_timer;
	
	piexPt=deadPoint;
	// cout<<"jolly test begin:"<<endl;
	// cout<<"drop x: "<<piexPt._x<<endl;
	// cout<<"drop y: "<<piexPt._y<<endl;
	// cout<<"jolly test end:"<<endl;
	// exChgePiex();
}

void Pick::msg_threeMinutes(char* msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%s",9,PICK_RETURN,FAILED,flag);
	map<string,string>::iterator it;
	for (it=pt_to_goodsid.begin();it!=pt_to_goodsid.end();++it)
	{
		snprintf(msg+strlen(msg),len-strlen(msg),"%s",(it->first).c_str());
	}
	// cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&   "<<msg<<endl;
}

void Pick::msg_fiveMinutes(void)
{
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,PICK_RETURN,SUCCESS,flag);	
	map<string,string>::iterator it;
	for (it=pt_to_goodsid.begin();it!=pt_to_goodsid.end();++it)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),"%s",(it->first).c_str());
	}
	send_nbox(g_out_buf);
	cout<<"g_out_buf:"<<g_out_buf<<endl;
}

char* Pick::getFlag(void)
{
	return flag;
}

char* Pick::getIdentity(void)
{
	return flag;
}

char* Pick::getKillHeroId(void)
{
	return killHeroId;
}

Map_Inform* Pick::getMap(void)
{
	return dropmap;
}

map<string,string> Pick::getDropGoods(void)
{
	return pt_to_goodsid;
}

int Pick::getBound(void)
{
	return bound;
}
void Pick::setBound(int _bound)
{
	bound=_bound;
}

int Pick::getNum(void)
{
	return num;
}
	
void Pick::setNum(int _num)
{
	num=_num;
}

void Pick::setDropGoods(map<string,string> _pt_to_goodsid)
{
	pt_to_goodsid=_pt_to_goodsid;
}

Point Pick::getDeadPoint(void)
{
	return deadPoint;
}

void Pick::initPickTimer(void)
{
	ext_ev_timer_init(three_timer,threeMinutes,30,0,this);
	ev_timer_start(loops,three_timer);
	ext_ev_timer_init(five_timer,fiveMinutes,60,0,this);
	ev_timer_start(loops,five_timer);
}

void Pick::stopThreeTimer(void)
{
	ev_timer_stop(loops,three_timer);
}

void Pick::stopFiveTimer(void)
{
	ev_timer_stop(loops,five_timer);
}

Pick::~Pick(void)
{
	if (three_timer!=NULL)
	{		
		ev_timer_stop(loops,three_timer); //added by benliao to avoid invalid timer
		delete three_timer;
		three_timer=NULL;
	}
	if (five_timer!=NULL)
	{
		ev_timer_stop(loops,five_timer);//added by benliao to avoid invalid timer
		delete five_timer;
		five_timer=NULL;
	}	
}
	
	
void Pick::msg_online(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%s,%d,%s",9,DROP_GOODS,killHeroId,bound,flag);
	map<string,string>::iterator it;
	for (it=pt_to_goodsid.begin();it!=pt_to_goodsid.end();++it)
	{
		snprintf(msg+strlen(msg),len-strlen(msg),"%s,%s",(it->first).c_str(),(it->second).c_str());
	}
	cout<<"msg:"<<msg<<endl;
}

void Pick::msg_offline(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%s",9,PICK_RETURN,SUCCESS,flag);
	map<string,string>::iterator it;
	for (it=pt_to_goodsid.begin();it!=pt_to_goodsid.end();it++)
	{
		snprintf(msg+strlen(msg),len-strlen(msg),"%s",(it->first).c_str());
	}
	cout<<"msg:"<<msg<<endl;
}

void Pick::send_nbox(char* _msg)
{
	Nbox *box;
	
	box = dropmap->getBox();
	
	if(box == NULL)
	{
		return;
	}
	
	StyObj obj(flag,PICK_STYLE_TYPE);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(_msg);
}

/*获得像素坐标*/
Point Pick::getPiexPt(void)
{
	return piexPt;
}

/*逻辑转像素*/
void Pick::exChgePiex(void)
{
	// Point logPt;
	// logPt = deadPoint;
	// if(dropmap == NULL)
	// {
		// return;
	// }
	// logPt._y -= dropmap->getBaseDigst();
	// piexPt = LogicalExchangeMap(logPt);
}

//添加掉落的物品到pt_togoodsId中
void Pick::insertDropGoods(char *pt_flag,char *goodsId)
{
	pt_to_goodsid.insert(map<string,string>::value_type(pt_flag,goodsId));
}
