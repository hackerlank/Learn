/* 
		文件类型：头文件
		文件名称：hero.cpp
		文件作用：实体类装备的属性和功能的实现
		实现时间：2012.4.16 11:00
		  实现人：Evan
*/
#include"equipment.h"
#include"user_role_manage_assist.h"
#include"bag.h"
#include"dropEquipAction.h"
extern struct ev_loop *loops;
extern char g_out_buf[20480];
extern Equip_Operator equip_operator[51];
Equipment::Equipment(Equip_config *equip_pt)
{
	equipmentdata=new EquipmentData();
	
	char identity[40];
	memset(identity,'\0',40);
	char* uuid = cid();
	sprintf(identity,"%s%s","ZB",uuid);
	free(uuid); //avoid mem leak by benliao 20121129
	strncpy(equipmentdata->entityid,identity,sizeof(equipmentdata->entityid));
	strncpy(equipmentdata->id,equip_pt->getid(),sizeof(equipmentdata->id));           //装备ID
	strncpy(equipmentdata->name,equip_pt->getname(),sizeof(equipmentdata->name));		 //装备名称
	strncpy(equipmentdata->party,equip_pt->getparty(),sizeof(equipmentdata->party));        //装备门派
	strncpy(equipmentdata->suit_id,equip_pt->getsuit_id(),sizeof(equipmentdata->suit_id));      //套装ID	
	strncpy(equipmentdata->photoId,equip_pt->getPhotoId(),sizeof(equipmentdata->photoId));		//图片id
	equipmentdata->grade=equip_pt->getgrade();        //装备等级
	equipmentdata->rank=equip_pt->getrank();         //装备级别
	equipmentdata->type=equip_pt->gettype();         //装备类型
	equipmentdata->suit_type=equip_pt->getsuit_type();    //套装类别
	equipmentdata->durability = equip_pt->getdurability();   //耐久度
	equipmentdata->durabilityLimit = equipmentdata->durability;   //耐久度
	equipmentdata->price=equip_pt->getMoney();        //价格
	equipmentdata->gold=equip_pt->getgold();
	equipmentdata->goldBound=equip_pt->getgoldBound();
	equipmentdata->priceBound=equip_pt->getMoneyBound();
	equipmentdata->sellPrice=equip_pt->getPrice(); 
	equipmentdata->move=equip_pt->getMove();
	equipmentdata->isbag = 0;		//装备是否穿在身上 0，在背包内；1
	equipmentdata->isWear=0;			//装备是否穿戴过
	equipmentdata->holeNumber = equip_pt->getHole();		 //装备打孔的数目	
	equipmentdata->time=equip_pt->getTime();				//持续时间
	cout<<"equipmentdata->time:"<<equipmentdata->time<<endl;
	equipmentdata->beginTime=0;								//开始时间
	equipmentdata->fourDiamonNumber=0;
	equipmentdata->attrNumber=equip_pt->getAttrNumber();
	if (strncmp(equipmentdata->id,"f",1))
	{
		equipmentdata->bound=1;
	}
	else
	{
		equipmentdata->bound=0;
	}
	map_now = NULL;
	
	equipmentdata->equipmentBase.life=equip_pt->getlife();         //生命值
	equipmentdata->equipmentBase.magic=equip_pt->getgenuine();      //真气
	equipmentdata->equipmentBase.inattack=equip_pt->getinattack();     //内功攻击
	equipmentdata->equipmentBase.outattack=equip_pt->getoutattack();    //外功攻击
	equipmentdata->equipmentBase.indefence=equip_pt->getindefence();    //内功防御
	equipmentdata->equipmentBase.outdefence=equip_pt->getoutdefence();   //外功防御
	equipmentdata->equipmentBase.crit=equip_pt->getcrit();         //暴击
	equipmentdata->equipmentBase.hit=equip_pt->gethit(); 		 //命中
	equipmentdata->equipmentBase.dodge=equip_pt->getdodge();        //闪避
	equipmentdata->equipmentBase.tenacity=equip_pt->gettenacity(); 	 //韧性
	
	equipmentdata->equipmentRongLian.life=0;         //生命值
	equipmentdata->equipmentRongLian.magic=0;      //真气
	equipmentdata->equipmentRongLian.inattack=0;     //内功攻击
	equipmentdata->equipmentRongLian.outattack=0;    //外功攻击
	equipmentdata->equipmentRongLian.indefence=0;    //内功防御
	equipmentdata->equipmentRongLian.outdefence=0;   //外功防御
	equipmentdata->equipmentRongLian.rongLianLevel=0;   
	equipmentdata->equipmentRongLian.rongLianLucky=0;   
	equipmentdata->equipmentRongLian.rongLianCost=equip_pt->getJinglianCost();   
	
	equipmentdata->equipmentKaiRen.crit=0;         //暴击
	equipmentdata->equipmentKaiRen.hit=0; 		 //命中
	equipmentdata->equipmentKaiRen.dodge=0;        //闪避
	equipmentdata->equipmentKaiRen.tenacity=0; 	 //韧性
	equipmentdata->equipmentKaiRen.kaiRenLevel=0; 	 						
	equipmentdata->equipmentKaiRen.kaiRenCost=equip_pt->getCulianCost();
	
	equipmentdata->equpmentDiamon.life=0;         //生命值
	equipmentdata->equpmentDiamon.magic=0;      //真气
	equipmentdata->equpmentDiamon.inattack=0;     //内功攻击
	equipmentdata->equpmentDiamon.outattack=0;    //外功攻击
	equipmentdata->equpmentDiamon.indefence=0;    //内功防御
	equipmentdata->equpmentDiamon.outdefence=0;   //外功防御
	equipmentdata->equpmentDiamon.crit=0;         //暴击
	equipmentdata->equpmentDiamon.hit=0; 		 //命中
	equipmentdata->equpmentDiamon.dodge=0;        //闪避
	equipmentdata->equpmentDiamon.tenacity=0; 	 //韧性
	
	int i = 0;
	for(i; i<10; i++)
	{
		bs_xq_num[i] = 0;
	}
	
	countAttribute();
}

Equipment::Equipment(EquipmentData *_equipmentdata)
{		
	equipmentdata=new EquipmentData();
	*equipmentdata=*_equipmentdata;
	
	int i;
	for(i=0; i<10; i++)
	{
		bs_xq_num[i] = 0;
	}
	
	string test=equipmentdata->xq_bs;
	string str;
	string d;
	string b=";";
	for(i=0; i<test.size(); i++)
	{			
		d.push_back(test[i]);
		if(b != d)
		{
			str.append(d);
		}
		else
		{				
			xq_bs.push_back(str);	
			if(str.size() == 12)				//完整的宝石id为12字节长度
			{
				int type = str[11]-'0';
				if(type < 10 && type >= 0)
					bs_xq_num[type] += 1;
			}
			str = "";
		}
		d="";
	}	

	map_now = NULL;
	
	countAttribute();
}

