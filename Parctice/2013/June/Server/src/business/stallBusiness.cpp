#include"anyBusiness.h"
#include"commodity.h"

extern map<string ,PrivateStall> stall;  //heroId为键
extern map<string, Hero> heroId_to_pHero;
extern int sock_fd;



//摆摊
void createStall(char *buff)
{
	string heroId;
	string goodsId;
	PrivateStall *privateStall=new PrivateStall();
	//截取goodsId分别实例出商品放入摊位容器
	for()
	{
		Commodity stallCommodity;
		stallCommodity.num;
		stallCommodity.money;
		stallCommodity.comId;
		privateStall->container.insert(pair<string ,Commodity>(goodsId,stallCommodity));
	}
	stall.insert(pair<string ,*PrivateStall>(heroId,privateStall));

}
//他人买入
void stallBusiness(char *buff)
{
	string buyHeroId;  //买入玩家id
	string buyGoodsId; //买入物品id
	int buyGoodsNum; //买入物品数量
	string sellerId; //卖家id
	extern map<string, Hero*> heroId_to_pHero;
	
	map<string ,PrivateStall *>::iterator stallIter=stall.find(sellerId);
	if(stallIter==stall.end())
	{
		cout<<"there is no this stall in  stallBusiness.cpp :34"<<endl;
		return;
	}
	
	map<string,StallCommodity>container; //商品容器
	set<AuctionCommodity>record; //售出记录
	PrivateStall *privateStall=stallIter->second;
	set<StallCommodity > ::iterator iterContainer=privateStall->container.find(buyGoodsId);
	if(iterContainer==privateStall->container.end())
	{
		cout<<"there is no this Commodity in  stallBusiness.cpp :45"<<endl;
		return;
	}
	StallCommodity stallCommodity=iterContainer->second();//想要买入商品
	map<string, Hero *>::iterator heroIter=heroId_to_pHero.find(buyHeroId);
	if(heroIter==heroId_to_pHero.end())
	{
		cout<<"there is no buyer in  stallBusiness.cpp :52"<<endl;
		return;
	}
	Hero *buyer=heroIter->second;//买入者
		//玩家消费
	if(goods->boundGold)
	{
		if(hero->money->useBoundGold())
		{
			//交易成功
			//将卖家背包内物品转移至买家背包
		}	
		else
		{
			//失败
			//返回买家交易失败（钱不够）
		}
	}
	if(goods->gold)
	{
		if(hero->money->useGold())
		{
		
		}
		else
		{
		
		}
	}
	if(goods->boundMoney)
	{
		if(hero->money->useBoundGameMoney())
		{
		
		}
		else
		{
		
		}
	}
	if(goods->money)
	{
		if(hero->money->useGameMoney())
		{
		
		}
		else
		{
		
		}
	}
}

//物品改价
void changeStallCommodityPrice(char *buff)
{
	string stallCommodityId;
	string heroId;
	
	//消息解析
	
	if(stall.find(heroId)==stall.end())
	{
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
	}
	PrivateStall *privateStall=stall.find(heroId)->second;
	if(privateStall->container.find(stallCommodityId)==privateStall->container.end())
	{
		
	}
	StallCommodity stallCommodity=privateStall->container.find(stallCommodityId)->second;
	stallCommodity.num=num; //修改物品数量
		int num;
	int boundGold;				//修改商品价格
	int gold;
	int boundMoney;
	int money;
	
}

//物品下架
void deleteStallCommodity(char *buff)
{
	string stallCommodityId;
	string heroId;
	
	//消息解析
	
	if(stall.find(heroId)==stall.end())
	{
		cout<<"cant find this privateStall   in stallBusiness.cpp:120"<<endl;
		return;
	}
	PrivateStall *privateStall=stall.find(heroId)->second;
	if(privateStall->container.find(stallCommodityId)==privateStall->container.end())
	{
		cout<<"error"<<endl;
		return;
	}
	privateStall->container.erase(stallCommodityId);
	string msg;//success
	send(msg,sock_fd);
}

//收摊
void deleteStall(char *buff)
{
	string heroId;
	if(stall.find(heroId)==stall.end())
	{
		return;
	}
	stall.erase(stall.find(heroId));
}


























