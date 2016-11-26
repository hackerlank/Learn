#ifndef HERO_CONFIGURATION_H
#define HERO_CONFIGURATION_H
#include"data_structure_struct.h"
#include<map>
#include <stdio.h>
#include <stdlib.h>

class Hero_Configuration
{
	private: 
		char *party_hero_Id;   //初始角色Id
		int  lifeUpperVal ;  	//生命上限值
		int  lifeVal;        	//当前生命值
		int  magicUpperVal ; 	//魔法上限值
		int  magicVal ;      	//当前魔法值
		Point pt;           	//当前坐标点（地图像像素点）
		int attack;         	//攻击力
		int eat;            	//损耗
		char *mapId;
	//	char *photoId;
		int atk_range;			//初始攻击范围
		/*Evan add 2012.3.30
	start
	注意：在使用期外攻比例，内攻比例，攻击比例，防御比例，
	都在获取的值的基础上除以100
	*/
	char 	*party;
	int     AttackAndDefense;			//攻防总值
	int     bufferCD;                    //攻击CD
	int     hited;                       //命中
	int     crit;                        //暴击
	int     dodge;                        //闪避
	int     tenacity;                     //韧性
	int     outratio;					//外攻比例
	int     inratio;                    //内攻比例
	int     attackratio;                 //攻击比例
	int     defenseratio;                 //防御比例
	/*end*/	
	/*2012.4.5 evan add start*/	
	int    sec_hurt;                //秒伤害
	int    five_elements_value;  //五行属性值
	
	/*2012.4.5 evan add end*/

public:
	Hero_Configuration(char *_mapId,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,
	Point _pt,int _attack,int _eat, int _atk_range);
	
	Hero_Configuration(char *_party_hero_Id,char *_mapId,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,
						Point _pt,int _attack,int _eat, int _atk_range,char *_party,int _AttackAndDefense,int _bufferCD,
						int _hited,int _crit,int _dodge,int _tenacity,int _outratio,int _inratio,int _attackratio,int _defenseratio);
	/*2012.4.5 evan add start*/	
	Hero_Configuration(char *_party_hero_Id,char *_mapId,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,
						Point _pt,int _attack,int _eat, int _atk_range,char *_party,int _AttackAndDefense,int _bufferCD,
						int _hited,int _crit,int _dodge,int _tenacity,int _outratio,int _inratio,int _attackratio,int _defenseratio,
						int _five_elements_value,int _sec_hurt);
	/*2012.4.5 evan add end*/
	char* getParty_Hero_Id(void);//获得初始角色ID					
	char* getMapId(void);
	int  getLifeUpperVal(void) ; 	//获得生命上限值
	int  getLifeVal(void) ;      	//获得当前生命值
	int  getMagicUpperVal(void) ; 	//获得魔法上限值
	int  getMagicVal(void) ;       	//获得当前魔法值
	Point getLocation(void);      	//获得当前位置
	int getAttack(void);           	//获得攻击力
	int getEaten(void);            	//获得损耗
//	char* getPhotoId(void);
	int getAtk_range();
	
/*Evan add 2012.3.30
	start
	*/	
	char* getParty(void);
	int getAttackAndDefense(void);			//攻防总值
	int getBufferCD(void);                    //攻击CD
	int getHited(void);                       //命中
	int getCrit(void);                        //暴击
	int getDodge(void);                        //闪避
	int getTenacity(void);                     //韧性
	int getOutRatio(void);					//外攻比例
	int getInRatio(void);                    //内攻比例
	int getAttackRatio(void);                 //攻击比例
	int getDefenseRatio(void);                 //防御比例
	/*end*/
	/*2012.4.5 evan add start*/
	int getSec_Hurt(void);//秒伤害
	int    getFive_Elements_Value(void);  //五行属性值
	
	/*2012.4.5 evan add end*/

	~Hero_Configuration(void);
};

