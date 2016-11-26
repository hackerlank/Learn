#include "ride_config.h"
#include<cstring>

Ride_Config::Ride_Config(int _quality,int _expMax,int _lifeUpperVal,int _magicUpperVal,int _outAttack,int _inAttack,int _outDef,int _inDef,int _hited,int _crit,int _dodge,int _tenacity,int _move,int _evolutionMax,int _expTimes,int _skill001,int _skill002,int _skill003,int _skill004,int _skill005,int _skill006,int _skill007,int _skill008,int _skill009,int _skill010,char* _photoId,char* _nickName)
{
	quality=_quality;
	expMax=_expMax;
	lifeUpperVal=_lifeUpperVal;
	magicUpperVal=_magicUpperVal;
	outAttack=_outAttack;
	inAttack=_inAttack;
	outDef=_outDef;
	inDef=_inDef;
	hited=_hited;
	crit=_crit;
	dodge=_dodge;
	tenacity=_tenacity;
	move=_move;
	evolutionMax=_evolutionMax;
	expTimes=_expTimes;
	skill001=_skill001;
	skill002=_skill002;
	skill003=_skill003;
	skill004=_skill004;
	skill005=_skill005;
	skill006=_skill006;
	skill007=_skill007;
	skill008=_skill008;
	skill009=_skill009;
	skill010=_skill010;
	memset(photoId,0,sizeof(photoId));
	strncpy(photoId,_photoId,sizeof(photoId));
	memset(nickName,0,sizeof(nickName));
	strncpy(nickName,_nickName,sizeof(nickName));
}

int Ride_Config::getQuality(void)
{
	return quality;
}

int Ride_Config::getExpMax(void)
{
	return expMax;
}

int Ride_Config::getLifeUpperVal(void)
{
	return lifeUpperVal;
}

int Ride_Config::getMagicUpperVal(void)
{
	return magicUpperVal;
}

int Ride_Config::getOutAttack(void)
{
	return outAttack;
}

int Ride_Config::getInAttack(void)
{
	return inAttack;
}

int Ride_Config::getOutDef(void)
{
	return outDef;
}

int Ride_Config::getInDef(void)
{
	return inDef;
}

int Ride_Config::getHited(void)
{
	return hited;
}

int Ride_Config::getCrit(void)
{
	return crit;
}

int Ride_Config::getDodge(void)
{
	return dodge;
}

int Ride_Config::getTenacity(void)
{
	return tenacity;
}

int Ride_Config::getMove(void)
{
	return move;
}

int Ride_Config::getEvolutionMax(void)
{
	return evolutionMax;
}

int Ride_Config::getExpTimes(void)
{
	return expTimes;
}

int Ride_Config::getSkill(int index)
{
	if (index==0)
	{
		return skill001;
	}
	else if (index==1)
	{
		return skill002;
	}
	else if (index==2)
	{
		return skill003;
	}
	else if (index==3)
	{
		return skill004;
	}
	else if (index==4)
	{
		return skill005;
	}
	else if (index==5)
	{
		return skill006;
	}
	else if (index==6)
	{
		return skill007;
	}
	else if (index==7)
	{
		return skill008;
	}
	else if (index==8)
	{
		return skill009;
	}
	else if (index==9)
	{
		return skill010;
	}
}

char *Ride_Config::getPhotoId(void)
{
	return photoId;
}

char* Ride_Config::getNickName(void)
{
	return nickName;
}