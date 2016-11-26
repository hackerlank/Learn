#include "data_structure_struct.h"
#include<map>

typedef struct Hero_Conf_S
{
	char party[8];
	char mapId[32];
	Point bornPt;
	unsigned attkType;
	unsigned bornHeroSkillExp;
	unsigned lifeUpperVal;
	unsigned magicUpperVal;
	unsigned outDef;
	unsigned inDef;
	unsigned outAttack;
	unsigned inAttack;
	unsigned hited;
	unsigned crit;
	unsigned dodge;
	unsigned tenacity;
	unsigned outHurt;
	unsigned inHurt;
	unsigned upgradeNeedExp[200];
	unsigned addLife[200];
	unsigned addMagic[200];
	unsigned addOutDef[200];
	unsigned addInDef[200];
	unsigned addOutAttack[200];
	unsigned addInAttack[200];
	unsigned addHited[200];
	unsigned addCrit[200];
	unsigned addDodge[200];
	unsigned addTenacity[200];
	unsigned addOutHurt[200];
	unsigned addInHurt[200];
} Hero_Conf_T;

extern map<string, Hero_Conf_T> party_2_heroConf;