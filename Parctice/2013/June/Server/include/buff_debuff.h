#include<map>
#include<iostream>
#include"my_timer.h"
using namespace std;

#define NO_BUFF_OR_DEBUF_STATE		0x0				//无buff或debuff状态
#define DEBUF_DIZZ_STATE			0x1				//眩晕
#define DEBUF_FORB_MOVE_STATE		0x2				//定身：可操作不可移动
#define DEBUF_FORB_ATTK_STATE		0x4				//点穴：可移动
#define DEBUF_IN_POISON_STATE		0x8				//中毒：持续掉血
#define	DEBUF_LOSE_HIT_STATE 		0x10			//丢失：降低命中
#define DEBUF_LOSE_DF_AT_STATE		0x20			//黯灭：减攻减防
#define DEBUF_LOSE_TENC_STATE		0x40			//虚弱：减少韧性
#define BUFF_ADD_CRIT_STATE			0x80			//醉拳：增加暴击
#define BUFF_ADD_DODGE_STATE		0x100			//闪避
#define	BUFF_ADD_SACRF_STATE		0x200			//牺牲：消耗生命提升攻击
#define BUFF_REFLEX_STATE			0x400			//反弹：反弹伤害
#define	BUFF_INVINCIBLE_STATE		0x800			//无敌
#define BUFF_BLADE_STORM_STATE		0x1000			//剑刃风暴
#define DEBUF_LOSE_SPEED_STATE		0x2000			//减少移动速度
#define BUFF_MAGIC_SHIELD_STATE		0x4000			//魔法盾状态
#define PLAY_ANIMATION_STATE		0x8000			//播放动画状态
#define MAX_HERO_BUFF_NUM			15				//角色身上最大buff和debuff数量
typedef struct Buff_debuff_conf_S
{
	char skillId[51];
	int effect;
	int lastTimeBase;
	int lastTimeFactor;
	int effectBase;
	int effectIncFactor;
	Buff_debuff_conf_S(char *id, int eft, int timeB, int timeF, int eB, int eF)
	{
		strncpy(skillId, id, sizeof(skillId));
		effect = eft;
		lastTimeBase = timeB;
		lastTimeFactor = timeF;
		effectBase = eB;
		effectIncFactor = eF;
	}
} Buff_debuff_conf_T;

typedef struct SkillBuff_S
{
	char skillId[51];
	unsigned skillLevel;
	char atkerId[51];
	int lastTime;
	int leftTime;
	int perVal;
	int totalVal;
	ev_timer *timer;
	SkillBuff_S()
	{
		timer = new ev_timer;
		memset(skillId, 0, sizeof(skillId));
		memset(atkerId, 0, sizeof(atkerId));
		skillLevel = 0;
		lastTime = 0;
		perVal = 0;
		totalVal = 0;
	}
	~SkillBuff_S()
	{
		delete timer;
	}
}SkillBuff_T;

extern map<string, Buff_debuff_conf_T*> buf_debuf_conf;	//buff和debuff的配置