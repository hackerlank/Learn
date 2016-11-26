/***********************************
* Author: 	
* Date	:		 	
* Description: 游戏中所有字符数组的长度宏定义
* Amend:	Tory 2012.10.12
*************************************/
#include <map>
#ifndef WHOLEDEFINE
#define WHOLEDEFINE


using namespace std;

#define int64	long long
#define int32	int
#define int16   short
#define int8	char

#define uint64 unsigned long long
#define uint32 unsigned int
#define uint16 unsigned short
#define uint8  unsigned char
#define byte   unsigned char

#define IDL 50						//定义ID长度
#define UUIDL 36					//uuid生成的id长度
#define EL 433						//
#define PL 361						//
#define BL 5185
#define SL 469
#define TRADE_NUM 16		
#define PRIVATE_STALL_NUM 1200
#define COPYCAUSELEN 253
#define CAUSELEN 14
#define ALLTITLELEN 1000
#define TITLELEN 5

#define NORMAL_HERO_SPEED		normalHeroSpeed				//玩家正常速度
#define NORMAL_MONSTER_SPEED	normalMonsterSpeed			//怪物正常速度
#define NORMAL_WAGON_SPEED		normalWagonSpeed			//马车正常速度
#define NORMAL_PET_SPEED		normalPetSpeed				//宠物正常速度

#define  generalDrugNum  2
#define  buffDrugNum  10

#define  OUT_VIEW_LENGTH  1024         //走出视野时字符串容器的容量
#define  IN_VIEW_LENGTH  1024         //走入出视野时字符串容器的容量
#define  MONSTER_MSG_LENGTH  1023    //怪物消息发送长度
#define  MONSTER_ROAD_LENGTH  10240    //怪物寻路时，中间变量
#define  MONSTER_MID_LENGTH  30      //在复制对象时，中间id长度
#define  TRAP_ATT_LENGTH  10240        //暗器群攻消息长度
#define  SHOR_MID_VALUE_LENGTH  80   //其他一些短的字符变量长度
#define  LONG_MID_VALUE_LENGTH  200  //其他一些长的字符变量长度
#define  LITTLE_MID_VALUE_LENGTH  10 //其他一些很短的字符变量长度
#define  HEROID_LENGTH 50				//实例heroid的最大长度
#define  TYPE_LENGTH 4				//普通的类型长度
#define  NOTKNOW_ATTRIBUTE_LENGTH 100 //未知属性长度
#define  GEM_LENGTH 50				//宝石属性的最大长度
#define  LITTLE_VALUE_LENGTH = 20   //小数据长度
#define	MAX_DISTANCE_IN_MAP		0x7FFFffff	//最大距离

const int DROP_GOODS_DISPERAR_TIME = 60; //60秒会消失

//common msg parser macro by benliao 20121125
#define MSG_BEGIN(buff, buflen) char *_head=buff+6; char *p = _head; int _buflen=buflen; unsigned char _len = *p ; int _j=0;
#define MSG_CHAR(c) c=p+1;  p += _len+1; if ((p-_head) > _buflen+1) return; _len = *p; *p=0;
#define MSG_CHAR_END(c) c=p+1; if(_len !=0) {p += _len; if ((p-_head) > _buflen) return;} *(_head+_buflen)=0;
#define MSG_INT(i) _j=(unsigned char)*(p+1)<<24|(unsigned char)*(p+2)<<16|(unsigned char)*(p+3)<<8|(unsigned char)*(p+4); if(_j<0) return; p += _len+1; if ((p-_head) > _buflen+1) return; _len = *p; i=_j;
#define MSG_INT_MAX(i, m) _j=(unsigned char)*(p+1)<<24|(unsigned char)*(p+2)<<16|(unsigned char)*(p+3)<<8|(unsigned char)*(p+4); if(_j<0) return; if(_j > m) return; p += _len+1; if ((p-_head) > _buflen+1) return; _len = *p; i=_j;
#define MSG_CHAR_U(c) c=p+1; *(_head+_buflen)=0;
//common outbouf for everyone
extern char g_out_buf[20480];
extern int g_msg_len;
class Hero;
class Role;

extern Hero *pg_hero;
extern Role *pg_role;
extern map<int, Role*> fd_to_pRole;

extern int normalHeroSpeed;
extern int normalPetSpeed;
extern int normalMonsterSpeed;
extern int normalWagonSpeed;

#endif 
