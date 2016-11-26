#include"mysteriousBussiness.h"
#include "command_other_function_all_over.h"
#include "my_time.h"
extern map<string,MysteriousBussiness_Config*> stage_to_mysteriousBussiness;
extern map<string,Equip_config*> id_to_equip;
extern struct timeval myTime;
MysteriousBussiness::MysteriousBussiness(void)
{
	mysteriousBussinessData.beginTime=myTime.tv_sec;
	mysteriousBussinessData.refreshMoney=10;
	mysteriousBussinessData.flag=0;
	// cout<<"!!!!!!!!!!!!!!!!!!!!!!       "<<mysteriousBussinessData.beginTime<<endl;
	// cout<<"!!!!!!!!!!!!!!!!!!!@@@@@@@@@@@@@@@@@@@@@@@@#######################"<<endl;
}

MysteriousBussiness::MysteriousBussiness(MysteriousBussinessData _mysteriousBussinessData)
{
	mysteriousBussinessData=_mysteriousBussinessData;
	// cout<<"||||||||||||||||||||||||||||||||     "<<mysteriousBussinessData.beginTime<<endl;
}

void MysteriousBussiness::refreshGoods(int level)
{
	// cout<<"111111111111111111111111111111111111111"<<endl;
	int stage=level/10;
	// cout<<"5555555555555555555555555555555     "<<stage<<endl;
	map<string,MysteriousBussiness_Config*>::iterator it;
	// for (it=stage_to_mysteriousBussiness.begin();it!=stage_to_mysteriousBussiness.end();it++)
	// {
		// cout<<"#####################  "<<it->first<<endl;
	// }
	it=stage_to_mysteriousBussiness.find(itos(stage));
	if (it==stage_to_mysteriousBussiness.end())
	{
		cout<<"jolly:MysteriousBussiness refresh error mysteriousBussiness.cpp 15"<<endl;
	}
	else
	{
		MysteriousBussiness_Config *mysteriousBussiness_config=it->second;
		int number=mysteriousBussiness_config->getNumber();
		vector<string> gen_goodsid=mysteriousBussiness_config->getGen_goodsid();	
		// vector<string>::iterator it;
		// for (it=gen_goodsid.begin();it!=gen_goodsid.end();it++)
		// {	
			// cout<<"     "<<*it<<endl;
		// }
		vector<int> gen_money=mysteriousBussiness_config->getGen_money();
		vector<int> gen_percent=mysteriousBussiness_config->getGen_percent();
		int wnumber=mysteriousBussiness_config->getWnumber();
		vector<string> white_goodsid=mysteriousBussiness_config->getWhite_goodsid();
		// for (it=white_goodsid.begin();it!=white_goodsid.end();it++)
		// {	
			// cout<<"!!!!!!! "<<*it<<endl;
		// }
		int wpercent=mysteriousBussiness_config->getWpercent();
		int bnumber=mysteriousBussiness_config->getBnumber();
		vector<string> blue_goodsid=mysteriousBussiness_config->getBlue_goodsid();
		// for (it=blue_goodsid.begin();it!=blue_goodsid.end();it++)
		// {	
			// cout<<"@@@@@@@@"<<*it<<endl;
		// }
		int bpercent=mysteriousBussiness_config->getBpercent();
		int pnumber=mysteriousBussiness_config->getPnumber();
		vector<string> purple_goodsid=mysteriousBussiness_config->getPurple_goodsid();
		// for (it=purple_goodsid.begin();it!=purple_goodsid.end();it++)
		// {	
			// cout<<" #######"<<*it<<endl;
		// }
		int ppercent=mysteriousBussiness_config->getPpercent();
		int loop;
		//srand(MY_TV_USEC);
		// string goodsid="";
		
		// cout<<"22222222222222222222222222222222222222222"<<endl;
		for (loop=0;loop<10;loop++)
		{
			int random=random_number(1,1000);
			int gen_max_per=number-1;
			// cout<<"!!!!!!!!!   "<<random<<"            "<<gen_percent[gen_max_per]<<"   "<<wpercent<<"   "<<bpercent<<"    "<<ppercent<<endl;
			if (random<=gen_percent[gen_max_per])
			{
				for (int i=0;i<number;i++)
				{
					if (random<gen_percent[i])
					{
						if (gen_goodsid[i].size()!=0)
						{
							strncpy(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid,gen_goodsid[i].c_str(),sizeof(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid));
							mysteriousBussinessData.mysteriousgoodsdata[loop].money=gen_money[i];
							mysteriousBussinessData.mysteriousgoodsdata[loop].flag=0;	
						}
						else
						{
							cout<<"jolly:no goods in mysteriousBussiness.cpp 56"<<endl;
						}
						break;
					}
				}
			}
			else if (random<=wpercent)
			{
				random=random_number(1,wnumber);
				if (white_goodsid[random-1].size()==0)
				{
					cout<<"jolly:whit equip id is error in mysteriousBussiness 67"<<endl;
				}
				else
				{
					map<string,Equip_config*>::iterator equip_it;
					equip_it=id_to_equip.find(white_goodsid[random-1]);
					if (equip_it==id_to_equip.end())
					{
						cout<<"jolly:According to the id can't find the equip in mysteriousBussiness 70"<<endl;
					}
					else
					{
						strncpy(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid,white_goodsid[random-1].c_str(),sizeof(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid));
						mysteriousBussinessData.mysteriousgoodsdata[loop].money=equip_it->second->getPrice();
						mysteriousBussinessData.mysteriousgoodsdata[loop].flag=0;	
					}					
				}				
			}
			else if (random<=bpercent)
			{
				random=random_number(1,bnumber);
				if (blue_goodsid[random-1].size()==0)
				{
					cout<<"jolly:whit equip id is error in mysteriousBussiness 67"<<endl;
				}
				else
				{
					map<string,Equip_config*>::iterator equip_it;
					equip_it=id_to_equip.find(blue_goodsid[random-1]);
					if (equip_it==id_to_equip.end())
					{
						cout<<"jolly:According to the id can't find the equip in mysteriousBussiness 70"<<endl;
					}
					else
					{
						strncpy(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid,blue_goodsid[random-1].c_str(),sizeof(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid));
						mysteriousBussinessData.mysteriousgoodsdata[loop].money=equip_it->second->getPrice();
						mysteriousBussinessData.mysteriousgoodsdata[loop].flag=0;	
					}					
				}	
			}
			else if (random<=ppercent)
			{
				random=random_number(1,pnumber);
				if (purple_goodsid[random-1].size()==0)
				{
					cout<<"jolly:whit equip id is error in mysteriousBussiness 67"<<endl;
				}
				else
				{
					map<string,Equip_config*>::iterator equip_it;
					equip_it=id_to_equip.find(purple_goodsid[random-1]);
					if (equip_it==id_to_equip.end())
					{
						cout<<"jolly:According to the id can't find the equip in mysteriousBussiness 70"<<endl;
					}
					else
					{
						strncpy(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid,purple_goodsid[random-1].c_str(),sizeof(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid));
						mysteriousBussinessData.mysteriousgoodsdata[loop].money=equip_it->second->getPrice();
						mysteriousBussinessData.mysteriousgoodsdata[loop].flag=0;	
					}					
				}	
			}
			if (isSameGoods(mysteriousBussinessData.mysteriousgoodsdata[loop].goodsid,loop))
			{
				loop--;
			}
		}
	}
}

