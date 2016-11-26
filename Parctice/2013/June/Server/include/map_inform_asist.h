/************************************************************
	文件名：map_inform_asist.h
	文件作用：类Map_Inform类的辅助功能数据结构
	作者：chenzhen
	创建日期：2012.08.29
************************************************************/
#ifndef MAP_INFORM_ASIST_H
#define MAP_INFORM_ASIST_H
#include<string>
#include<set>
using namespace std;
/*刷怪批次结构体*/
typedef struct BruGro
{
	/*每批的怪物id*/
	set<string>monId;
	
	/*计数器，判断此批怪是否死完*/
	int ctn;
	
	BruGro(set<string> _monId)
	{
		monId = _monId;
		ctn = 0;
	}
	
	BruGro(const BruGro &bruGro)
	{
		monId = bruGro.monId;
		ctn = bruGro.ctn;
	}
	
	BruGro& operator= (const BruGro &bruGro)
	{
		monId = bruGro.monId;
		ctn = bruGro.ctn;
		
		return *this;
	}
	
	
	BruGro(void)
	{
		ctn = 0;
	}
	/*判断此批怪是否死完，真为死完*/
	bool judDieCtn(void)
	{
		return ctn >= monId.size();
	}
	/*自增*/
	void monDie(char *_monId)
	{
		set<string>::iterator set_it;
		if(_monId == NULL || strlen(_monId) == 0)
		{
			return;
		}
		set_it = monId.find(_monId);
		if(set_it == monId.end())
		{		
			return;
		}
		ctn++;
			
	}
	/*重置*/
	void init(void)
	{
		ctn = 0;
	}
	/*插入一个怪物id*/
	void inPut(string _monId)
	{
		monId.insert(_monId);	
	}
	
	/*测试刷怪容器*/
	void testPrint(void)
	{
		cout<<"test oneObject groupGruMonId begin:"<<endl;
		set<string>::iterator monId_it;
		cout<<"the num of the monsterId:"<<monId.size()<<endl;
		for(monId_it = monId.begin();monId_it != monId.end();monId_it++)
		{
			cout<<"monsterId:"<<*monId_it<<endl;
		}
		cout<<"test oneObject groupGruMonId end:"<<endl;
	}
}BruGro;


#endif