void Equipment::initEquip(Equip_config *equip_pt)
{
	equipmentdata->durability = equip_pt->getdurability();   //耐久度
	equipmentdata->durabilityLimit = equipmentdata->durability;   //耐久度
	equipmentdata->price=equip_pt->getMoney();        //价格
	equipmentdata->gold=equip_pt->getgold();
	equipmentdata->goldBound=equip_pt->getgoldBound();
	equipmentdata->priceBound=equip_pt->getMoneyBound();
	equipmentdata->sellPrice=equip_pt->getPrice(); 
	equipmentdata->move=equip_pt->getMove();
	equipmentdata->isbag = 0;		//装备是否穿在身上 0，在背包内；1
	equipmentdata->isWear=0;
	equipmentdata->time=equip_pt->getTime();				//持续时间
	equipmentdata->beginTime=0;								//开始时间
	if (strncmp(equipmentdata->id,"f",1))
	{
		equipmentdata->bound=1;
	}
	else
	{
		equipmentdata->bound=0;
	}
	map_now = NULL;
	
	equipmentdata->equipmentRongLian.life=0;         //生命值
	equipmentdata->equipmentRongLian.magic=0;      //真气
	equipmentdata->equipmentRongLian.inattack=0;     //内功攻击
	equipmentdata->equipmentRongLian.outattack=0;    //外功攻击
	equipmentdata->equipmentRongLian.indefence=0;    //内功防御
	equipmentdata->equipmentRongLian.outdefence=0;   //外功防御
	equipmentdata->equipmentRongLian.rongLianLevel=0;   
	equipmentdata->equipmentRongLian.rongLianLucky=0;      
	
	equipmentdata->equipmentKaiRen.crit=0;         //暴击
	equipmentdata->equipmentKaiRen.hit=0; 		 //命中
	equipmentdata->equipmentKaiRen.dodge=0;        //闪避
	equipmentdata->equipmentKaiRen.tenacity=0; 	 //韧性
	equipmentdata->equipmentKaiRen.kaiRenLevel=0; 	 					
	
	equipmentdata->equpmentDiamon.life=0;         //生命值
	equipmentdata->equpmentDiamon.magic=0;      //真气
	equipmentdata->equpmentDiamon.inattack=0;     //内功攻击
	equipmentdata->equpmentDiamon.outattack=0;    //外功攻击
	equipmentdata->equpmentDiamon.indefence=0;    //内功防御
	equipmentdata->equpmentDiamon.outdefence=0;   //外功防御
	equipmentdata->equpmentDiamon.crit=0;         //暴击
	equipmentdata->equpmentDiamon.hit=0; 		 //命中
	equipmentdata->equpmentDiamon.dodge=0;        //闪避
	equipmentdata->equpmentDiamon.tenacity=0; 	 //韧性
	
	int i = 0;
	for(i; i<10; i++)
	{
		bs_xq_num[i] = 0;
	}
	

	xq_bs.clear();
	{
		std::vector<string> tmp;
		xq_bs.swap(tmp);
	}
}

Equipment::~Equipment(void)
{
	if(equipmentdata != NULL)
	{
		delete equipmentdata;
		equipmentdata = NULL;
	}
	
	ev_timer_stop(loops,&timer);	
		
	map_now = NULL;	
}

int Equipment::getMove(void)
{
	return equipmentdata->move;
}
		
int Equipment::getRongLianCost(void)
{
	return equipmentdata->equipmentRongLian.rongLianCost*equipmentdata->attrNumber;
}

int Equipment::getKaiRenCost(void)
{
	return (equipmentdata->equipmentKaiRen.kaiRenCost+equipmentdata->attrNumber*100)*(equipmentdata->equipmentKaiRen.kaiRenLevel+1);
}
	
char* Equipment::getentityid(void)		//实体类id
{
	return equipmentdata->entityid;
}	
	
char* Equipment::getid(void)           //装备ID
{
	return equipmentdata->id;
}

char* Equipment::getname(void)		 //装备名称
{
	return equipmentdata->name;
}

int    Equipment::getgrade(void)        //装备等级
{
	return equipmentdata->grade;
}

int    Equipment::getrank(void)         //装备级别，5橙，3紫
{
	return equipmentdata->rank;
}

int Equipment::getFourDiamonNumber(void)
{
	return equipmentdata->fourDiamonNumber;
}

int Equipment::xianQiangFourDiamon(void)
{
	equipmentdata->fourDiamonNumber++;
}

int Equipment::zhaiQuFourDiamon(void)
{
	equipmentdata->fourDiamonNumber--;
	if (equipmentdata->fourDiamonNumber<0)
	{
		equipmentdata->fourDiamonNumber=0;
	}
}

int    Equipment::gettype(void)         //装备类型
{
	return equipmentdata->type;
}

char*  Equipment::getparty(void)        //装备门派
{
	return equipmentdata->party;
}

int    Equipment::getsuit_type(void)    //套装类别
{
	return equipmentdata->suit_type;
}

char* Equipment::getsuit_id(void)      //套装ID
{
	return equipmentdata->suit_id;
}

int    Equipment::getlife(void)         //生命值
{		
	return lifeTotal;
}

int    Equipment::getinattack(void)     //内功攻击
{
	return inAttackTotal;
}

int    Equipment::getoutattack(void)    //外功攻击
{
	return outAttackTotal;
}

int    Equipment::getindefence(void)    //内功防御
{
	return inDefenceTotal;
}

int    Equipment::getoutdefence(void)   //外功防御
{
	return outDefenceTotal;
}

int    Equipment::getMagic(void)      //真气
{
	return magicTotal;
}

int    Equipment::getcrit(void)         //暴击
{
	return critTotal;
}

int    Equipment::gethit(void) 		 //命中
{
	return hitTotal;
}
	
int    Equipment::getdodge(void)        //闪避
{
	return dodgeTotal;
}

int    Equipment::gettenacity(void) 	 //韧性
{
	return tenacityTotal;
}

int	   Equipment::getdurability(void)   //耐久度
{
	return equipmentdata->durability; 
}

int	   Equipment::getprice(void)        //价格
{
	return equipmentdata->price;
}

int	   Equipment::getbound(void)			//绑定状态 jolly added
{
	return equipmentdata->bound;
}

void Equipment::setBound(int bound)
{
	equipmentdata->bound=bound;
}

int Equipment::getgold(void)
{
	return equipmentdata->gold;
}

int	   Equipment::getKaiRenLevel(void)	 //装备淬砺等级
{
	return equipmentdata->equipmentKaiRen.kaiRenLevel;
}
		
