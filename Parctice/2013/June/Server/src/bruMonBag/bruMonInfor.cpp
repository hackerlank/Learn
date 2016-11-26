/************************************************************
	文件名：bruMonInfor.cpp
	文件作用：实现类BruMonInfor类的方法
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#include"bruMonInfor.h"
BruMonInfor::BruMonInfor(char *_typeId,int _brushed_count = 0,int _sum = 0,int _alive_count = 0)
{
	typeId = _typeId;
	brushed_count = _brushed_count;
	sum = _sum;
	alive_count = _alive_count;
}

/*获得此类型现存活的怪的id集合*/
set<string>& BruMonInfor::getLivMonId(void)
{
	return liveMonId;
}

/*获得此类型即将涮出怪的id集合*/
set<string>& BruMonInfor::getBushMonId(void)
{
	return bushMonId;
}

/*获得此类型怪物id*/
char* BruMonInfor::getTyId(void)
{
	return const_cast<char *>(typeId.c_str());
}

/*获得此类型怪物待涮出数目*/
int BruMonInfor::getBrshCnt(void)
{
	return brushed_count;
}

/*获得此类型怪物总数目*/
int BruMonInfor::getSumCnt(void)
{
	return sum;
}

/*得到活着的怪的数目*/	
int BruMonInfor::getLivCnt(void)
{
	return alive_count;
}

/*设置将要刷怪的数目*/
void BruMonInfor::setBrshCnt(int _num)
{
	brushed_count = _num;
}

/*设置总怪的数目*/	
void BruMonInfor::setSumCnt(int _num)
{
	sum = _num;
}

/*设置活着的怪的数目*/	
void BruMonInfor::setLivCnt(int _num)
{
	alive_count = _num;
}

/*获得死亡的怪的id容器引用*/
set<string>& BruMonInfor::getDieMonId(void)
{
	return dieMonId;
}


//把死亡的怪的id放入死亡容器中
// void BruMonInfor::InputDieId(char *monId)
// {
	// dieMonId.insert(monId);	
	// alive_count -= 1;
// }


/*把死亡的怪的id放入死亡容器中(在怪物死亡函数里面调用）*/
void BruMonInfor::InputDieId(char *monId)
{
	set<string>::iterator liv_it;
	liv_it = liveMonId.find(monId);
	if(liv_it == liveMonId.end())
	{
		return;
	}
	liveMonId.erase(liv_it);
	dieMonId.insert(monId);	
	alive_count -= 1;
}

/*把活着的怪的id放入存活容器中*/
void BruMonInfor::InputLiveId(char* monLivId)
{
	set<string>::iterator bru_it;
	bru_it = bushMonId.find(monLivId);
	if(bru_it == bushMonId.end())
	{
		return;
	}
	bushMonId.erase(bru_it);	
	liveMonId.insert(monLivId);
	alive_count += 1;
}

//把活着的怪的id放入存活容器中
// void BruMonInfor::InputLiveId(char* monLivId)
// {
	// liveMonId.insert(monLivId);
	// alive_count += 1;
// }

/*把要刷怪的id放入刷怪容器中*/
void BruMonInfor::InputBruId(char* monBruId)
{
	set<string>::iterator die_it;
	die_it = dieMonId.find(monBruId);
	if(die_it == dieMonId.end())
	{
		return;
	}
	dieMonId.erase(die_it);
	bushMonId.insert(monBruId);
	sum += 1;
}

/*把要刷怪的id放入刷怪容器中(主要在地图配置文件里面调用）*/
void BruMonInfor::inputBruId(char* monBruId)
{
	bushMonId.insert(monBruId);
	sum += 1;
}

/*把要死亡容器的id放入刷怪容器中*/
void BruMonInfor::exchage(void)       
{
	set<string>::iterator die_it;
	for(die_it = dieMonId.begin();die_it != dieMonId.end();die_it++)
	{
		string dieId = *die_it;
		bushMonId.insert(*die_it);
	}
	dieMonId.clear();
}

