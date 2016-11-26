/*	背包类 BAG
*	制作:jolly
*	功能:捡取物品的位置判断,以及保存已捡起的物品信息
*
*	日期:2012,6,21
*/
#include"bag.h"
// extern map<string,Ointment *> id_to_ointment;
extern map<string,Equip_config*>id_to_equip;
extern map<string,Goods_Config*> id_to_cl;
extern map<string,Goods_Config*> id_to_dj;

extern int sock_fd;
using namespace std;
Bag::Bag(void)	//初始化背包
{	
	bagdata.bagnum=40;
	bagdata.expandNeedGold=1;
}

Bag::Bag(BagData _bagdata)
{
	bagdata=_bagdata;
} 

Bag::~Bag(void)
{
	trade_goods.clear();
	{
		std::vector<Trade_Goods> tmp;   
		trade_goods.swap(tmp);  
	}
	trade_index.clear();
	{
		std::vector<int> tmp;   
		trade_index.swap(tmp); 
	}
}

int Bag::getExpandNeedGold(void)
{
	return bagdata.expandNeedGold;
}

void Bag::setExpandNeedGold(int _expandNeedGold)
{
	bagdata.expandNeedGold=_expandNeedGold;
}

int Bag::get_goods_num(int index)
{
	if((index<0)||(index>=(bagdata.bagnum)))//tory modify 2012.12.10
	{
		return 0;
	}
	return bagdata.baggoodsdata[index].num;
}

int Bag::isExist(char* goodsid,int maxNum)
{
	int i=0;
	for (i=0;i<bagdata.bagnum;i++)
	{
		if (test(i,goodsid))
		{
			int num=getGridNum(i);
			if (num<maxNum)
			{
				return i;
			}
		}
	}
	i=getNextGoodsIndex();
	return i;
}

void Bag::saveGoodsInGrid(char* goodsid,int index,int num)
{
	strncpy(bagdata.baggoodsdata[index].goodsid,goodsid,sizeof(bagdata.baggoodsdata[index].goodsid));
	bagdata.baggoodsdata[index].num=num;	
}

bool Bag::finishTask(int num,int index)
{	
	int used=bagdata.baggoodsdata[index].num=bagdata.baggoodsdata[index].num-num;	
	if (used<0)
	{		
		return false;
	}
	else if (used==0)
	{
		initGrid(index);
		return true;	
	}		
	else
	{
		bagdata.baggoodsdata[index].num=used;
		return true;
	}	
}

int Bag::searchIndex(char* identity)				//根据物品id查找所在的id
{	
	int i;
	for (i=0;i<bagdata.bagnum;i++)
	{
		if (strcmp(bagdata.baggoodsdata[i].goodsid,identity)==0)
		{
			return i;
		}			
	}		
	return i;
}

int Bag::getBagNum(void)	//获取背包格子数量
{
	return bagdata.bagnum;
}

void Bag::setBagNum(int _bagnum)	//设置背包格子数量
{
	bagdata.bagnum=_bagnum;
}

int Bag::getNextGoodsIndex(void)	//取得下一个物品在全部栏中的位置
{
	int i;
	for (i=0;i<bagdata.bagnum;i++)
	{
		if(bagdata.baggoodsdata[i].num==0)
		{			
			return i;
		}			
	}		
	return i;
}

void Bag::initGrid(int index,int flag)						//初始化格子
{	
	strncpy(bagdata.baggoodsdata[index].goodsid,"0",sizeof(bagdata.baggoodsdata[index].goodsid));
	bagdata.baggoodsdata[index].num=0;
}

int Bag::remainGridNum(void)						//剩余的背包格子数
{
	int num=0;	
	cout<<"bagdata.bagnum:"<<bagdata.bagnum<<endl;
	for (int i=0;i<bagdata.bagnum;i++)
	{
		if (bagdata.baggoodsdata[i].num==0)
		{
			num++;
		}
	}
	return num;
}

