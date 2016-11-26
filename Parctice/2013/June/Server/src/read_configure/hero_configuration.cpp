#include<iostream>
#include"hero_configuration.h"
using namespace std;
Hero_Configuration::Hero_Configuration(char *_mapId,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,Point _pt,int _attack,int _eat, int _atk_range)
{
	mapId=_mapId;
	lifeUpperVal=_lifeUpperVal;
	magicUpperVal=_magicUpperVal;
	magicVal=_magicVal;
	lifeVal=_lifeVal;
	pt=_pt;
	attack=_attack;
	eat=_eat;
	atk_range=_atk_range;
}
Hero_Configuration::Hero_Configuration(char *_party_hero_Id,char *_mapId,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,Point _pt,int _attack,int _eat, int _atk_range,char *_party,int _AttackAndDefense,int _bufferCD,int _hited,int _crit,int _dodge,int _tenacity,int _outratio,int _inratio,int _attackratio,int _defenseratio)
{
	party_hero_Id = _party_hero_Id;
	mapId=_mapId;
	lifeUpperVal=_lifeUpperVal;
	magicUpperVal=_magicUpperVal;
	magicVal=_magicVal;
	lifeVal=_lifeVal;
	pt=_pt;
	attack=_attack;
	eat=_eat;
	atk_range=_atk_range;
	party = _party;
	AttackAndDefense = _AttackAndDefense;
	bufferCD = _bufferCD;
	hited = _hited;
	crit = _crit;
	dodge = _dodge;
	tenacity = _tenacity;
	outratio = _outratio;
	inratio = _inratio;
	attackratio = _attackratio;
	defenseratio = _defenseratio;
}
/*2012.4.5 evan add start*/	
Hero_Configuration::Hero_Configuration(char *_party_hero_Id,char *_mapId,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,
						Point _pt,int _attack,int _eat, int _atk_range,char *_party,int _AttackAndDefense,int _bufferCD,
						int _hited,int _crit,int _dodge,int _tenacity,int _outratio,int _inratio,int _attackratio,int _defenseratio,
						int _five_elements_value,int _sec_hurt)
{
	party_hero_Id = _party_hero_Id;
	mapId=_mapId;
	lifeUpperVal=_lifeUpperVal;
	magicUpperVal=_magicUpperVal;
	magicVal=_magicVal;
	lifeVal=_lifeVal;
	pt=_pt;
	attack=_attack;
	eat=_eat;
	atk_range=_atk_range;
	party = _party;
	AttackAndDefense = _AttackAndDefense;
	bufferCD = _bufferCD;
	hited = _hited;
	crit = _crit;
	dodge = _dodge;
	tenacity = _tenacity;
	outratio = _outratio;
	inratio = _inratio;
	attackratio = _attackratio;
	defenseratio = _defenseratio;
	five_elements_value = _five_elements_value;
	sec_hurt = _sec_hurt;
}						
	/*2012.4.5 evan add end*/
char* Hero_Configuration::getMapId(void)
{
	return mapId;
}
int Hero_Configuration::getLifeUpperVal(void)
{
	return lifeUpperVal;
}
int Hero_Configuration::getLifeVal(void)
{
	return lifeVal;
}
int Hero_Configuration::getMagicUpperVal(void)
{
	return magicUpperVal;
}
int Hero_Configuration::getMagicVal(void)
{
	return magicVal;
}
Point Hero_Configuration::getLocation(void)
{
	return pt;
}
int Hero_Configuration::getAttack(void)
{
	return attack;
}
int Hero_Configuration::getEaten(void)
{
	return eat;
}

int Hero_Configuration::getAtk_range()
{
	return atk_range;
}

/*Evan add 2012.3.30
	start
	*/	
