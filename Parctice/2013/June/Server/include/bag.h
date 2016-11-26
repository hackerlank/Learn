/***********************************************
*	鑳屽寘绫?Bag
*	鍒朵綔:jolly
*	鏃ユ湡:2012.6.20
*	鍔熻兘:鎻愪緵淇濆瓨鐗╁搧,鍚戝鎴风鍙戦€佷俊鎭殑鏂规硶
***********************************************/
#ifndef BAG_H
#define BAG_H
#include <iostream>
#include <map>
#include <vector>
#include "wholeDefine.h"
#include "goods_config.h"
#include "data_structure_struct.h"
#include "command_return_define_data.h"
#include "equip_config.h"
#include "my_memcached.h"
#include "command_other_function_all_over.h"
#include "pet.h"
#include "bag_operator.h"
#include "pet_config.h"
using namespace std;

class Ointment;
class Goods;
class Pet;
class Bag
{

private:			
	vector<Trade_Goods> trade_goods;			//浜ゆ槗鎴愬姛瀹瑰櫒
	
	vector<int> trade_index;						//浜ゆ槗瀹瑰櫒
	
	set<int> lockIndex;							//姝ｅ湪閿佸畾鐨勭墿鍝佷笅鏍?
	
	BagData bagdata;
	
public:
	int getTradeGoodsSize(void);
	int getTradeIndexSize(void);
	Goods *getGoods(int index);
	Bag(void);		//鍒濆鍖栧嚱鏁?榛樿鍒氬垱寤轰汉鐗╃殑鏃跺€?鑳屽寘涓病鏈変换浣曢亾鍏?
	Bag(BagData _bagdata);
	~Bag(void);
	
	int getExpandNeedGold(void);
	
	void setExpandNeedGold(int _expandNeedGold);	
	
	bool putOnEquip(int _index,char* goodsid);	//绌胯澶?
				
	int searchIndex(char* goodsid);				//鏍规嵁鐗╁搧id鏌ユ壘鎵€鍦ㄧ殑id
		
	void saveGoodsInGrid(char* goodsid,int index,int num);		//淇濆瓨鑽搧瀹炰緥
						
	int isExist(char* goodsid,int maxNum);	//鍒ゆ柇鏄惁鏈夌浉鍚岀殑鑽搧瀛樺湪
	
	void beforeArrang(void);
	
	bool deleteEquip(char* identity);		//鍒犻櫎瑁呭瀹炰緥
	
	int get_goods_num(int index); //鍙栧嚭鐗╁搧鐨勫爢鍙犳暟閲?
		
	int getNextGoodsIndex(void); 	//鍙栧緱涓嬩竴涓墿鍝佸湪鍏ㄩ儴鏍忎腑鐨勪綅缃?
	
	bool finishTask(int _num,int index);	//瀹屾垚浠诲姟,鎻愪氦浠诲姟閬撳叿
		
	int getBagNum(void);	//鑾峰彇鑳屽寘鏍煎瓙鏁伴噺
	
	void setBagNum(int _bagnum);	//璁剧疆鑳屽寘鏍煎瓙鏁伴噺
	
	void setGridNum(int _num,int index);				//璁剧疆璇ユ牸瀛愮殑鐗╁搧鏁伴噺
	
	void initGrid(int index,int flag=0);						//鍒濆鍖栨牸瀛?	
	
	bool drag(int _initindex,int _finalindex,char* initgoodsid,char* finalgoodsid);	//鎷栧姩鑳屽寘鐗╁搧 閲嶆柊鍌ㄥ瓨鍑芥暟
		
	int remainGridNum(void);						//鍓╀綑鐨勮儗鍖呮牸瀛愭暟
	
	bool bagExpand(int num);						//鑳屽寘鎵╁睍
	
	char* getIdentity(int index);						//鏍规嵁绱㈠紩鎵惧疄渚媔d	
	
	int getGridNum(int index);							//浣跨敤绱㈠紩鎵炬牸瀛愪腑鐗╁搧鐨勬暟閲?
	
	int getGoodsNum(char* goodsid);					//鏍规嵁鐗╁搧id鏌ユ壘鐗╁搧鏁伴噺	
	
	bool bagIsFull(int _willUse);						//鍒ゆ柇鑳屽寘鏄惁宸叉弧
		
	bool addGoods(char* identity,int index,int num=1);	
	
	bool test(int index, const char* identity);			//楠岃瘉鐗╁搧

	bool testNumber(int index,int number);			
		
	bool putOnTradeTable(char* goodsid,int index_bag);
	
	bool takeOffTradeTable(int index_trade);
	
	vector<int> tradeSuccessReturnIndex(void);
	vector<Trade_Goods> getTrade_Goods(void);
	
	void tradeFailed(void);
	
	char* identity_to_goodsid(char* identity);
	
	bool isLocking(int index);
	
	BagData getMemStruct(void);
	
	void setMemStruct(BagData _bagdata);
	
	int showBagData(BagData *obj, char *outfile);
	
	void msg_drag_success(char *msg,int len,int initindex,int finalindex,char* firstgoodsid,char* secondgoodsid);
	
	
	BagGoodsData getBagGoodsData(int _index);
	
	void setGridData(BagGoodsData _baggoodsdata,int _index);
	
	//缁欏嚭瑁呭鐨勫疄渚媔d,鏌ユ壘瑁呭鍦ㄨ儗鍖呬腑鐨勭储寮?
	int getEquipIndex(char *index);
	
	//鏌愪簺鎿嶄綔闇€瑕侀攣瀹氱墿鍝佺储寮?
	void goodsLockIndex(int index);
	bool isLock(int index);
	//瑙ｉ攣鏌愪簺鐗╁搧
	void goodsUnlockIndex(int index);
	
	void msg_expand_success(char* msg,int len);
	void msg_drag_failed(char *msg,int len);
	
	set<int> getLockIndex(void);
};
#endif