bool Bag::drag(int _initindex,int _finalindex,char* initgoodsid,char* finalgoodsid)
{ 
	int initindex=_initindex;
	int finalindex=_finalindex;
	int itemp;
	if (initindex>bagdata.bagnum||finalindex>bagdata.bagnum||initindex<0||finalindex<0)
	{
		return false;
	}
	else
	{		
		if (test(initindex,initgoodsid)&&test(finalindex,finalgoodsid))
		{			
			if (strcmp(finalgoodsid,"0")==0)
			{
				strncpy(bagdata.baggoodsdata[finalindex].goodsid,initgoodsid,sizeof(bagdata.baggoodsdata[finalindex].goodsid));
				strncpy(bagdata.baggoodsdata[initindex].goodsid,finalgoodsid,sizeof(bagdata.baggoodsdata[initindex].goodsid));					
				bagdata.baggoodsdata[finalindex].num=bagdata.baggoodsdata[initindex].num;
				bagdata.baggoodsdata[initindex].num=0;
				return true;
			}
			else
			{
				int type=getGoodsType(initgoodsid);
				if (strcmp(initgoodsid,finalgoodsid)==0&&type==getGoodsType(finalgoodsid))
				{
					int repeat;
					if (type==0)
					{
						cout<<"jolly:goodstype is error bag 873"<<endl;
					}
					else if (type==1)
					{
						repeat=1;
					}
					else if (type==4)
					{				
						map<string,Goods_Config*>::iterator cl_it;
						cl_it=id_to_cl.find(initgoodsid);
						if (cl_it==id_to_cl.end())
						{
							cout<<"jolly:According  to the goodsid can't find the goods in warehouse_operator 120"<<endl;
						}
						else
						{
							Goods_Config *goods=cl_it->second;
							repeat=goods->getRepeat();
						}
					}
					else 
					{
						map<string,Goods_Config*>::iterator dj_it;
						dj_it=id_to_dj.find(initgoodsid);
						if (dj_it==id_to_dj.end())
						{
							cout<<"jolly:According th the goodsid can't find the goods in warehouse_operator 134"<<endl;
						}
						else
						{
							Goods_Config *goods=dj_it->second;
							repeat=goods->getRepeat();
						}
					} 
					int number=bagdata.baggoodsdata[initindex].num+bagdata.baggoodsdata[finalindex].num;		
					if (number<=repeat)
					{
						bagdata.baggoodsdata[finalindex].num=number;
						bagdata.baggoodsdata[initindex].num=0;
						strncpy(bagdata.baggoodsdata[initindex].goodsid,"0",sizeof(bagdata.baggoodsdata[initindex].goodsid));
						return true;
					}
					else
					{
						bagdata.baggoodsdata[finalindex].num=repeat;
						bagdata.baggoodsdata[initindex].num=number-repeat;
						return true;
					}		
				}
				else
				{	
					strncpy(bagdata.baggoodsdata[finalindex].goodsid,initgoodsid,sizeof(bagdata.baggoodsdata[finalindex].goodsid));
					strncpy(bagdata.baggoodsdata[initindex].goodsid,finalgoodsid,sizeof(bagdata.baggoodsdata[initindex].goodsid));					
					itemp=bagdata.baggoodsdata[initindex].num;
					bagdata.baggoodsdata[initindex].num=bagdata.baggoodsdata[finalindex].num;
					bagdata.baggoodsdata[finalindex].num=itemp;
					return true;
				}
			}
		}
		else
		{
			cout<<"jolly: goods test error bag.cpp 936"<<endl;
			return false;
		}
	}
}

void Bag::beforeArrang(void)
{
	int type;
	for (int i=0;i<bagdata.bagnum;i++)
	{
		char* identity=getIdentity(i);
		type=getGoodsType(identity);
		int repeat;
		if (type==4)
		{
			map<string,Goods_Config*>::iterator it;
			it=id_to_cl.find(identity);
			if (it==id_to_cl.end())
			{
				cout<<"jolly:According to the identity can't find cl bag 478"<<endl;
			}
			else
			{
				repeat=it->second->getRepeat();
			}
		}
		else if (type==2||type==3)
		{
			map<string,Goods_Config*>::iterator it;
			it=id_to_dj.find(identity);
			if (it==id_to_dj.end())
			{
				cout<<"jolly:According to the identity can't find dj bag 492"<<endl;
			}
			else
			{
				repeat=it->second->getRepeat();
			}
		}
		int number=getGridNum(i);
		if (repeat!=1&&number<repeat)
		{
			for (int j=i+1;j<bagdata.bagnum;j++)
			{
				char* tarIdentity=getIdentity(j);
				int tarNumber=getGridNum(j);
				if (strcmp(identity,tarIdentity)==0&&tarNumber<repeat)
				{
					int totalNumber=tarNumber+number;
					if (totalNumber>repeat)
					{
						bagdata.baggoodsdata[i].num=totalNumber-repeat;
						bagdata.baggoodsdata[j].num=repeat;
					}
					else
					{						
						bagdata.baggoodsdata[j].num=repeat;
						initGrid(i);
					}
				}
			}
		}
	}
}

