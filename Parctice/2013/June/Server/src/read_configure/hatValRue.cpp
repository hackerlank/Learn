#include"hatValRue.h"
HatValRue::HatValRue(double _hatInRag,double _genHitPer,double _sklHitPer,double _proLosPer,double _friHitGan,double _chageAir,double _hatUpVal,double _redueValPer,int _hatRage)
{
	hatInRag = _hatInRag;       
	genHitPer = _genHitPer ;      
	sklHitPer = _sklHitPer;	
	proLosPer = _proLosPer;		
	friHitGan =  _friHitGan;       
	chageAirPer = _chageAir;        
	hatUpVal = _hatUpVal;         
	redueValPer = _redueValPer;   
	hatRage = _hatRage;
}

double HatValRue::getHatInRag(void)
{
	return hatInRag;
}

int HatValRue::getHatRage(void)
{
	return hatRage;
}
double HatValRue::getGenHitPer(void)
{
	return genHitPer;
}
double HatValRue::getSklHitPer(void)
{
	return sklHitPer;
}
double HatValRue::getProLosPer(void)
{
	return proLosPer;
}
double HatValRue::getFriHitGan(void)
{
	return friHitGan;
}

double HatValRue::getChageAirPer(void)
{
	return chageAirPer;
}

double HatValRue::getHatUpVal(void)
{
	return hatUpVal;
}
double HatValRue::getRedueValPer(void)
{
	return redueValPer;
}