int    Equipment::getRongLianLevel(void)	 //装备精练等级
{
	return equipmentdata->equipmentRongLian.rongLianLevel;
}
		
int    Equipment::getRongLianLucky(void)	 //装备精练幸运值
{
	return equipmentdata->equipmentRongLian.rongLianLucky;
}
		
int    Equipment::getHoleNumber(void)		 //装备打孔的数目
{
	return equipmentdata->holeNumber;
}

int Equipment::getDiamonLife(void)
{
	return 	equipmentdata->equpmentDiamon.life;
}

void Equipment::setDiamonLife(int _diamonLife)
{
	equipmentdata->equpmentDiamon.life=_diamonLife;
}

int Equipment::getDiamonMagic(void)
{
	return 	equipmentdata->equpmentDiamon.magic;
}

void Equipment::setDiamonMagic(int _diamonMagic)
{
	equipmentdata->equpmentDiamon.magic=_diamonMagic;
}

int Equipment::getDiamonInattack(void)
{
	return 	equipmentdata->equpmentDiamon.inattack;
}

void Equipment::setDiamonInattack(int _diamonInattack)
{
	equipmentdata->equpmentDiamon.inattack=_diamonInattack;
}

int Equipment::getDiamonOutattack(void)
{
	return equipmentdata->equpmentDiamon.outattack;
}

void Equipment::setDiamonOutattack(int _diamonOutattack)
{
	equipmentdata->equpmentDiamon.outattack=_diamonOutattack;
}

int Equipment::getDiamonIndefence(void)
{
	return equipmentdata->equpmentDiamon.indefence;
}

void Equipment::setDiamonIndefence(int _diamonIndefence)
{
	equipmentdata->equpmentDiamon.indefence=_diamonIndefence;
}

int Equipment::getDiamonOutdefence(void)
{
	return equipmentdata->equpmentDiamon.outdefence;
}
void Equipment::setDiamonOutdefence(int _diamonOutdefence)
{
	equipmentdata->equpmentDiamon.outdefence=_diamonOutdefence;
}

int Equipment::getDiamonCrit(void)
{
	return equipmentdata->equpmentDiamon.crit;
}

void Equipment::setDiamonCrit(int _diamonCrit)
{
	equipmentdata->equpmentDiamon.crit=_diamonCrit;
}

int Equipment::getDiamonHit(void)
{
	return equipmentdata->equpmentDiamon.hit;
}

void Equipment::setDiamonHit(int _diamonHit)
{
	equipmentdata->equpmentDiamon.hit=_diamonHit;
}

int Equipment::getDiamonDodge(void)
{
	return equipmentdata->equpmentDiamon.dodge;
}

void Equipment::setDiamonDodge(int _diamonDodge)
{
	equipmentdata->equpmentDiamon.dodge=_diamonDodge;
}

int Equipment::getDiamonTenacity(void)
{
	return equipmentdata->equpmentDiamon.tenacity;
}

void Equipment::setDiamonTenacity(int _diamonTenacity)
{
	equipmentdata->equpmentDiamon.tenacity=_diamonTenacity;
}
		
vector<string> Equipment::getxq_bs(void)	 //装备上镶嵌的宝石的集合
{
	return xq_bs;
}
void   Equipment::setxq_bs(vector<string> _xq_bs)
{
	xq_bs = _xq_bs;
}

int Equipment::getBaseLife(void)
{
	return equipmentdata->equipmentBase.life;
}

int Equipment::getBaseMagic(void)
{
	return equipmentdata->equipmentBase.magic;
}

int Equipment::getBaseOutAttack(void)
{
	return equipmentdata->equipmentBase.outattack;
}

int Equipment::getBaseInAttack(void)
{
	return equipmentdata->equipmentBase.inattack;
}

int Equipment::getBaseOutDefense(void)
{
	return equipmentdata->equipmentBase.outdefence;
}

int Equipment::getBaseInDefense(void)
{
	return equipmentdata->equipmentBase.indefence;
}

int Equipment::getBaseHit(void)
{
	return equipmentdata->equipmentBase.hit;
}

int Equipment::getBaseCrit(void)
{
	return equipmentdata->equipmentBase.crit;
}

int Equipment::getBaseDodge(void)
{
	return equipmentdata->equipmentBase.dodge;
}

int Equipment::getBaseTenacity(void)
{
	return equipmentdata->equipmentBase.tenacity;
}

void Equipment::saveInStruct(void)
{
	vector<string>::iterator it;
	string test="";
	if (xq_bs.empty())
	{
		strncpy(equipmentdata->xq_bs,"0",sizeof(equipmentdata->xq_bs));
	}
	else
	{
		for (it=xq_bs.begin();it!=xq_bs.end();++it)
		{
			if (!(*it).empty())
			{
				test=test+*it+";";
			}
		}
		strncpy(equipmentdata->xq_bs,test.c_str(),sizeof(equipmentdata->xq_bs));	
	}
	
	// showEquipmentData(equipmentdata,"equipmentdata.txt");
}

void Equipment::msg_return_equipInform(char* msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",9,5,equipmentdata->entityid,equipmentdata->suit_id,equipmentdata->isbag,equipmentdata->durability/400, equipmentdata->equipmentRongLian.rongLianLevel, equipmentdata->equipmentKaiRen.kaiRenLevel, outAttackTotal,inAttackTotal,outDefenceTotal,inDefenceTotal,lifeTotal,magicTotal,hitTotal,critTotal,dodgeTotal,tenacityTotal,equipmentdata->sellPrice,equipmentdata->isWear);
	//0-19
	if (equipmentdata->type==0||equipmentdata->type==13)			//20
	{
		if (equipmentdata->time==-1)
		{
			snprintf(msg+strlen(msg),len-strlen(msg),",%d",-1);
		}
		else
		{
			if (equipmentdata->beginTime==0)
			{
				snprintf(msg+strlen(msg),len-strlen(msg),",%d",equipmentdata->time);
			}
			else
			{
				snprintf(msg+strlen(msg),len-strlen(msg),",%d",remainTime());
			}
		}		
	}
	else
	{
		snprintf(msg+strlen(msg),len-strlen(msg),",%d",0);
	}
		
	vector<string> ::iterator it;
	int num = xq_bs.size();
	sprintf(msg+strlen(msg), ",%d", num);//21
	for(it=xq_bs.begin();it!=xq_bs.end();it++)
	{
		char diamond_id[40] = {0};
		strncpy(diamond_id,(*it).c_str(),sizeof(diamond_id));
		sprintf(msg+strlen(msg),",%s,%d",diamond_id, goodsReturnInt(diamond_id,0));
	}

	snprintf(msg+strlen(msg),len-strlen(msg),",%s,%d",equipmentdata->id,equipmentdata->isbag);
}