bool Bag::bagExpand(int num)
{
	bagdata.bagnum=bagdata.bagnum+num;
}

char* Bag::getIdentity(int index)
{
	if((index<0) || (index>=sizeof(bagdata.baggoodsdata))) //tory add 2012.12.10
	{
		return "";
	}else{
		return bagdata.baggoodsdata[index].goodsid;
	}
}

int Bag::getGoodsNum(char* goodsid)					//根据物品id查找物品数量
{
	int _num=0;
	for (int i=0;i<bagdata.bagnum;i++)
	{
		if (strcmp(goodsid,bagdata.baggoodsdata[i].goodsid)==0)
		{
			_num=_num+bagdata.baggoodsdata[i].num;
		}
	}
	return _num;
}

bool Bag::bagIsFull(int _willUse)						//判断背包是否已满
{
	cout<<"in bagIsFull"<<endl;
	int _remain=remainGridNum();
	if (_remain<_willUse)
	{
		char msg[50];
		memset(msg,'\0',50);
		sprintf(msg,"9,%d,%d",BAG_FULL,FAILED);
		send_msg(sock_fd,msg);
		return true;
	}
	else
	{
		return false;
	}
}


bool Bag::addGoods(char* identity,int index,int num)
{
	strncpy(bagdata.baggoodsdata[index].goodsid,identity,sizeof(bagdata.baggoodsdata[index].goodsid));	
	bagdata.baggoodsdata[index].num+=num;
}

