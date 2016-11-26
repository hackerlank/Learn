#include"five_configuration.h"
Five_Configuration::Five_Configuration(string _id,int _gold,int _wood,int _water,int _fire,int _soil)
{
	id=_id;
	gold=_gold;
	wood=_wood;
	water=_water;
	fire=_fire;
	soil=_soil;
}
int Five_Configuration::getgold(void)
{
	return gold;
}
int Five_Configuration::getwood(void)
{
	return wood;
}
int Five_Configuration::getwater(void)
{
	return water;
}
int Five_Configuration::getfire(void)
{
	return fire;
}
int Five_Configuration::getsoil(void)
{
	return soil;
}