int    Equipment::getIsBag(void)		//装备是否穿在身上 0，在背包内；1，在身上 evan add 2012.8.31
{
	return equipmentdata->isbag;
}
void   Equipment::setisbag(int _isbag)
{
	equipmentdata->isbag = _isbag;
	equipmentdata->isWear=1;
}
//tory 2012.12.14 Didn't do anything
int  Equipment::repairCost(void)
{
	int per=((equipmentdata->durabilityLimit-equipmentdata->durability)*100)/equipmentdata->durabilityLimit;
	int price=per*equipmentdata->sellPrice;
	return price;
}
//装备修理 by cookie
void Equipment::repair(void)
{
	equipmentdata->durability = equipmentdata->durabilityLimit;
}

EquipmentData* Equipment::getEquipmentData(void)
{
	return equipmentdata;
}

void Equipment::wareEquipSetBound(void)			//穿装备时,将未绑定装备变为绑定装备
{
	if(strlen(equipmentdata->id) == 0)
	{
		cout<<"jolly:id is error equipment 502"<<endl;
		return;
	}
	if (strncmp(equipmentdata->id,"f",1)==0)
	{			
		equipmentdata->id[0]= 'b';	
		setBound(1);
	}

}

int Equipment::getsellprice(void)
{
	return equipmentdata->sellPrice;
}

char* Equipment::getPhotoId(void)
{
	return equipmentdata->photoId;
}

/*生成物品掉落信息*/
void Equipment::formDropMsg(Hero *killHero,char *identity)
{
	if(killHero == NULL || identity == NULL)
	{
		return;
	}
	map_now = killHero->getMap();
	piexPt = killHero->getLocation();
	memset(dropMsg,'\0',sizeof(dropMsg));
	snprintf(dropMsg,sizeof(dropMsg),"%d,%d,%s,%d,%s,%d,%d,%s",9,0,identity,0,equipmentdata->entityid,piexPt._x,piexPt._y,equipmentdata->id);
}

/*获得物品掉落信息*/
char* Equipment::getDropMsg(void)
{
	return dropMsg;
}

/*生成物品掉落信息*/
void Equipment::formDropDisMsg(void)
{
	memset(dropDisMsg,'\0',sizeof(dropDisMsg));
	snprintf(dropDisMsg,sizeof(dropDisMsg),"%d,%d,%d,%s,%d,%d",9,1,1,equipmentdata->entityid,piexPt._x,piexPt._y);	
}

/*获得物品掉落信息*/
char* Equipment::getDropDisMsg(void)
{
	return dropDisMsg;
}

/*启动掉落装备计时器*/
void Equipment::initTime(void)
{
	ext_ev_timer_init(&timer,dropEquipCalBak,DROP_GOODS_DISPERAR_TIME,12,this);
	ev_timer_start(loops,&timer);
}

/*装备地图消亡*/
void Equipment::disperMsg(void)
{
	StyObj obj(equipmentdata->entityid,DROP_EQUIP_STYLE_TYPE);	
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
	
	formDropDisMsg();  
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(dropDisMsg);
	
	map_now->deleteID(obj);	
	
	ev_timer_stop(loops,&timer);
}

/*装备掉落以及消息发送*/
void Equipment::bronMsg(Hero *killHero,char *identity)
{

	StyObj obj(equipmentdata->entityid,DROP_EQUIP_STYLE_TYPE);
	Nbox *box;	
	
	formDropMsg(killHero,identity);  
	
	box = map_now->getBox();
	
	if(box == NULL)
	{
		return;
	}
	
	cout<<"dropMsg:"<<dropMsg<<endl;
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(dropMsg);
}

/*获得掉落装备的位置*/
Point Equipment::getPiexPt(void)
{
	return piexPt;
}

//按宝石类型增加镶嵌的宝石数目
void Equipment::addBsNumByTy(char* goodsid)
{
	if(strlen(goodsid) != 12)
	{
		cout<<"goodid error in equipment.cpp 825"<<endl;
		return;
	}
	int effect_type = *(goodsid+11)-'0';		//effect_type宝石作用类型
	cout<<"effect_type:"<<effect_type<<endl;
	if(effect_type >= 0 && effect_type < 10)
	{
		bs_xq_num[effect_type] += 1;	
	}	
}		

void Equipment::diamonAttribute(Hero *hero,char* goodsid)
{
	if (hero==NULL)
	{
		return;
	}
	
	int type = *(goodsid+11)-'0';		//effect_type宝石作用类型
	int effect = goodsReturnInt(goodsid, 0);  //宝石增加或减少的装备属性的数值	jolly 修改 9-4
	if (type==0)
	{
		setDiamonOutattack(effect);
		hero->setOutAttack(hero->memHero->basicHeroData.outattack+getDiamonOutattack());
	}
	else if (type==1)
	{
		setDiamonInattack(effect);
		hero->setInAttack(hero->memHero->basicHeroData.inattack+getDiamonInattack());
	}
	else if (type==2)
	{
		setDiamonOutdefence(effect);
		hero->setOutDefense(hero->memHero->basicHeroData.outdefense+getDiamonOutdefence());
	}
	else if (type==3)
	{
		setDiamonIndefence(effect);
		hero->setInDefense(hero->memHero->basicHeroData.indefense+getDiamonIndefence());
	}
	else if (type==4)
	{
		setDiamonCrit(effect);
		hero->setCrit(hero->memHero->basicHeroData.crit+getDiamonCrit());
	}
	else if (type==5)
	{
		setDiamonHit(effect);
		hero->setHited(hero->memHero->basicHeroData.hited+getDiamonHit());
		cout<<"equipmentdata->equpmentDiamon.hit:"<<equipmentdata->equpmentDiamon.hit<<endl;
	}
	else if (type==6)
	{
		setDiamonDodge(effect);
		hero->setDodge(hero->memHero->basicHeroData.dodge+getDiamonDodge());
	}
	else if (type==7)
	{
		setDiamonLife(effect);
		hero->setLifeUpperVal(hero->memHero->basicHeroData.lifeUpperVal+getDiamonLife());
	}
	else if (type==8)
	{
		setDiamonMagic(effect);
		hero->setMagicUpperVal(hero->memHero->basicHeroData.magicUpperVal+getDiamonMagic());
	}
	else if (type==9)
	{
		setDiamonTenacity(effect);
		hero->setTenacity(hero->memHero->basicHeroData.tenacity+getDiamonTenacity());
	}
	countAttribute();
}

