#include"mysteriousBussiness_config.h"
#include <string.h>
MysteriousBussiness_Config::MysteriousBussiness_Config(char* _stage,int _number,vector<string> _gen_goodsid,vector<int> _gen_money,vector<int> _gen_percent,int _wnumber,vector<string> _white_goodsid,int _wpercent,int _bnumber,vector<string> _blue_goodsid,int _bpercent,int _pnumber,vector<string> _purple_goodsid,int _ppercent)
{
	strncpy(stage,_stage,sizeof(stage));
	number=_number;
	gen_goodsid=_gen_goodsid;
	gen_money=_gen_money;
	gen_percent=_gen_percent;
	wnumber=_wnumber;
	white_goodsid=_white_goodsid;
	wpercent=_wpercent;
	bnumber=_bnumber;
	blue_goodsid=_blue_goodsid;
	bpercent=_bpercent;
	pnumber=_pnumber;
	purple_goodsid=_purple_goodsid;
	ppercent=_ppercent;
}

char* MysteriousBussiness_Config::getStage(void)
{
	return stage;
}

int MysteriousBussiness_Config::getNumber(void)
{
	return number;
}

vector<string> MysteriousBussiness_Config::getGen_goodsid(void)
{
	return gen_goodsid;
}

vector<int> MysteriousBussiness_Config::getGen_money(void)
{
	return gen_money;
}

vector<int> MysteriousBussiness_Config::getGen_percent(void)
{
	return gen_percent;
}

int MysteriousBussiness_Config::getWnumber(void)
{
	return wnumber;
}

vector<string> MysteriousBussiness_Config::getWhite_goodsid(void)
{
	return white_goodsid;
}

int MysteriousBussiness_Config::getWpercent(void)
{
	return wpercent;
}

int MysteriousBussiness_Config::getBnumber(void)
{
	return bnumber;
}

vector<string> MysteriousBussiness_Config::getBlue_goodsid(void)
{
	return blue_goodsid;
}

int MysteriousBussiness_Config::getBpercent(void)
{
	return bpercent;
}

int MysteriousBussiness_Config::getPnumber(void)
{
	return pnumber;
}

vector<string> MysteriousBussiness_Config::getPurple_goodsid(void)
{
	return purple_goodsid;
}

int MysteriousBussiness_Config::getPpercent(void)
{
	return ppercent;
}