bool Bag::testNumber(int index,int number)
{
	if (index<0)
	{
		return false;
	}
	else if (index>bagdata.bagnum)
	{
		return false;
	}
	else
	{
		if (bagdata.baggoodsdata[index].num>=number)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
	
bool Bag::test(int index, const char* identity)
{
	if (index<0)
	{
		cout<<"index error in bag.cpp fuction test 396 and index:"<<index<<endl;
		return false;
	}
	else if (index>bagdata.bagnum)
	{
		cout<<"index is bigger than bagdata.bagnum in bag.cpp 401"<<endl;
		return false;
	}
	else
	{			
		// cout<<"&&&&&&&&&&&&&&&&&&&  "<<bagdata.baggoodsdata[index]<<endl;
		// cout<<"&&&&&&&&&&&&&&&&&&&  "<<identity<<endl;
		if (strcmp(bagdata.baggoodsdata[index].goodsid,identity)==0)
		{
			return true;
		}
		else
		{
			// cout<<"index:"<<index<<"           identity:"<<identity<<"                    not suit   goodsid::"<<bagdata.baggoodsdata[index].goodsid<<endl;
			return false;
		}
	}
}

/*交易相关函数 start*/
//将背包中的物品拖动到交易界面上
bool Bag::putOnTradeTable(char* goodsid,int index_bag)
{
	if (test(index_bag,goodsid))
	{
		trade_index.push_back(index_bag);
		lockIndex.insert(index_bag);
		return true;
	}
	else
	{
		return false;
	}
}
	
//某些操作需要锁定物品索引
void Bag::goodsLockIndex(int index)
{
	lockIndex.insert(index);
}

//解锁某些物品
void Bag::goodsUnlockIndex(int index)
{
	set<int>::iterator it;
	it=lockIndex.find(index);
	if (it!=lockIndex.end())
	{
		lockIndex.erase(it);
	}
}

//将交易界面上的物品拖到背包中
bool Bag::takeOffTradeTable(int index_bag)
{
	if (!trade_index.empty())
	{
		vector<int>::iterator it;
		for (it=trade_index.begin();it!=trade_index.end();it++)
		{
			if (*it==index_bag)
			{
				break;
			}
		}
		// cout<<*it<<endl;
		if(it == trade_index.end())
		{
			return false;
		}
		trade_index.erase(it);
		return true;
	}
	else
	{
		cout<<"bag error------------1010------------------"<<endl;
		return false;
	}	
}
	
//交易成功,返回交易的物品下标容器
vector<int> Bag::tradeSuccessReturnIndex(void)
{
	return trade_index;
}
int Bag::getTradeIndexSize(void)
{
	return trade_index.size();
}
	
//交易失败,交易栏中的物品都回到背包中
void Bag::tradeFailed(void)
{
	trade_goods.clear();
	{
		std::vector<Trade_Goods> tmp;   
		trade_goods.swap(tmp);  
	}
	trade_index.clear();
	{
		std::vector<int> tmp;   
		trade_index.swap(tmp); 
	}
	lockIndex.clear();
}

int Bag::getTradeGoodsSize(void)
{
	return trade_goods.size();
}

vector<Trade_Goods> Bag::getTrade_Goods(void)
{
	return trade_goods;
}

/*交易相关函数 end*/

void Bag::setGridNum(int _num,int index)				//设置该格子的物品数量
{
	bagdata.baggoodsdata[index].num=_num;
}

int Bag::getGridNum(int index)
{
	if (index<0)
	{
		return 0;
	}
	else if (index>bagdata.bagnum)
	{
		return 0;
	}
	else
	{
		return bagdata.baggoodsdata[index].num;
	}
}

bool Bag::isLocking(int index)			//若被锁定 则返回true;	
{
	if (lockIndex.empty())
	{
		return false;
	}
	else
	{
		set<int>::iterator it;
		it=lockIndex.find(index);
		if (it==lockIndex.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void Bag::msg_expand_success(char *msg,int len)
{	
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"9,%d,%d,%d",EXPAND_BAG,SUCCESS,bagdata.bagnum);
}

BagData Bag::getMemStruct(void)
{
	return bagdata;
}

int Bag::showBagData(BagData *obj, char *outfile)
{
	// FILE *out;
	// if((out = fopen(outfile, "w+")) == NULL){
		// fprintf(stderr, "fopen file %s error!\n", outfile);
		// exit(EXIT_FAILURE);
	// }
 	// fprintf(out, "test BagData bagdata.bagnum:%d\n", obj->bagnum);
	// fprintf(out, "test BagData totaltype:");
	// for (int i=0;i<bagdata.bagnum;i++)
	// {
		// fprintf(out, "%d  ", obj->totaltype[i]);
	// }
	// fprintf(out, "\ntest BagData bagdata.baggoodsdata:");
	// for (int i=0;i<bagdata.bagnum;i++)
	// {
		// fprintf(out, "%d  ", obj->bagdata.baggoodsdata[i]);
	// }
	// fprintf(out, "test BagData bagdata.expandNeedGold:%d\n", obj->expandNeedGold);
	// fprintf(out, "test BagData goodsids:%s\n", obj->goodsids);

	// if(fclose(out) != 0){
		// fprintf(stderr, "fclose file error!\n");
		// exit(EXIT_FAILURE);
	// } 	
	
	// return 0;
}

void Bag::msg_drag_success(char *msg,int len,int initindex,int finalindex,char* firstgoodsid,char* secondgoodsid)
{	
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"9,%d,%d,%d,%s,%d,%d,%s,%d",BAG_DRAG,SUCCESS,initindex,firstgoodsid,getGridNum(initindex),finalindex,secondgoodsid,getGridNum(finalindex));
}
	
void Bag::msg_drag_failed(char *msg,int len)
{
	if (msg == NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d",9,BAG_DRAG,FAILED);
}

void Bag::setMemStruct(BagData _bagdata)
{
	bagdata=_bagdata;
}

BagGoodsData Bag::getBagGoodsData(int _index)
{
	if((_index<0)||(_index>bagdata.bagnum))
	{
		BagGoodsData newBagGoodsData; 
		return  newBagGoodsData;
	}
	return bagdata.baggoodsdata[_index];	
}

void Bag::setGridData(BagGoodsData _baggoodsdata,int _index)
{
	bagdata.baggoodsdata[_index]=_baggoodsdata;
}

//给出装备的实例id,查找装备在背包中的索引
int Bag::getEquipIndex(char *identity)
{
	for (int i=0;i<bagdata.bagnum;i++)
	{
		if (strcmp(bagdata.baggoodsdata[i].goodsid,identity)==0)
		{
			return i;
		}
	}
	return -1;
}

set<int> Bag::getLockIndex(void)
{
	return lockIndex;
}