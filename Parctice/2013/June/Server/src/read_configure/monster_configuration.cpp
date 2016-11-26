/********************************************************************

    created:   2012/2/24  15:24
	
	文件名：	monster_configuration.cpp

    author:       Tory 

    purpose:  monster_configuration.h的实现文件
	
	修改：	

*********************************************************************/
#include "monster_configuration.h"
#include<string.h>
#include <iostream>
Monster_Inform::Monster_Inform(char *_typeId, char *_type, char *_kind,double _rank,char *_nickName, double _lifeUpperVal,\
double _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud,double _outHrt,double _inHrt, double _outAttVal, double _inAttVal,\
double _outDefVal, double _inDefVal, int _defSumVal,double _hit,double _crit,double _voids,double _tenacity,int _moveRange,\
int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,int _angVal,vector<string> _skiIdSet,\
char *_genAttId,int _gold,set<string>& _failId,char *_photoId,char* _stage,int _experience,double _cdTime,int _fiveEleInt,\
int _fiveHurt,int _fiveEleRank,int _goFor,int _expTme,int _monyTme,int _speed,int _ownerAttriType,char* _ownerAttri,\
double _attackRatio,bool _isInnerAttack,int _radius)					
{

	int len;
	len = strlen(_typeId);
	typeId = new char[len+1];
	strncpy(typeId,_typeId,len);
	typeId[len]='\0';
	
	len = strlen(_type);
	type = new char[len+1];
	strncpy(type,_type,len);
	type[len]='\0';

	
	len = strlen(_kind);
	kind = new char[len+1];
	strncpy(kind,_kind,len);
	kind[len]='\0';
	rank = _rank;
	
	len = strlen(_nickName);
	nickName = new char[len+1];
	strncpy(nickName,_nickName,len);
	nickName[len]='\0';
	
	memset(genAttId,'\0',sizeof(genAttId));
	strncpy(genAttId,_genAttId,strlen(_genAttId));
	
	lifeUpperVal=_lifeUpperVal;
	
	lifeVal=_lifeVal;
	
	magicUpperVal = _magicUpperVal;
	magicVal = _magicVal;
	
	hrtSud = _getHrtSud;
	
	outHrt = _outHrt;
	
	inHrt= _inHrt;
	
	outAttVal = _outAttVal;
	
	inAttVal = _inAttVal;
	
	outDefVal = _outDefVal;
	
	inDefVal = _inDefVal;
	
	defSumVal = _defSumVal;
	
	hit = _hit;
	
	crit = _crit;
	
	voids = _voids;
	
	tenacity = _tenacity;
	
	walk_range = _moveRange;
	
	hatRange = _hatRange;
	
	attack_range = _attRange;
	
	failGoodsLess = _failGoodsless;
	
	failGoodsMost = _failGoodsmost;
	
	hatVal = _hatVal;
	
	angVal = _angVal;
	
	skiIdSet = _skiIdSet;
	
	gold = _gold;
	
	failList = _failId;
		
	len = strlen(_stage);
	stage = new char[len+1];
	strncpy(stage,_stage,len);
	stage[len]='\0';
	
	radius = _radius;
	
	cdTime = _cdTime;
	
	experience = _experience;
	
	len = strlen(_photoId);
	photoId = new char[len+1];
	strncpy(photoId,_photoId,len);
	photoId[len]='\0';
	
	speed = _speed;
	
	sum = 0;
	
	
	fiveEleInt = _fiveEleInt;
	fiveHurt = _fiveHurt;
	fiveEleRank = _fiveEleRank;
	
	goFor = _goFor;
	expTme = _expTme;
	monyTme = _monyTme;
	
	ownerAttriType = _ownerAttriType;
	attackRatio = _attackRatio;
	
	memset(ownerAttri,'\0',sizeof(ownerAttri));
	strncpy(ownerAttri,_ownerAttri,strlen(_ownerAttri));
	
	isInnerAttack = _isInnerAttack;
	
}
Monster_Inform::~Monster_Inform(void)
{
	if(typeId != NULL)
	{
		delete[] typeId;
		typeId = NULL;
	}
	if(type != NULL)
	{
		delete [] type;
		type = NULL;
	}
	if(kind != NULL)
	{
		delete [] kind;
		kind = NULL;
	}
	if(nickName != NULL)
	{
		delete[] nickName;
		nickName = NULL;
	}
	if(photoId != NULL)
	{
		delete[] photoId;
		photoId = NULL;
	}
}

char* Monster_Inform::getstage(void)
{
	return stage;
}

int Monster_Inform::getgold(void)
{
	return gold;
}

int Monster_Inform::getrank(void)
{
	return rank;
}

char* Monster_Inform::getkind(void)
{
	return kind;
}

int Monster_Inform::getExperience(void)
{
	return experience;
}

int Monster_Inform::getAngVal(void)
{
	return angVal;
}

vector<string> Monster_Inform::getSkiIdSet(void)
{
	return skiIdSet;
}
int Monster_Inform::getRank(void)
{
	return rank;
}

int Monster_Inform::getSpeed(void)
{
	return speed;
}


void Monster_Inform::print(char *monKindId)
{
	if(strcmp(kind,monKindId) != 0)
	{
		return;
	}
	
	cout<<"lifeUpperVal:"<<lifeUpperVal<<endl;
	
	
	
	cout<<"lifeVal:"<<lifeVal<<endl;
	
	
	
	cout<<"outHrt:"<<outHrt<<endl;
	
	
	cout<<"inHrt:"<<inHrt<<endl;
	
	
	
	cout<<"outAttVal:"<<outAttVal<<endl;
	
	
	
	cout<<"inAttVal:"<<inAttVal<<endl;
	
	
	cout<<"outDefVal:"<<outDefVal<<endl;
	
	
	
	cout<<"inDefVal:"<<inDefVal<<endl;
	
	
	
	cout<<"hit:"<<hit<<endl;
	
	
	
	cout<<"crit:"<<crit<<endl;
	 
	
	
	cout<<"voids:"<<voids<<endl;
	
	
	
	cout<<"tenacity:"<<tenacity<<endl;	
	
	
	cout<<"rank:"<<rank<<endl;
}
	