void MysteriousBussiness::msg_mysteriousGoods(char* msg)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,sizeof(g_out_buf),"%d,%d,%d,%d",9,MYSTERIOUS_RETURN,14400+mysteriousBussinessData.beginTime-int(myTime.tv_sec),mysteriousBussinessData.refreshMoney);
	// snprintf(msg,sizeof(g_out_buf),"%d,%d,%d,%d",9,MYSTERIOUS_RETURN,60+mysteriousBussinessData.beginTime-int(myTime.tv_sec),mysteriousBussinessData.refreshMoney);
	// string msg="9";
	// string goodsid;
	// msg+=intTostring(MYSTERIOUS_RETURN);
	// cout<<mysteriousBussinessData.beginTime<<endl;
	// cout<<myTime.tv_sec<<endl;	
	// msg+=intTostring(28800+mysteriousBussinessData.beginTime-myTime.tv_sec);
	// msg+=intTostring(mysteriousBussinessData.refreshMoney);
	for (int i=0;i<10;i++)
	{
		snprintf(msg+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%s,%d,%d",mysteriousBussinessData.mysteriousgoodsdata[i].goodsid,mysteriousBussinessData.mysteriousgoodsdata[i].money,mysteriousBussinessData.mysteriousgoodsdata[i].flag);
		// goodsid=mysteriousBussinessData.mysteriousgoodsdata[i].goodsid;
		// msg=msg+","+goodsid;
		// msg+=intTostring(mysteriousBussinessData.mysteriousgoodsdata[i].money);
		// msg+=intTostring(mysteriousBussinessData.mysteriousgoodsdata[i].flag);
	}	
	// return msg;
}