void Equipment::diamonOff(Hero *hero,int index)
{
	if (hero==NULL)
	{
		return;
	}
	
	// cout<<"---------------xq_bs before begin---------------------"<<endl;
	// for (int i=0;i<xq_bs.size();i++)
	// {
		// cout<<"xq_bs["<<i<<"]:"<<xq_bs[i]<<endl;
	// }
	// cout<<"---------------xq_bs before end---------------------"<<endl;

	if (index<0||index>=equipmentdata->holeNumber)
	{
		return;
	}
	string goodsid=xq_bs[index];
	for (int i=index;i<xq_bs.size()-1;i++)
	{
		xq_bs[i]=xq_bs[i+1];
	}
	xq_bs.pop_back();
	
	string type = goodsid.substr(11,1);	
	cout<<"type:"<<type<<endl;
	// cout<<"---------------xq_bs after begin---------------------"<<endl;
	// for (int i=0;i<xq_bs.size();i++)
	// {
		// cout<<"xq_bs["<<i<<"]:"<<xq_bs[i]<<endl;
	// }
	// cout<<"---------------xq_bs after end---------------------"<<endl;
			
	if (type=="0")
	{
		hero->setOutAttack(hero->memHero->basicHeroData.outattack-getDiamonOutattack());
		setDiamonOutattack(0);
	}
	else if (type=="1")
	{
		hero->setInAttack(hero->memHero->basicHeroData.inattack-getDiamonInattack());
		setDiamonInattack(0);
	}
	else if (type=="2")
	{
		hero->setOutDefense(hero->memHero->basicHeroData.outdefense-getDiamonOutdefence());
		setDiamonOutdefence(0);
	}
	else if (type=="3")
	{
		hero->setInDefense(hero->memHero->basicHeroData.indefense-getDiamonIndefence());
		setDiamonIndefence(0);
	}
	else if (type=="4")
	{
		hero->setCrit(hero->memHero->basicHeroData.crit-getDiamonCrit());
		setDiamonCrit(0);
	}
	else if (type=="5")
	{
		cout<<"equipmentdata->equpmentDiamon.hit:"<<equipmentdata->equpmentDiamon.hit<<endl;
		hero->setHited(hero->memHero->basicHeroData.hited-getDiamonHit());
		setDiamonHit(0);
	}
	else if (type=="6")
	{
		hero->setDodge(hero->memHero->basicHeroData.dodge-getDiamonDodge());
		setDiamonDodge(0);
	}
	else if (type=="7")
	{
		hero->setLifeUpperVal(hero->memHero->basicHeroData.lifeUpperVal-getDiamonLife());
		setDiamonLife(0);
	}
	else if (type=="8")
	{
		hero->setMagicUpperVal(hero->memHero->basicHeroData.magicUpperVal-getDiamonMagic());
		setDiamonMagic(0);
	}
	else if (type=="9")
	{
		hero->setTenacity(hero->memHero->basicHeroData.tenacity-getDiamonTenacity());
		setDiamonTenacity(0);
	}
	
	countAttribute();
	cout<<"end diamonOff equipment.cpp 905"<<endl;
}
		
//按宝石类型减少镶嵌的宝石数目
void Equipment::delBsNumByTy(char* goodsid)
{
	if(strlen(goodsid) != 12)
	{
		cout<<"goodsid isn't right equipment.cpp 981"<<endl;
		return;
	}
	int effect_type = *(goodsid+11)-'0';		//effect_type宝石作用类型
	
	if(effect_type >= 0 && effect_type < 10)
	{
		if(bs_xq_num[effect_type] > 0)
		{
			cout<<"@@Tory before delBsNumByTy:"<<bs_xq_num[effect_type]<<endl;
			bs_xq_num[effect_type] -= 1;
			cout<<"@@Tory after delBsNumByTy:"<<bs_xq_num[effect_type]<<endl;		
		}
	}
	else
	{
		cout<<"effect_type error in equipment 996   effect_type:"<<effect_type<<endl;
	}
}
	
//按宝石类型获取镶嵌的宝石数目，数据传入错误，返回-1
int Equipment::getBsNumByTy(char* goodsid)
{
	if(strlen(goodsid) != 12)
	{
		cout<<"goodsid error in equipment.cpp 1002"<<endl;
		return 0;
	}
	int effect_type = *(goodsid+11)-'0';		//effect_type宝石作用类型
	cout<<"effect_type:"<<effect_type<<endl;
	if(effect_type < 0 || effect_type > 9)
	{
		cout<<"effect_type error in equipment 1013"<<endl;
		return 0;
	}
	else
	{
		return bs_xq_num[effect_type];
	}
}

bool Equipment::testDiamon(int index,char *goodsid)
{
	if (index<0||index>equipmentdata->holeNumber)
	{
		cout<<"Diamon index error index:"<<index<<endl;
		return false;
	}
	else
	{
		if (strcmp(xq_bs[index].c_str(),goodsid)==0)
		{
			return true;
		}
		else
		{
			cout<<"xq_bs[index]:"<<xq_bs[index]<<"         goodsid:"<<goodsid<<endl;
			return false;
		}
	}
}

//穿上时装,开启时间倒计时
void Equipment::beginTime(void)
{
	if (equipmentdata->beginTime==0)
	{
		equipmentdata->isWear=1;
		// cout<<"开始了!"<<endl;
		equipmentdata->beginTime=myTime.tv_sec;								//开始时间
		// cout<<"beginTime:"<<equipmentdata->beginTime<<endl;
		// cout<<"myTime.tv_sec:"<<myTime.tv_sec<<endl;
	}	
}

//判断时装是否有效
bool Equipment::isEffect(Hero *hero)
{
	cout<<"myTime.tv_sec-equipmentdata->beginTime::"<<myTime.tv_sec-equipmentdata->beginTime<<endl;
	cout<<"myTime.tv_sec:"<<myTime.tv_sec<<endl;
	cout<<"equipmentdata->beginTime:"<<equipmentdata->beginTime<<endl;
	
	if (equipmentdata->beginTime>0)
	{
		if (equipmentdata->time==-1)
		{
			return true;
		}
		else if ((myTime.tv_sec-equipmentdata->beginTime)>equipmentdata->time)
		{		
			cout<<"equipmentdata->time:"<<equipmentdata->time<<endl;
			fasionDestory(hero,equipmentdata->type,equipmentdata->entityid);
			return false;
		}
		else if (equipmentdata->time-myTime.tv_sec+equipmentdata->beginTime<=3600&&equipmentdata->time-myTime.tv_sec+equipmentdata->beginTime>3595)
		{
			memset(g_out_buf,0,sizeof(g_out_buf));
			msg_return_equipInform(g_out_buf,sizeof(g_out_buf));
			send_msg(hero->getFd(),g_out_buf);
			return true;
		}
		else
		{
			return true;
		}
	}
	else if (equipmentdata->beginTime<0)
	{
		equipmentdata->beginTime=myTime.tv_sec;
	}
	else
	{
		return true;
	}
}

