#ifndef RIDE_CONFIG
#define RIDE_CONFIG
#include<iostream>

using namespace std;

class Ride_Config
{
private:
	int quality;
	int expMax;
	int lifeUpperVal;
	int magicUpperVal;
	int outAttack;
	int inAttack;
	int outDef;
	int inDef;
	int hited;
	int crit;
	int dodge;
	int tenacity;
	int move;
	int evolutionMax;
	int expTimes;
	int skill001;
	int skill002;
	int skill003;
	int skill004;
	int skill005;
	int skill006;
	int skill007;
	int skill008;
	int skill009;
	int skill010;
	char photoId[20];
	char nickName[50];
public:
	Ride_Config(int _quality,int _expMax,int _lifeUpperVal,int _magicUpperVal,int _outAttack,int _inAttack,int _outDef,int _inDef,int _hited,int _crit,int _dodge,int _tenacity,int _move,int _evolutionMax,int _expTimes,int _skill001,int _skill002,int _skill003,int _skill004,int _skill005,int _skill006,int _skill007,int _skill008,int _skill009,int _skill010,char *_photoId,char *_nickName);
	int getQuality(void);
	int getExpMax(void);
	int getLifeUpperVal(void);
	int getMagicUpperVal(void);
	int getOutAttack(void);
	int getInAttack(void);
	int getOutDef(void);
	int getInDef(void);
	int getHited(void);
	int getCrit(void);
	int getDodge(void);
	int getTenacity(void);
	int getMove(void);
	int getEvolutionMax(void);
	int getExpTimes(void);
	int getSkill(int index);
	char *getPhotoId(void);
	char* getNickName(void);
};

#endif