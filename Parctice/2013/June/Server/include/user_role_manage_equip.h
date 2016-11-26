/*
* 文件类型：头文件
* 文件名称：user_role_manage_equip.h
* 文件作用：成长系统处理
* 实现者：Evan		 Amend:Tory 2012.12.6
* 完成时间：2012.6.13
*/
#ifndef USER_ROLE_MANAGE_EQUIP
#define USER_ROLE_MANAGE_EQUIP
#include"equipment.h"
#include"hero.h"

/*
* author: evan
* describe:请求将要锻造的装备需符合要求和达到预期,响应客户端的4,10命令
*/
void require_equip_operater(char *buffer);	

void heroDropEquipment(Hero *hero,Equipment *equip);	
void ChangeEquipToHero(Hero *hero,Equipment *equip,int type);		//装备对人物属性的影响

int  SuitManage(Hero *hero,Equipment *equip,int type);			//玩家身上套装的管理,type=1，玩家穿装备，type=2，玩家脱装备   evan add 2012.8.31
void equipchange(char *buffer);									//玩家脱装备的方法实现
void putOnEquip(Hero *hero,int index,char* goodsid);			//玩家穿装备的方法实现
void wearEquip(Hero *hero,Equipment *equip);					//玩家穿装备的辅助方法实现
	//更换装备导致玩家自身属性改变的方法实现，type=-1：脱装备；type=1:穿装备；

	
void OperateHelp_JingLian(Hero* hero, Equipment *equipment, int lev_gap=1);		//精炼的辅助方法，将下一级装备精练的要求和预期发给客户端
void msg_yiZhi(Hero* hero, Equipment *src_quipment, Equipment *des_equipment);//精炼的辅助方法，将装备转移后的属性发给客户端

int DurabilityManage_Attack(Hero *hero);						//装备耐久度管理,玩家攻击
int DurabilityManage_Hited(Hero *hero);						    //装备耐久度管理,玩家受击
int DurabilityManage_Dead(Hero *hero);						    //装备耐久度管理,玩家死亡
string DurabilityManage_Help(Hero *hero,int part_body);			//装备耐久度的辅助方法

bool takeOffEquip(string heroId,int equip_number,string equipId,int equiptype);			//脱装备

void equiphelp_operate(char *buffer); 		//玩家装备的各种操作命令解析,处理（4,9命令）装备锻造功能具体实现总入口

int EquipOperateKaiRen(Hero *hero,Equipment *equipment);		//进入装备粗炼操作的具体实现	

int EquipOperateRongLian(Hero *hero,Equipment *equip,char* goodsid, int index);

int EquipOperateHeCheng(Hero *hero, int developMode,char* firstGoodsid, int first_index,char* secondGoodsid, int second_index,char* thirdGoodsid, int third_index,char *luckGoodsid,int index);

int EquipOperateYiZhi(Hero *hero,Equipment *equipA,Equipment *equipB);//装备粗炼等级移植的功能实现 evan 2012.11.22

int EquipOperateXQ(Hero *hero,Equipment *equip,char* ,int);//装备的镶嵌操作，index为镶嵌宝石的ID

bool EquipOperateZQ(Hero *hero,Equipment *equip, char* goodsid,int index);//装备的宝石摘取操作，index为摘取的宝石的ID

//时装到期,脱时装并摧毁的方法
void fasionDestory(Hero *hero,int _index,char *identity);

//坐骑穿装备的方法
void rideWearEquip(Hero *hero,Equipment *equipment,int bagIndex);
//坐骑脱装备通信
void rideTakeOffEquip(char *buffer);
#endif