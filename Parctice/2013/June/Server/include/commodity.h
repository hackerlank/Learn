#ifndef COMMODITY_
#define COMMODITY_

typedef struct StallGoods_T
{
	char typeId[20];//类型id
	char goodsId[40];  //该物品实例id
	int number; //物品数量
	int type; //物品类型
	int price; //物品价格
	int goodsIndexInBag; //该物品在背包中的
	int priceFlag;		//价格标志 1为银两 2为元宝
	StallGoods_T()
	{
		strncpy(typeId,"0",sizeof(typeId));
		typeId[sizeof(typeId)-1]='\0';
		strncpy(goodsId,"0",sizeof(goodsId));
		typeId[sizeof(goodsId)-1]='\0';
		number=0;
		type=0;
		price=0;
		goodsIndexInBag=-1;
		priceFlag=0;
	}
	void initStallGoods(void)
	{
		strncpy(typeId,"0",sizeof(typeId));
		typeId[sizeof(typeId)-1]='\0';
		strncpy(goodsId,"0",sizeof(goodsId));
		typeId[sizeof(goodsId)-1]='\0';
		number=0;
		type=0;
		price=0;
		priceFlag=0;
		goodsIndexInBag=-1;
	}
}StallGoods;
//个人摊位
typedef struct PrivateStall_T
{
	char privateStallName[50]; //摊位名
	StallGoods stallGoods[24];
	Point pt;  //该商店坐标点即摊主的当前位置
	int number;			//摆摊的总数量
	void initPrivateStall(void)
	{
		strncpy(privateStallName,"0",sizeof(privateStallName));
		number=0;
	}
}PrivateStall;
#endif