/*把要即将要刷的怪的id放入参数vector中*/
void BruMonInfor::outBruMonId(vector<string>& bruId,int _num)
{
	int i = 0;
	if(_num == 0)
	{
		_num = bushMonId.size();
	}		
	set<string>::iterator bru_it;
	for(bru_it = bushMonId.begin();bru_it != bushMonId.end() && i < _num;bru_it++,i++)
	{
		string id = *bru_it;
		bruId.push_back(id);		
	}
	bushMonId.erase(bushMonId.begin(),bru_it);
}

/*把刚刷好的的怪的id（即参数vector）放入存活容器中*/
void BruMonInfor::InputLiveId(vector<string>& bruId)
{
	int num_arr = bruId.size();
	int i ;
	for(i = 0;i < num_arr;i++)
	{
		liveMonId.insert(bruId[i]);
	}
	alive_count += i;
}

/*析构函数*/		
BruMonInfor::~BruMonInfor(void)
{
	liveMonId.clear();
	bushMonId.clear();
	dieMonId.clear();
}

/*取出所有即将涮出的怪物id*/
void BruMonInfor::outBruMonIdAll(vector<string>& bruId)     
{
	set<string>::iterator bru_it;
	for(bru_it = bushMonId.begin();bru_it != bushMonId.end() ;bru_it++)
	{
		string id = *bru_it;
		bruId.push_back(id);		
	}
	bushMonId.clear();
}

/*测试打印死亡容器内容*/
void BruMonInfor::testPrintDie(void)
{
	cout<<"begin test Die container:"<<endl;
	set<string>::iterator die_it;
	for(die_it = dieMonId.begin();die_it != dieMonId.end();die_it++)
	{
		cout<<"monster Id:"<<*die_it<<endl;
	}
	cout<<"end test Die container:"<<endl;
}

/*测试打印存活容器内容*/
void BruMonInfor::testPrintLive(void)
{
	cout<<"begin test live container:"<<endl;
	set<string>::iterator live_it;
	for(live_it = liveMonId.begin();live_it != liveMonId.end();live_it++)
	{
		cout<<"monster Id:"<<*live_it<<endl;
	}
	cout<<"end test live container:"<<endl;
}	

/*测试打印将要涮出容器内容*/
void BruMonInfor::testPrintBush(void)
{
	cout<<"begin test brush container:"<<endl;
	set<string>::iterator brush_it;
	for(brush_it = bushMonId.begin();brush_it != bushMonId.end();brush_it++)
	{
		cout<<"monster Id:"<<*brush_it<<endl;
	}
	cout<<"end test brush container:"<<endl;
}	

/*把以存活怪物放进待刷容器中*/
void BruMonInfor::exchageLve(void)
{
	set<string>::iterator liv_it;
	for(liv_it = liveMonId.begin();liv_it != liveMonId.end();liv_it++)
	{
		string livId = *liv_it;
		bushMonId.insert(livId);
	}
	liveMonId.clear();
}
	
/*复原brush*/
void BruMonInfor::initBrush(void)
{
	exchage();
	exchageLve();
	brushed_count = 0;	           
	alive_count = 0;
	sum = bushMonId.size();       
}

/*单插入存活容器中*/
void BruMonInfor::inputOneLve(char* monLivId)
{
	set<string>::iterator bru_it;
	bru_it = liveMonId.find(monLivId);
	if(bru_it != liveMonId.end())
	{
		return;
	}	
	liveMonId.insert(monLivId);
	alive_count += 1;
}

/*设置存活容器*/
void BruMonInfor::setLiveMonId(set<string> &_liveMonId)
{
	liveMonId = _liveMonId;
}

/*设置存活容器*/
void BruMonInfor::setDieMonId(set<string> &_dieMonId)
{
	dieMonId = _dieMonId;
}

/*设置刷怪容器*/
void BruMonInfor::setBushMonId(set<string> &_bushMonId)
{
	bushMonId = _bushMonId;
}


/*设置刷怪容器*/
BruMonInfor* BruMonInfor::copyMonBru(void)
{
	BruMonInfor* newMonBru;
	newMonBru = NULL;

	newMonBru = new BruMonInfor(const_cast<char *>(typeId.c_str()),brushed_count,sum,alive_count);
	newMonBru->setLiveMonId(liveMonId);
	newMonBru->setDieMonId(dieMonId);
	newMonBru->setBushMonId(bushMonId);
	return newMonBru;	
}