//返回时装还有多少时间
int Equipment::remainTime(void)
{
	return (equipmentdata->time-(myTime.tv_sec-equipmentdata->beginTime));
}

//解绑减属性
void Equipment::unboundDecreaseAttr(Hero *hero,Equip_config *equip_config)
{
	if (hero==NULL)
	{
		return;
	}
	
	if (equip_config==NULL)
	{
		return;
	}
	
	equipmentdata->isbag = 0;		//装备是否穿在身上 0，在背包内；1，在身上	
	equipmentdata->id[0]='f';
		
	equipmentdata->equipmentRongLian.life=0;         //生命值
	equipmentdata->equipmentRongLian.magic=0;      //真气
	equipmentdata->equipmentRongLian.inattack=0;     //内功攻击
	equipmentdata->equipmentRongLian.outattack=0;    //外功攻击
	equipmentdata->equipmentRongLian.indefence=0;    //内功防御
	equipmentdata->equipmentRongLian.outdefence=0;   //外功防御
	
	equipmentdata->equipmentKaiRen.crit=0;         //暴击
	equipmentdata->equipmentKaiRen.hit=0; 		 //命中
	equipmentdata->equipmentKaiRen.dodge=0;        //闪避
	equipmentdata->equipmentKaiRen.tenacity=0; 	 //韧性
	
	int finalKaiRen=equipmentdata->equipmentKaiRen.kaiRenLevel/2;
	equipmentdata->equipmentKaiRen.kaiRenLevel=0;	
	for (int i=1;i<=finalKaiRen;i++)
	{
		kaiRenAttributeIncrease(hero,i);
	}

	int finalRongLian=equipmentdata->equipmentRongLian.rongLianLevel/2;
	for (int j=1;j<=finalRongLian;j++)
	{
		rongLianAttributeIncrease(hero,j);
	}
	
	equipmentdata->equipmentRongLian.rongLianLucky = 0;	 //装备精练幸运值
}

//熔炼增加属性
void Equipment::rongLianAttributeIncrease(Hero *hero,int level)
{
	if (hero==NULL)
	{
		return;
	}
	
	if (level>50)
	{
		return;
	}
	
	if (level<=equipmentdata->equipmentRongLian.rongLianLevel||level<1||level!=(equipmentdata->equipmentRongLian.rongLianLevel+1))
	{
		return;
	}
	
	float increasePer=(float)equip_operator[level].rongLianAdd/1000.0;
	
	int lifeIncrease=0;
	int magicIncrease=0;
	int outAttackIncrease=0;
	int inAttackIncrease=0;
	int outDefenseIncrease=0;
	int inDefenseIncrease=0;
	
	if (equipmentdata->equipmentBase.life!=0)
	{		
		lifeIncrease=equipmentdata->equipmentBase.life*increasePer;
		if (lifeIncrease<=equipmentdata->equipmentRongLian.life)
		{
			lifeIncrease=1;
		}
		else
		{
			lifeIncrease-=equipmentdata->equipmentRongLian.life;
		}
		equipmentdata->equipmentRongLian.life+=lifeIncrease;
	}
	
	if (equipmentdata->equipmentBase.magic!=0)
	{
		magicIncrease=equipmentdata->equipmentBase.magic*increasePer;
		if (magicIncrease<=equipmentdata->equipmentRongLian.magic)
		{
			magicIncrease=1;
		}
		else
		{
			magicIncrease-=equipmentdata->equipmentRongLian.magic;
		}
		equipmentdata->equipmentRongLian.magic+=magicIncrease;
	}
	if (equipmentdata->equipmentBase.outattack!=0)
	{
		outAttackIncrease=equipmentdata->equipmentBase.outattack*increasePer;
		if (outAttackIncrease<=equipmentdata->equipmentRongLian.outattack)
		{
			outAttackIncrease=1;
		}
		else
		{
			outAttackIncrease-=equipmentdata->equipmentRongLian.outattack;
		}
		equipmentdata->equipmentRongLian.outattack+=outAttackIncrease;
	}
	if (equipmentdata->equipmentBase.inattack!=0)
	{
		inAttackIncrease=equipmentdata->equipmentBase.inattack*increasePer;
		if (inAttackIncrease<=equipmentdata->equipmentRongLian.inattack)
		{
			inAttackIncrease=1;
		}
		else
		{
			inAttackIncrease-=equipmentdata->equipmentRongLian.inattack;
		}
		equipmentdata->equipmentRongLian.inattack+=inAttackIncrease;
	}
	if (equipmentdata->equipmentBase.outdefence!=0)
	{
		outDefenseIncrease=equipmentdata->equipmentBase.outdefence*increasePer;
		if (outDefenseIncrease<=equipmentdata->equipmentRongLian.outdefence)
		{
			outDefenseIncrease=1;
		}
		else
		{
			outDefenseIncrease-=equipmentdata->equipmentRongLian.outdefence;
		}
		equipmentdata->equipmentRongLian.outdefence+=outDefenseIncrease;
	}
	if (equipmentdata->equipmentBase.indefence!=0)
	{
		inDefenseIncrease=equipmentdata->equipmentBase.indefence*increasePer;
		if (inDefenseIncrease<=equipmentdata->equipmentRongLian.indefence)
		{
			inDefenseIncrease=1;
		}
		else
		{
			inDefenseIncrease-=equipmentdata->equipmentRongLian.indefence;
		}
		equipmentdata->equipmentRongLian.indefence+=inDefenseIncrease;
	}
	
	if (getIsBag()==1)
	{
		hero->setLifeUpperVal(hero->memHero->basicHeroData.lifeUpperVal+lifeIncrease);
		hero->setMagicUpperVal(hero->memHero->basicHeroData.magicUpperVal+magicIncrease);
		hero->setInAttack(hero->memHero->basicHeroData.inattack+inAttackIncrease);
		hero->setOutAttack(hero->memHero->basicHeroData.outattack+outAttackIncrease);
		hero->setInDefense(hero->memHero->basicHeroData.indefense+inDefenseIncrease);
		hero->setOutDefense(hero->memHero->basicHeroData.outdefense+outDefenseIncrease);
	}

	equipmentdata->equipmentRongLian.rongLianLevel=level;
	equipmentdata->equipmentRongLian.rongLianLucky=0;
	
	countAttribute();
}

