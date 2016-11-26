#include"equip_config.h"
#include <string.h>

Equip_config::Equip_config(char* _id,char* _name,int _grade,int _order,int _rank,int _type,char* _party,int _suit_type,char* _suit_id,
						int _life,int _inattack,int _outattack,int _indefence,int _outdefence,
						int _genuine,int _crit,int _hit,int _dodge,int _tenacity,int _durability,int _priceBound,int _price,int _goldBound,int _gold,int _sellPrice,\
						int _time,char *_photoId,int _move,int _culianCost,int _jinglianCost,int _hole,int _attrNumber)
{
	strncpy(id , _id,sizeof(id));
	strncpy(name , _name,sizeof(name));
	grade = _grade;
	order = _order;
	rank = _rank;
	type = _type;
	strncpy(party , _party,sizeof(party));
	suit_type = _suit_type;
	strncpy(suit_id , _suit_id,sizeof(suit_id));
	life = _life;
	inattack = _inattack;
	outattack = _outattack;
	indefence = _indefence;
	outdefence = _outdefence;
	genuine = _genuine;
	crit = _crit;
	hit = _hit;
	dodge = _dodge;
	tenacity = _tenacity;
	durability = _durability;
	priceBound=_priceBound;
	price = _price;
	goldBound=_goldBound;
	gold=_gold;
	sellPrice=_sellPrice;
	time=_time;
	strncpy(photoId , _photoId,sizeof(_photoId));
	move=_move;
	culianCost=_culianCost;
	jinglianCost=_jinglianCost;
	hole=_hole;
	attrNumber=_attrNumber;
}
char* Equip_config::getid(void)           //装备ID
{
		return id;
}
char* Equip_config::getname(void)		 //装备名称
{
		return name;
}
int    Equip_config::getgrade(void)        //装备等级
{
		return grade;
}
int Equip_config::getOrder(void)			//装备排序
{
	return order;
}
int	   Equip_config::getrank(void)         //装备级别
{
	return rank;
}
int    Equip_config::gettype(void)         //装备类型
{
	return type;
}
char*  Equip_config::getparty(void)        //装备门派
{
	return party;
}
int    Equip_config::getsuit_type(void)    //套装类别
{
	return suit_type;
}
char* Equip_config::getsuit_id(void)      //套装ID
{
	return suit_id;
}
int    Equip_config::getlife(void)         //生命值
{
	return life;
}
int    Equip_config::getinattack(void)     //内功攻击
{
	return inattack;
}
int    Equip_config::getoutattack(void)    //外功攻击
{
	return outattack;
}
int    Equip_config::getindefence(void)    //内功防御
{
	return indefence;
}
int    Equip_config::getoutdefence(void)   //外功防御
{
	return outdefence;
}
int    Equip_config::getgenuine(void)      //真气
{
	return genuine;
}
int    Equip_config::getcrit(void)         //暴击
{
	return crit;
}
int    Equip_config::gethit(void) 		 //命中
{
	return hit;
}
int    Equip_config::getdodge(void)        //闪避
{
	return dodge;
}
int    Equip_config::gettenacity(void) 	 //韧性
{
	return tenacity;
}
int	   Equip_config::getdurability(void)   //耐久度
{
	return durability;
}
int	   Equip_config::getMoneyBound(void) 
{
	return priceBound;
}
int	   Equip_config::getMoney(void)        //价格
{
	return price;
}
int		Equip_config::getgoldBound(void)  
{
	return goldBound;
}
int		Equip_config::getgold(void)  
{
	return gold;
}

int Equip_config::getPrice(void)      //卖出游戏币价格
{
	return sellPrice;
}

int Equip_config::getTime(void)
{
	return time;
}

char *Equip_config::getPhotoId(void)
{
	return photoId;
}

int Equip_config::getMove(void)
{
	return move;
}

int Equip_config::getCulianCost(void)
{
	return culianCost;
}

int Equip_config::getJinglianCost(void)
{
	return jinglianCost;
}

int Equip_config::getHole(void)
{
	return hole;
}
int Equip_config::getAttrNumber(void)
{
	return attrNumber;
}