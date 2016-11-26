#ifndef _EQUIP_
#define _EQUIP_
#include<string>
using namespace std;
class Equip_config
{
private:
		char id[20];           //装备ID
		char name[50];		 //装备名称
		int    grade;        //装备等级
		int order;			//装备排序
		int    rank;         //装备级别
		int	   type;         //装备类型
		char party[10];        //装备门派
		int    suit_type;    //套装类别
		char suit_id[20];      //套装ID		
		int    life;         //生命值
		int    inattack;     //内功攻击
		int    outattack;    //外功攻击
		int    indefence;    //内功防御
		int    outdefence;   //外功防御
		int    genuine;      //真气
		int    crit;         //暴击
		int    hit; 		 //命中
		int    dodge;        //闪避
		int    tenacity; 	 //韧性
		int	   durability;   //耐久度
		int priceBound;
		int	   price;        //价格
		int goldBound;
		int    gold;		 //元宝价格
		int sellPrice;
		int time;				//时装时间
		char photoId[10];		//图片id	
		int move;				//移动速度
		int culianCost;
		int jinglianCost;
		int hole;
		int attrNumber;
		
public:
		Equip_config(char* _id,char* _name,int _grade,int _order,int _rank,int _type,char* _party,int _suit_type,char* _suit_id,
						int _life,int _inattack,int _outattack,int _indefence,int _outdefence,
						int _genuine,int _crit,int _hit,int _dodge,int _tenacity,int _durability,int _priceBound,int _price,int _goldBound,int _gold,int _sellPrice,\
						int _time,char *_photoId,int _move,int _culianCost,int _jinglianCost,int _hole,int _attrNumber);
		char* getid(void);           //装备ID
		char* getname(void);		 //装备名称
		int    getgrade(void);        //装备等级
		int getOrder(void);			//装备排序
		int    getrank(void);         //装备级别
		int	   gettype(void);         //装备类型
		char* getparty(void);        //装备门派
		int    getsuit_type(void);    //套装类别
		char* getsuit_id(void);      //套装ID
		int    getlife(void);         //生命值
		int    getinattack(void);     //内功攻击
		int    getoutattack(void);    //外功攻击
		int    getindefence(void);    //内功防御
		int    getoutdefence(void);   //外功防御
		int    getgenuine(void);      //真气
		int    getcrit(void);         //暴击
		int    gethit(void); 		 //命中
		int    getdodge(void);        //闪避
		int    gettenacity(void); 	 //韧性
		int	   getdurability(void);   //耐久度
		int	   getMoneyBound(void) ;	
		int	   getMoney(void);        //价格
		int		getgoldBound(void) ;
		int 	getgold(void);
		int getPrice(void);
		int getTime(void);
		char *getPhotoId(void);
		int getMove(void);
		int getCulianCost(void);
		int getJinglianCost(void);
		int getHole(void);
		int getAttrNumber(void);
};
#endif