void MysteriousBussiness::msg_mysteriousRefresh(char *msg)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,sizeof(g_out_buf),"%d,%d,%d",9,MYSTERIOUS_REFRESH,mysteriousBussinessData.refreshMoney);
	// string msg="9";
	// string goodsid;
	// msg+=intTostring(MYSTERIOUS_REFRESH);
	// msg+=intTostring(mysteriousBussinessData.refreshMoney);
	for (int i=0;i<10;i++)
	{
		snprintf(msg+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%s,%d,%d",mysteriousBussinessData.mysteriousgoodsdata[i].goodsid,mysteriousBussinessData.mysteriousgoodsdata[i].money,mysteriousBussinessData.mysteriousgoodsdata[i].flag);
	}	
	// return msg;
}

void MysteriousBussiness::refreshIncreaseMoney(void)
{	
	mysteriousBussinessData.refreshMoney+=5;
}

void MysteriousBussiness::setFlag(int _flag)
{
	// cout<<"---------------------------------------------"<<endl;
	cout<<_flag<<endl;
	// cout<<"---------------------------------------------"<<endl;
	mysteriousBussinessData.flag=_flag;
}

bool MysteriousBussiness::isTimerForRefresh(void)			//看到没到自动刷新的时间,若到了返回true 否则返回false;
{
	if (mysteriousBussinessData.flag==0)
	{
		mysteriousBussinessData.refreshMoney=10;
		// cout<<"truetruetruetruetruetruetruetruetruetruetruetruetruetruetrue"<<endl;
		return true;
	}
	else
	{
		// cout<<"falsefalsefalsefalsefalsefalsefalsefalsefalsefalsefalsefalsefalsefalse"<<endl;
		return false;
	}
}

void MysteriousBussiness::verifyFlag(void)				//通过时间验证flag的值
{
	if ((myTime.tv_sec-mysteriousBussinessData.beginTime)>14400)
	{	
		mysteriousBussinessData.flag=0;
		for (int i=0;mysteriousBussinessData.beginTime<=myTime.tv_sec;i++)
		{			
			mysteriousBussinessData.beginTime+=14400;
		}
		mysteriousBussinessData.beginTime-=14400;
	}
	// if ((myTime.tv_sec-mysteriousBussinessData.beginTime)>60)
	// {	
		// mysteriousBussinessData.flag=0;
		// for (int i=0;mysteriousBussinessData.beginTime<=myTime.tv_sec;i++)
		// {			
			// mysteriousBussinessData.beginTime+=60;
		// }
		// mysteriousBussinessData.beginTime-=60;
	// }
}

MysteriousBussinessData MysteriousBussiness::getMemStruct(void)
{
	return mysteriousBussinessData;
}

bool MysteriousBussiness::isSameGoods(char* goodsid,int loop)		//判断本次出现的物品是否与之前的相同,若相同则返回true
{
	for (int i=0;i<loop;i++)
	{
		if (strcmp(mysteriousBussinessData.mysteriousgoodsdata[i].goodsid,goodsid)==0)
		{
			return true;
		}
	}
	return false;
}

char* MysteriousBussiness::getIdentiy(int _index)
{
	return mysteriousBussinessData.mysteriousgoodsdata[_index].goodsid;
}

int MysteriousBussiness::getPrice(int _index)
{
	return mysteriousBussinessData.mysteriousgoodsdata[_index].money;
}

void MysteriousBussiness::setBuyFlag(int _flag,int _index)
{
	mysteriousBussinessData.mysteriousgoodsdata[_index].flag=_flag;
}

int MysteriousBussiness::getBuyFlag(int _index)
{
	return mysteriousBussinessData.mysteriousgoodsdata[_index].flag;
}

void MysteriousBussiness::setRefreshMoney(int _refreshMoney)
{
	mysteriousBussinessData.refreshMoney=_refreshMoney;
}

int MysteriousBussiness::getRefreshMoney(void)
{
	return mysteriousBussinessData.refreshMoney;
}