typedef struct heroBasicData{
	char 	party_hero_id[50];  	//角色门派？？？
	char 	mapId[50];			//初始化所在地图ID
	int  	lifeUpperVal ;  	//生命上限值
	int  	lifeVal;        	//当前生命值
	int  	magicUpperVal ; 	//魔法上限值
	int  	magicVal ;      	//当前魔法值
	Point 	pt;           		//当前坐标点（地图像像素点）
	int 	attack;         	//攻击力
	int 	attkType;            	//损耗	
	int 	atk_range;			//初始攻击范围	
	int     AttackAndDefense;	//攻防总值
	int    	sec_hurt;           //秒伤害
	int     bufferCD;           //攻击CD
	int     hited;              //命中
	int     crit;               //暴击
	int     dodge;              //闪避
	int     tenacity;           //韧性
	//Evan add 2012.3.30start注意：在使用期外攻比例，内攻比例，攻击比例，防御比例，都在获取的值的基础上除以100
	int     outratio;			//外攻比例
	int     inratio;        	//内攻比例
	int     attackratio;        //攻击比例
	int     defenseratio;       //防御比例
	char 	party[8];			//角色门派
	int    	five_elements_value;//五行属性值

	//由读取的配置数据计算得来
	int		outattack;			//外功攻击
	int		inattack;			//内功攻击
	int		outdefense;			//外功防御
	int		indefense;			//内功防御
	int		outhurt;			//外功伤害
	int		inhurt;				//内功伤害

	heroBasicData(){}
	heroBasicData(char *party_hero_id, char *mapId, int lifeUpperVal, int lifeVal, int magicUpperVal, int magicVal, Point pt, int attack, int _attkType, int atk_range, int AttackAndDefense, int sec_hurt, int bufferCD, int hited, int crit, int dodge, int tenacity, int outratio, int inratio, int attackratio, int defenseratio, char *party, int five_elements_value){
	//	printf("in HeroBasicData 1000000000000000000\n");
		if(party_hero_id != NULL){
		//	printf("party_hero_id:%s\n",party_hero_id);
			memcpy(this->party_hero_id, party_hero_id, strlen(party_hero_id));
			this->party_hero_id[strlen(party_hero_id)] = '\0';;
		}
		if(mapId != NULL){
		//	printf("mapId:%s\n",mapId);
			memcpy(this->mapId, mapId, strlen(mapId));
			this->mapId[strlen(mapId)] = '\0';
		}
		this->lifeUpperVal =  lifeUpperVal;  	//生命上限值
	  	this->lifeVal = lifeVal;        		//当前生命值
	  	this->magicUpperVal = magicUpperVal; 	//魔法上限值
	  	this->magicVal = magicVal ;      		//当前魔法值
		this->pt = pt;           				//当前坐标点（地图像像素点）
	 	this->attack = attack;         			//攻击力
	 	this->attkType = _attkType;            	//职业攻击类型	
	 	this->atk_range = atk_range;			//初始攻击范围	
	    this->AttackAndDefense = AttackAndDefense;	//攻防总值
	    this->sec_hurt = sec_hurt;           	//秒伤害
	    this->bufferCD = bufferCD;           	//攻击CD
	    this->hited = hited;              		//命中
	    this->crit = crit;               		//暴击
	    this->dodge = dodge;              		//闪避
	    this->tenacity = tenacity;           	//韧性
		//Evan add 2012.3.30start注意：在使用期外攻比例，内攻比例，攻击比例，防御比例，都在获取的值的基础上除以100
	    this->outratio = outratio;				//外攻比例
	    this->inratio = inratio;        		//内攻比例
	    this->attackratio = attackratio;        //攻击比例
	    this->defenseratio = defenseratio;      //防御比例
	 	if(party != NULL){
		//	printf("party:%s\n",party);
			memcpy(this->party, party, strlen(party));	//角色门派
			this->party[strlen(party)] = '\0';
	    }
		this->five_elements_value = five_elements_value;//五行属性值
	
		//由读取的配置数据计算得来
		this->outattack = (AttackAndDefense*outratio*attackratio)/100;			//外功攻击
		this->inattack = (AttackAndDefense*inratio*attackratio)/100;			//内功攻击
		this->outdefense = (AttackAndDefense*outratio*defenseratio)/100;		//外功防御
		this->indefense = (AttackAndDefense*inratio*defenseratio)/100;			//内功防御
		this->outhurt = sec_hurt*outratio*bufferCD/10;							//外功伤害
		this->inhurt = sec_hurt*inratio*bufferCD/10;							//内功伤害	
	
	}
}HeroBasicData;

/**************************************
* 传入参数 :HeroBasicData *obj，输出文件名：outfile
* Description：用于测试从game server中的Hero Basic Data数据是否正确
***************************************/
int showHeroBasicData(HeroBasicData *obj, char *outfile);

#endif
