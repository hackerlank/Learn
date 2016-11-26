/* 
		文件类型：头文件
		文件名称：hero.h
		文件作用：实体类装备的属性和功能的定义
		实现时间：2012.4.16 10:00
		  实现人：Evan
*/

#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include<string>
#include<vector>
#include<map>
#include"data_structure_struct.h"
#include"libev.h"
using namespace std;


class Hero;
class Equip_config;
class Map_Inform;

/* tory add 2013.1.14 宝石合成配置数据 */
typedef struct{
	int cost[3];	//合成相应等级的宝石金钱消耗，宝石从二级开始
	int rate[3];	//合成相应等级的宝石成功概率*100，宝石从二级开始
}HeChengConfig;


class Equipment
{
private:

		int    lifeTotal;         //生命值
		int    magicTotal;      //真气
		int    inAttackTotal;     //内功攻击
		int    outAttackTotal;    //外功攻击
		int    inDefenceTotal;    //内功防御
		int    outDefenceTotal;   //外功防御
		int    critTotal;         //暴击
		int    hitTotal; 		 //命中
		int    dodgeTotal;        //闪避
		int    tenacityTotal; 	 //韧性
		
		vector<string> xq_bs;	 //装备上镶嵌的宝石的集合
		
		EquipmentData *equipmentdata;
				
		/* 
		* tory add 2012.12.13
		* bs_xq_num：按宝石作用类型记录镶嵌的宝石数目，宝石作用类型：宝石ID的最后一位f_cl_122_100
		* 0:石榴石;		1:翡翠;		2:绿宝石		3:黄宝石 	4:钻石		
		* 5:猫眼石		6:紫宝石	7:红宝石		8:蓝宝石	9:玛瑙石
		*/
		int bs_xq_num[10];	
		
		char dropMsg[LONG_MID_VALUE_LENGTH + 1];
		char dropDisMsg[LONG_MID_VALUE_LENGTH + 1];		
		ev_timer timer;
		Point piexPt;
		Map_Inform *map_now;	
		
		void setDiamonLife(int _diamonLife);
		
		void setDiamonMagic(int _diamonMagic);
		
		void setDiamonInattack(int _diamonInattack);
		
		void setDiamonOutattack(int _diamonOutattack);
		
		void setDiamonIndefence(int _diamonIndefence);
		
		void setDiamonOutdefence(int _diamonOutdefence);
		
		void setDiamonCrit(int _diamonCrit);
		
		void setDiamonHit(int _diamonHit);
		
		void setDiamonDodge(int _diamonDodge);
		
		void setDiamonTenacity(int _diamonTenacity);
		
public:
		//物品基类接口
		int repairCost(void);//返回修理费用  
		void repair(void);//装备修理 
		Equipment(Equip_config *equip_pt);
		Equipment(EquipmentData *_equipmentdata);
		void initEquip(Equip_config *equip_pt);
		~Equipment(void);
		
		char* getentityid(void);		//实体类id
		
		char* getid(void);           //装备ID
		
		char* getname(void);		 //装备名称
		
		int    getgrade(void);        //装备等级
		
		int    getrank(void);         //装备级别
		
		int    gettype(void);         //装备类型
		
		char*  getparty(void);        //装备门派
		
		int    getsuit_type(void);    //套装类别
		
		char* getsuit_id(void);      //套装ID
		
		int    getlife(void);         //生命值
		
		int    getinattack(void);     //内功攻击
		
		int    getoutattack(void);    //外功攻击
		
		int    getindefence(void);    //内功防御
		
		int    getoutdefence(void);   //外功防御
		
		int    getMagic(void);      //真气
		
		int    getcrit(void);         //暴击
		
		int    gethit(void); 		 //命中
		
		int    getdodge(void);        //闪避
		
		int    gettenacity(void); 	 //韧性
		
		int	   getdurability(void);   //耐久度
		
		int	   getprice(void);        //价格
		
		int	   getbound(void);			//绑定状态
		void setBound(int bound);		
		
