#ifndef MYSTERIOUSBUSSINESS_CONFIG_H
#define MYSTERIOUSBUSSINESS_CONFIG_H
#include<string>
#include<vector>
using namespace std;

class MysteriousBussiness_Config
{
private:
		char stage[5];
		int number;
		vector<string> gen_goodsid;
		vector<int> gen_money;
		vector<int> gen_percent;
		int wnumber;
		vector<string> white_goodsid;
		int wpercent;
		int bnumber;
		vector<string> blue_goodsid;
		int bpercent;
		int pnumber;
		vector<string> purple_goodsid;
		int ppercent;
public:
		MysteriousBussiness_Config(char* _stage,int _number,vector<string> _gen_goodsid,vector<int> _gen_money,vector<int> _gen_percent,int _wnumber,vector<string> _white_goodsid,int _wpercent,int _bnumber,vector<string> _blue_goodsid,int _bpercent,int _pnumber,vector<string> _purple_goodsid,int _ppercent);
		char* getStage(void);
		int getNumber(void);
		vector<string> getGen_goodsid(void);
		vector<int> getGen_money(void);
		vector<int> getGen_percent(void);
		int getWnumber(void);
		vector<string> getWhite_goodsid(void);
		int getWpercent(void);
		int getBnumber(void);
		vector<string> getBlue_goodsid(void);
		int getBpercent(void);
		int getPnumber(void);
		vector<string> getPurple_goodsid(void);
		int getPpercent(void);
};
#endif

