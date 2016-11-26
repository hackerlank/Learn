#ifndef DROPLIST_CONFIGURATION_H
#define DROPLIST_CONFIGURATION_H
#include<iostream>
#include<string>
#include<map>
using namespace std;
class DropList_Configuration
{
private:  
	char stage[20];
	int percent;
	int drugper;
	int drugnum;
	// char drugid[1500];
	int toolper;
	int toolnum;
	// char toolid[1500];
	int wequipper;
	int wequipnum;
	// char wequipid[1500];
	int bequipper;
	int bequipnum;
	// char bequipid[1500];
	int pequipper;
	int pequipnum;
	// char pequipid[1500];
	int pkequipper;
	int pkequipnum;
	// char pkequipid[1500];
	int oequipper;
	int oequipnum;
	// char oequipid[1500];

	map<int,string> drop_goods_id;

public:
	DropList_Configuration(char* _stage,int _percent,int _drugper,int _drugnum,int _toolper,int _toolnum,
		int _wequipper,int _wequipnum,int _bequipper,int _bequipnum,int _pequipper,
		int _pequipnum,int _pkequipper,int _pkequipnum,int _oequipper,
		int _oequipnum,map<int,string> _drop_goods_id);
	char* getstage(void);
	int getpercent(void);
	int getdrugper(void);
	int getdrugnum(void);
	// char* getdrugid(void);
	int gettoolper(void);
	int gettoolnum(void);
	// char* gettoolid(void);
	int getwequipper(void);
	int getwequipnum(void);
	// char* getwequipid(void);
	int getbequipper(void);
	int getbequipnum(void);
	// char* getbequipid(void);
	int getpequipper(void);
	int getpequipnum(void);
	// char* getpequipid(void);
	int getpkequipper(void);
	int getpkequipnum(void);
	// char* getpkequipid(void);
	int getoequipper(void);
	int getoequipnum(void);
	// char* getoequipid(void);
	map<int,string> getdropgoodsid(void);

};
#endif