		int getsellprice(void);
		
		int getgold(void);
		
		int getpriceBound(void);
		
		int getgoldBound(void);
		
		char *getPhotoId(void);	
		
		int getCulianLuckyNumber(void);
		
		int getMove(void);
		
		int getRongLianCost(void);
		
		int getKaiRenCost(void);
			
		int	   getKaiRenLevel(void);	
		
		int    getRongLianLevel(void);	
		
		int getFourDiamonNumber(void);
		
		int xianQiangFourDiamon(void);
		
		int zhaiQuFourDiamon(void);
		
		int getRongLianLucky(void);
		
		int    getHoleNumber(void);		 //装备打孔的数目

		int getDiamonLife(void);
		
		int getDiamonMagic(void);
		
		int getDiamonInattack(void);
		
		int getDiamonOutattack(void);
		
		int getDiamonIndefence(void);
		
		int getDiamonOutdefence(void);
		
		int getDiamonCrit(void);
		
		int getDiamonHit(void);
		
		int getDiamonDodge(void);
		
		int getDiamonTenacity(void);
		
		int getBaseLife(void);
		int getBaseMagic(void);
		int getBaseOutAttack(void);
		int getBaseInAttack(void);
		int getBaseOutDefense(void);
		int getBaseInDefense(void);
		int getBaseHit(void);
		int getBaseCrit(void);
		int getBaseDodge(void);
		int getBaseTenacity(void);
				
		vector<string> getxq_bs(void);	 //装备上镶嵌的宝石的集合
		void   setxq_bs(vector<string> _xq_bs);
		
		void saveInStruct(void);
		
		void msg_return_equipInform(char* msg,int len);
		
		int    getIsBag(void);		//装备是否穿在身上 0，在背包内；1，在身上
		void   setisbag(int _isbag);
		
		EquipmentData* getEquipmentData(void);
		
		int showEquipmentData(EquipmentData *obj, char *outfile);
		
		void wareEquipSetBound(void);			//穿装备时,将未绑定装备变为绑定装备

		/*生成物品掉落信息*/
		void formDropMsg(Hero *killHero,char *identity);
		
		/*获得物品掉落信息*/
		char* getDropMsg(void);
		
		/*生成物品掉落信息*/
		void formDropDisMsg(void);
		
		/*获得物品掉落信息*/
		char* getDropDisMsg(void);
		
		/*启动掉落装备计时器*/
		void initTime(void);
		
		/*装备地图消亡*/
		void disperMsg(void);
		
		/*装备掉落以及消息发送*/
		void bronMsg(Hero *killHero,char *identity);
		
		/*获得掉落装备的位置*/
		Point getPiexPt(void);
		//按宝石类型增加镶嵌的宝石数目
		void addBsNumByTy(char* goodsid);	
		//按宝石类型减少镶嵌的宝石数目
		void delBsNumByTy(char* goodsid);
		//按宝石类型获取镶嵌的宝石数目
		int getBsNumByTy(char* goodsid);
		
		void diamonAttribute(Hero *hero,char* goodsid);
		
		void diamonOff(Hero *hero,int index);
		
		bool testDiamon(int index,char *goodsid);
		
		//穿上时装,开启时间倒计时
		void beginTime(void);
		//判断时装是否有效
		bool isEffect(Hero *hero);
		//返回时装还有多少时间
		int remainTime(void);
		
		//解绑减属性
		void unboundDecreaseAttr(Hero *hero,Equip_config *equip_config);
		
		//熔炼增加属性
		void rongLianAttributeIncrease(Hero *hero,int level);
		//熔炼预览消息发送
		void msg_rongLian(char *msg,int len,int vipSuccess);
		void initRongLian(Hero *hero);
		void rongLianFailed(void);
		//开刃增加属性
		void kaiRenAttributeIncrease(Hero *hero,int level);
		//开刃预览消息发送
		void msg_kaiRen(char *msg,int len);
		void initKaiRen(Hero *hero);
		
		void countAttribute(void);
};
#endif

