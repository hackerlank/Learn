
#ifndef LOOT_H_
#define LOOT_H_

#include <unordered_map>
#include <vector>
#include "Item.h"
#include "Singleton.h"

// 
// 概率基础值为：10000
// 
// id1,chance1[,num1[,bind1[,expiretype1,expiretime1]]]|id2,chance2[,num2[,bind2[,expiretype2,expiretime2]]]|...|idN,chanceN[,numN[,bindN[,expiretypeN,expiretimeN]]]
// LT_ALL_ABOVE    = 0 产出概率大于随机概率的单元
// LT_ONE_FROM_ALL = 1 产出随机概率落于某一个概率范围所在的单元 chance1+chance2+...+chanceN=10000
// LT_EACH_CHANCE  = 2 对每一个单元单独随机，如果随机概率大于指定概率则产出该单元
//
// id 可为道具ID或包ID
// 最小包ID为65536 (道具ID:UINT16,最大65535)
// id 为包ID时，个数、绑定、过期等项无效
// 例：
// (0, "1,10000|2,10000|3,5000|4,3000,100")
// 随机到 4500，则1 2 3全有
// (1, "5,1000|6,2000,99|7,3000|8,4000,250")
// 随机到 4500，则只有7
// (2, "1,10000|2,10000|3,5000|4,3000,100")
// 则1 2必出，再随机一次，大于5000出3，再随机一次，大于3000出4
// 

enum ELootType
{
	ELOOT_ALL_ABOVE    = 0,
	ELOOT_ONE_FROM_ALL = 1,
	ELOOT_EACH_CHANCE  = 2,
	ELOOT_MAX
};
#define LOOT_PACKID_MIN 65536
struct SLootCell
{
	SLootCell()
		: chance(0), iid(0), count(1), bind(eBindNone)
	{}

	UINT16 chance;
	UINT32 iid;
	UINT32 count;
	EBindType bind;
};

class CLootLoader;

class CLootMgr : public StaticSingleton<CLootMgr>
{
	struct Loot
	{
		UINT32 _dwLootID;
		ELootType _eLootType;
		std::vector<SLootCell> _vecCells;

		Loot() : _dwLootID(0), _eLootType(ELOOT_ALL_ABOVE) {}
		Loot(UINT32 id) : _dwLootID(id), _eLootType(ELOOT_ALL_ABOVE) {}
		bool init(ELootType eLootType, const string& lcfg);
		bool roll(std::vector<SItemGenInfo>& items,TVecResource &vecRes);
		bool fetchall(std::vector<SItemGenInfo>& items,TVecResource &vecRes);
		bool isonefromall();
	private:
		bool initLootCells(const string& lcfg);
		bool rollAllAbove(std::vector<SItemGenInfo>& vecItems,TVecResource &vecRes);
		bool rollOneFromAll(std::vector<SItemGenInfo>& vecItems,TVecResource &vecRes);
		bool rollEachChance(std::vector<SItemGenInfo>& vecItems,TVecResource &vecRes);
	};

public:
	typedef std::unordered_map<UINT32, Loot> TLootMap;
	typedef TLootMap::iterator iterator;

public:
	bool Init();
    bool LoadConfig(bool bReload = false);
	bool CheckRoll(UINT32 id);
	bool Roll(UINT32 id, std::vector<SItemGenInfo>& items,TVecResource &vecRes);//后者直接加数字
	bool FetchAll(UINT32 id, std::vector<SItemGenInfo>& items,TVecResource &vecRes);
	bool IsRollOneLoot(UINT32 id);
	UINT16 CheckAndAddItem(UINT32 dwID, CUserPtr pUsr, bool bMsgNotify = true);

private:
	bool InitLoot(const CLootLoader& lootcfg);
	bool AddLootConfig(TLootMap& mapLoot, UINT32 id, ELootType type, const string& lcfg);
	bool CheckLootConfig(TLootMap& mapLoot);
	TLootMap _oLootMap;
};

#define LOOT CLootMgr::Instance()

#endif // LOOT_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