//熔炼预览消息发送
void Equipment::msg_rongLian(char *msg,int len,int vipSuccess)
{
	if (msg==NULL)
	{
		return;
	}
	
	if (equipmentdata->equipmentRongLian.rongLianLevel>=50)
	{
		snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",8,7,1,50,vipSuccess,0,vipSuccess,getRongLianCost(),getlife(),getMagic(),getoutattack(),getinattack(),getoutdefence(),getindefence());
	}
	else
	{
		float increasePer=(float)equip_operator[equipmentdata->equipmentRongLian.rongLianLevel+1].rongLianAdd/1000.0;
	
		int lifeIncrease=0;
		int magicIncrease=0;
		int outAttackIncrease=0;
		int inAttackIncrease=0;
		int outDefenseIncrease=0;
		int inDefenseIncrease=0;
		
		if (equipmentdata->equipmentBase.life!=0)
		{		
			lifeIncrease=equipmentdata->equipmentBase.life*increasePer;
			if (lifeIncrease<=equipmentdata->equipmentRongLian.life)
			{
				lifeIncrease=1;
			}
			else
			{
				lifeIncrease-=equipmentdata->equipmentRongLian.life;
			}
		}
		
		if (equipmentdata->equipmentBase.magic!=0)
		{
			magicIncrease=equipmentdata->equipmentBase.magic*increasePer;
			if (magicIncrease<=equipmentdata->equipmentRongLian.magic)
			{
				magicIncrease=1;
			}
			else
			{
				magicIncrease-=equipmentdata->equipmentRongLian.magic;
			}
		}
		if (equipmentdata->equipmentBase.outattack!=0)
		{
			outAttackIncrease=equipmentdata->equipmentBase.outattack*increasePer;
			if (outAttackIncrease<=equipmentdata->equipmentRongLian.outattack)
			{
				outAttackIncrease=1;
			}
			else
			{
				outAttackIncrease-=equipmentdata->equipmentRongLian.outattack;
			}
		}
		if (equipmentdata->equipmentBase.inattack!=0)
		{
			inAttackIncrease=equipmentdata->equipmentBase.inattack*increasePer;
			if (inAttackIncrease<=equipmentdata->equipmentRongLian.inattack)
			{
				inAttackIncrease=1;
			}
			else
			{
				inAttackIncrease-=equipmentdata->equipmentRongLian.inattack;
			}
		}
		if (equipmentdata->equipmentBase.outdefence!=0)
		{
			outDefenseIncrease=equipmentdata->equipmentBase.outdefence*increasePer;
			if (outDefenseIncrease<=equipmentdata->equipmentRongLian.outdefence)
			{
				outDefenseIncrease=1;
			}
			else
			{
				outDefenseIncrease-=equipmentdata->equipmentRongLian.outdefence;
			}
		}
		if (equipmentdata->equipmentBase.indefence!=0)
		{
			inDefenseIncrease=equipmentdata->equipmentBase.indefence*increasePer;
			if (inDefenseIncrease<=equipmentdata->equipmentRongLian.indefence)
			{
				inDefenseIncrease=1;
			}
			else
			{
				inDefenseIncrease-=equipmentdata->equipmentRongLian.indefence;
			}
		}
		cout<<"equip_operator[equipmentdata->rongLianLevel].rongLianPer:"<<equip_operator[equipmentdata->equipmentRongLian.rongLianLevel].rongLianPer<<endl;
		cout<<"getRongLianLucky():"<<getRongLianLucky()<<endl;
		cout<<"vipSuccess:"<<vipSuccess<<endl;
		snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",8,7,1,equipmentdata->equipmentRongLian.rongLianLevel,equip_operator[equipmentdata->equipmentRongLian.rongLianLevel].rongLianPer+getRongLianLucky()+vipSuccess*10,getRongLianLucky(),vipSuccess,getRongLianCost(),getlife()+lifeIncrease,getMagic()+magicIncrease,getoutattack()+outAttackIncrease,getinattack()+inAttackIncrease,getoutdefence()+outDefenseIncrease,getindefence()+inDefenseIncrease);
	}	
}

void Equipment::initRongLian(Hero *hero)
{	
	if (getIsBag()==1)
	{
		hero->setLifeUpperVal(hero->memHero->basicHeroData.lifeUpperVal-equipmentdata->equipmentRongLian.life);
		hero->setMagicUpperVal(hero->memHero->basicHeroData.magicUpperVal-equipmentdata->equipmentRongLian.magic);
		hero->setInAttack(hero->memHero->basicHeroData.inattack-equipmentdata->equipmentRongLian.outattack);
		hero->setOutAttack(hero->memHero->basicHeroData.outattack-equipmentdata->equipmentRongLian.inattack);
		hero->setInDefense(hero->memHero->basicHeroData.indefense-equipmentdata->equipmentRongLian.outdefence);
		hero->setOutDefense(hero->memHero->basicHeroData.outdefense-equipmentdata->equipmentRongLian.indefence);
	}

	equipmentdata->equipmentRongLian.life=0;         //生命值
	equipmentdata->equipmentRongLian.magic=0;      //真气
	equipmentdata->equipmentRongLian.inattack=0;     //内功攻击
	equipmentdata->equipmentRongLian.outattack=0;    //外功攻击
	equipmentdata->equipmentRongLian.indefence=0;    //内功防御
	equipmentdata->equipmentRongLian.outdefence=0;   //外功防御
	equipmentdata->equipmentRongLian.rongLianLevel=0;   
	equipmentdata->equipmentRongLian.rongLianLucky=0;   
	
	countAttribute();
}

void Equipment::rongLianFailed(void)
{
	equipmentdata->equipmentRongLian.rongLianLucky+=3;
}

//开刃增加属性
void Equipment::kaiRenAttributeIncrease(Hero *hero,int level)
{
	if (hero==NULL)
	{
		return;
	}
	
	if (level>50)
	{
		return;
	}
	
	if (level<=equipmentdata->equipmentKaiRen.kaiRenLevel||level<1||level!=(equipmentdata->equipmentKaiRen.kaiRenLevel+1))
	{
		return;
	}
	
	float increasePer=(float)equip_operator[level].kaiRenAdd/1000.0;
	
	int hitIncrease=0;
	int critIncrease=0;
	int dodgeIncrease=0;
	int tenacityIncrease=0;
	
	if (equipmentdata->equipmentBase.hit!=0)
	{		
		hitIncrease=equipmentdata->equipmentBase.hit*increasePer;
		if (hitIncrease<=equipmentdata->equipmentKaiRen.hit)
		{
			hitIncrease=1;
		}
		else
		{
			hitIncrease-=equipmentdata->equipmentKaiRen.hit;
		}
		equipmentdata->equipmentKaiRen.hit+=hitIncrease;
	}
	
	if (equipmentdata->equipmentBase.crit!=0)
	{
		critIncrease=equipmentdata->equipmentBase.crit*increasePer;
		if (critIncrease<=equipmentdata->equipmentKaiRen.crit)
		{
			critIncrease=1;
		}
		else
		{
			critIncrease-=equipmentdata->equipmentKaiRen.crit;
		}
		equipmentdata->equipmentKaiRen.crit+=critIncrease;
	}
	if (equipmentdata->equipmentBase.dodge!=0)
	{
		dodgeIncrease=equipmentdata->equipmentBase.dodge*increasePer;
		if (dodgeIncrease<=equipmentdata->equipmentKaiRen.dodge)
		{
			dodgeIncrease=1;
		}
		else
		{
			dodgeIncrease-=equipmentdata->equipmentKaiRen.dodge;
		}
		equipmentdata->equipmentKaiRen.dodge+=dodgeIncrease;
	}
	if (equipmentdata->equipmentBase.tenacity!=0)
	{
		tenacityIncrease=equipmentdata->equipmentBase.tenacity*increasePer;
		if (tenacityIncrease<=equipmentdata->equipmentKaiRen.tenacity)
		{
			tenacityIncrease=1;
		}
		else
		{
			tenacityIncrease-=equipmentdata->equipmentKaiRen.tenacity;
		}
		equipmentdata->equipmentKaiRen.tenacity+=tenacityIncrease;
	}
	
	if (getIsBag()==1)
	{
		hero->setHited(hero->memHero->basicHeroData.hited+hitIncrease);
		hero->setCrit(hero->memHero->basicHeroData.crit+critIncrease);
		hero->setDodge(hero->memHero->basicHeroData.dodge+dodgeIncrease);
		hero->setTenacity(hero->memHero->basicHeroData.tenacity+tenacityIncrease);
	}
		
	equipmentdata->equipmentKaiRen.kaiRenLevel=level;

	countAttribute();
}