char* Hero_Configuration::getParty(void)
{
	return party;
}
int Hero_Configuration::getAttackAndDefense()	//攻防总值
{
	return AttackAndDefense;
}
int Hero_Configuration::getBufferCD()                    //攻击CD
{
	return bufferCD;
}
int Hero_Configuration::getHited()                       //命中
{
	return hited;
}
int Hero_Configuration::getCrit()                        //暴击
{
	return crit;
}
int Hero_Configuration::getDodge()                        //闪避
{
	return dodge;
}
int Hero_Configuration::getTenacity()                     //韧性
{
	return tenacity;
}
int Hero_Configuration::getOutRatio()					//外攻比例
{
	return outratio;
}
int Hero_Configuration::getInRatio()                   //内攻比例
{
	return inratio;
}
int Hero_Configuration::getAttackRatio()                 //攻击比例
{
	return attackratio;
}
int Hero_Configuration::getDefenseRatio()                //防御比例
{
	return defenseratio;
}
	/*end*/
/*2012.4.5 evan add start*/
int Hero_Configuration::getSec_Hurt(void)//秒伤害
{
	return sec_hurt;
}
int    Hero_Configuration::getFive_Elements_Value(void)  //五行属性值
{
	return five_elements_value;
}

	/*2012.4.5 evan add end*/

Hero_Configuration::~Hero_Configuration()
{
	delete [] mapId;
}

/**************************************
* Author:	Tory
* Date	:	2012.9.12
* 传入参数 :HeroBasicData *obj，输出文件名：outfile
* Description：用于测试从game server中的Hero Basic Data数据是否正确
***************************************/
int showHeroBasicData(HeroBasicData *obj, char *outfile)
{
	FILE *out;
	if((out = fopen(outfile, "w+")) == NULL){
		fprintf(stderr, "fopen file %s error!\n", outfile);
		return -1;
	//	exit(EXIT_FAILURE);
	}
 	fprintf(out, "test HeroData party_hero_Id:%s\n", obj->party_hero_id);
	fprintf(out, "test HeroData mapId:%s\n", obj->mapId);
	fprintf(out, "test HeroData lifeUpperVal:%d\n", obj->lifeUpperVal);
	fprintf(out, "test HeroData lifeVal:%d\n", obj->lifeVal);
	fprintf(out, "test HeroData magicUpperVal:%d\n", obj->magicUpperVal);
	fprintf(out, "test HeroData magicVal:%d\n", obj->magicVal);
	fprintf(out, "test HeroData pt._x:%d\tpt._y:%d\n", obj->pt._x, obj->pt._y);
	fprintf(out, "test HeroData attack:%d\n", obj->attack);
	fprintf(out, "test HeroData attkType:%d\n", obj->attkType);
	fprintf(out, "test HeroData atk_range:%d\n", obj->atk_range);
	fprintf(out, "test HeroData AttackAndDefense:%d\n", obj->AttackAndDefense);
	fprintf(out, "test HeroData sec_hurt:%d\n", obj->sec_hurt);
	fprintf(out, "test HeroData bufferCD:%d\n", obj->bufferCD);
	fprintf(out, "test HeroData hited:%d\n", obj->hited);
	fprintf(out, "test HeroData crit:%d\n", obj->crit);
	fprintf(out, "test HeroData dodge:%d\n", obj->dodge);
	fprintf(out, "test HeroData tenacity:%d\n", obj->tenacity);
	fprintf(out, "test HeroData outratio:%d\n", obj->outratio);
	fprintf(out, "test HeroData inratio:%d\n", obj->inratio);
	fprintf(out, "test HeroData attackratio:%d\n", obj->attackratio);
	fprintf(out, "test HeroData defenseratio:%d\n", obj->defenseratio);
	fprintf(out, "test HeroData party:%s\n", obj->party);
	fprintf(out, "test HeroData five_elements_value:%d\n", obj->five_elements_value);	
	fprintf(out, "test HeroData outattack:%d\n", obj->outattack);
	fprintf(out, "test HeroData inattack:%d\n", obj->inattack);
	fprintf(out, "test HeroData outdefense:%d\n", obj->outdefense);
	fprintf(out, "test HeroData indefense:%d\n", obj->indefense);
	fprintf(out, "test HeroData outhurt:%d\n", obj->outhurt);
	fprintf(out, "test HeroData inhurt:%d\n", obj->inhurt);

	if(fclose(out) != 0){
		fprintf(stderr, "fclose file error!\n");
		return -1;
	//	exit(EXIT_FAILURE);
	} 	

	return 0;

}
