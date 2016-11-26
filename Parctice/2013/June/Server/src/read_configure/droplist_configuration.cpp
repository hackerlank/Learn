#include "droplist_configuration.h"
#include <string.h>
DropList_Configuration::DropList_Configuration(char* _stage,int _percent,int _drugper,int _drugnum,
												int _toolper,int _toolnum,
												int _wequipper,int _wequipnum,int _bequipper,
												int _bequipnum,int _pequipper,int _pequipnum,
												int _pkequipper, int _pkequipnum,
												int _oequipper,int _oequipnum,
												map<int,string> _drop_goods_id)
{
	// int len;
	// len = strlen(_stage);
	// stage = new char[len+1];
	strncpy(stage,_stage,sizeof(stage));
	// stage[len]='\0';
	
	percent=_percent;
	drugper=_drugper;
	drugnum=_drugnum;
	// strncpy(drugid,_drugid,sizeof(drugid));
	toolper=_toolper;
	toolnum=_toolnum;
	// strncpy(toolid,_toolid,sizeof(toolid));
	wequipper=_wequipper;
	wequipnum=_wequipnum;
	// strncpy(wequipid,_wequipid,sizeof(wequipid));
	bequipper=_bequipper;
	bequipnum=_bequipnum;
	// strncpy(bequipid,_bequipid,sizeof(bequipid));
	pequipper=_pequipper;
	pequipnum=_pequipnum;
	// strncpy(pequipid,_pequipid,sizeof(pequipid));
	pkequipper=_pkequipper;
	pkequipnum=_pkequipnum;
	// strncpy(pkequipid,_pkequipid,sizeof(pkequipid));
	oequipper=_oequipper;
	oequipnum=_oequipnum;
	// strncpy(oequipid,_oequipid,sizeof(oequipid));
	drop_goods_id=_drop_goods_id;

}

char* DropList_Configuration::getstage(void)
{
	return stage;
}

int DropList_Configuration::getpercent(void)
{
	return percent;
}

int DropList_Configuration::getdrugper(void)
{
	return drugper;
}

int DropList_Configuration::getdrugnum(void)
{
	return drugnum;
}

// char* DropList_Configuration::getdrugid(void)
// {
	// return drugid;
// }

int DropList_Configuration::gettoolper(void)
{
	return toolper;
}

int DropList_Configuration::gettoolnum(void)
{
	return toolnum;
}

// char* DropList_Configuration::gettoolid(void)
// {
	// return toolid;
// }

int DropList_Configuration::getwequipper(void)
{
	return wequipper;
}

int DropList_Configuration::getwequipnum(void)
{
	return wequipnum;
}

// char* DropList_Configuration::getwequipid(void)
// {
	// return wequipid;
// }

int DropList_Configuration::getbequipper(void)
{
	return bequipper;
}

int DropList_Configuration::getbequipnum(void)
{
	return bequipnum;
}

// char* DropList_Configuration::getbequipid(void)
// {
	// return bequipid;
// }

int DropList_Configuration::getpequipper(void)
{
	return pequipper;
}

int DropList_Configuration::getpequipnum(void)
{
	return pequipnum;
}

// char* DropList_Configuration::getpequipid(void)
// {
	// return pequipid;
// }

int DropList_Configuration::getpkequipper(void)
{
	return pkequipper;
}

int DropList_Configuration::getpkequipnum(void)
{
	return pkequipnum;
}

// char* DropList_Configuration::getpkequipid(void)
// {
	// return pkequipid;
// }
int DropList_Configuration::getoequipper(void)
{
	return oequipper;
}

int DropList_Configuration::getoequipnum(void)
{
	return oequipnum;
}

// char* DropList_Configuration::getoequipid(void)
// {
	// return oequipid;
// }
map<int,string> DropList_Configuration::getdropgoodsid(void)
{
	return drop_goods_id;
}