//开刃增加数值
void Equipment::msg_kaiRen(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	
	if (equip_operator[equipmentdata->equipmentKaiRen.kaiRenLevel+1].kaiRenAdd==-1)
	{
		snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d",8,7,0,equipmentdata->equipmentKaiRen.kaiRenLevel,getKaiRenCost(),0,0,0,0);
	}
	else
	{
		float increasePer=(float)equip_operator[equipmentdata->equipmentKaiRen.kaiRenLevel+1].kaiRenAdd/1000.0;
	
		int hitIncrease=0;
		int critIncrease=0;
		int dodgeIncrease=0;
		int tenacityIncrease=0;
		
		if (equipmentdata->equipmentBase.hit!=0)
		{		
			hitIncrease=equipmentdata->equipmentBase.hit*increasePer;
			if (hitIncrease<=equipmentdata->equipmentKaiRen.hit)
			{
				hitIncrease=1;
			}
			else
			{
				hitIncrease-=equipmentdata->equipmentKaiRen.hit;
			}
		}
		
		if (equipmentdata->equipmentBase.crit!=0)
		{
			critIncrease=equipmentdata->equipmentBase.crit*increasePer;
			if (critIncrease<=equipmentdata->equipmentKaiRen.crit)
			{
				critIncrease=1;
			}
			else
			{
				critIncrease-=equipmentdata->equipmentKaiRen.crit;
			}
		}
		if (equipmentdata->equipmentBase.dodge!=0)
		{
			dodgeIncrease=equipmentdata->equipmentBase.dodge*increasePer;
			if (dodgeIncrease<=equipmentdata->equipmentKaiRen.dodge)
			{
				dodgeIncrease=1;
			}
			else
			{
				dodgeIncrease-=equipmentdata->equipmentKaiRen.dodge;
			}
		}
		if (equipmentdata->equipmentBase.tenacity!=0)
		{
			tenacityIncrease=equipmentdata->equipmentBase.tenacity*increasePer;
			if (tenacityIncrease<=equipmentdata->equipmentKaiRen.tenacity)
			{
				tenacityIncrease=1;
			}
			else
			{
				tenacityIncrease-=equipmentdata->equipmentKaiRen.tenacity;
			}
		}	
		snprintf(msg,len,"%d,%d,%d,%d,%d,%d,%d,%d,%d",8,7,0,equipmentdata->equipmentKaiRen.kaiRenLevel,getKaiRenCost(),gethit()+hitIncrease,getcrit()+critIncrease,getdodge()+dodgeIncrease,gettenacity()+tenacityIncrease);
	}
}

void Equipment::initKaiRen(Hero *hero)
{
	if (hero==NULL)
	{
		return;
	}
	
	if (getIsBag()==1)
	{
		hero->setHited(hero->memHero->basicHeroData.hited-equipmentdata->equipmentKaiRen.hit);
		hero->setCrit(hero->memHero->basicHeroData.crit-equipmentdata->equipmentKaiRen.crit);
		hero->setDodge(hero->memHero->basicHeroData.dodge-equipmentdata->equipmentKaiRen.dodge);
		hero->setTenacity(hero->memHero->basicHeroData.tenacity-equipmentdata->equipmentKaiRen.tenacity);
	}
	
	equipmentdata->equipmentKaiRen.crit=0;         //暴击
	equipmentdata->equipmentKaiRen.hit=0; 		 //命中
	equipmentdata->equipmentKaiRen.dodge=0;        //闪避
	equipmentdata->equipmentKaiRen.tenacity=0; 	 //韧性
	equipmentdata->equipmentKaiRen.kaiRenLevel=0; 	 	
		
	
	countAttribute();	
}

void Equipment::countAttribute(void)
{
	lifeTotal=equipmentdata->equipmentBase.life+equipmentdata->equipmentRongLian.life+equipmentdata->equpmentDiamon.life;
	magicTotal=equipmentdata->equipmentBase.magic+equipmentdata->equipmentRongLian.magic+equipmentdata->equpmentDiamon.magic;     						
	inAttackTotal=equipmentdata->equipmentBase.inattack+equipmentdata->equipmentRongLian.inattack+equipmentdata->equpmentDiamon.inattack;
	outAttackTotal=equipmentdata->equipmentBase.outattack+equipmentdata->equipmentRongLian.outattack+equipmentdata->equpmentDiamon.outattack;
	inDefenceTotal=equipmentdata->equipmentBase.indefence+equipmentdata->equipmentRongLian.indefence+equipmentdata->equpmentDiamon.indefence;
	outDefenceTotal=equipmentdata->equipmentBase.outdefence+equipmentdata->equipmentRongLian.outdefence+equipmentdata->equpmentDiamon.outdefence;
	critTotal=equipmentdata->equipmentBase.crit+equipmentdata->equipmentKaiRen.crit+equipmentdata->equpmentDiamon.crit;
	hitTotal=equipmentdata->equipmentBase.hit+equipmentdata->equipmentKaiRen.hit+equipmentdata->equpmentDiamon.hit;
	dodgeTotal=equipmentdata->equipmentBase.dodge+equipmentdata->equipmentKaiRen.dodge+equipmentdata->equpmentDiamon.dodge;
	tenacityTotal=equipmentdata->equipmentBase.tenacity+equipmentdata->equipmentKaiRen.tenacity+equipmentdata->equpmentDiamon.tenacity;
}
