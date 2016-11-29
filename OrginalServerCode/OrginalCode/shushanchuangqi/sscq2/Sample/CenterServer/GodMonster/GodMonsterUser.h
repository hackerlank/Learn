
#ifndef GODMONSTERUSER_H_
#define GODMONSTERUSER_H_
#include "User.h"
#include "UserMgr.h"
#include "GodMonsterProt.h"
#include "Singleton.h"

using namespace NGodMonsterProt;

const static UINT32 BASESCORE = 10; 
//////////////////////////////////
//限购礼包类
class CLimitPrize
{
    public:
        CLimitPrize(UINT16 wPrizeID): _wID(wPrizeID)
        {
            _wCurNum = 0;
            _wCurPrice = 0;
        }
        virtual ~CLimitPrize() {};
        void SetCurNum(UINT16 wNum) { _wCurNum = wNum; }
        void Update2DB(UINT64 qwRoleID,UINT16 wNum);
    public:
        UINT16 GetID() { return _wID; }
        void AddCurNum(UINT16 wNum) { _wCurNum += wNum; }
        UINT16 GetCurPrice() { return _wCurPrice; }
        void SetCurPrize(UINT16 wTmp) { _wCurPrice = wTmp; }
        UINT16 GetCurNum() { return _wCurNum; }
    private:
        UINT16 _wID;
        UINT16 _wCurNum;
        UINT16 _wCurPrice;
};
typedef shared_ptr<CLimitPrize> LimitPrizePtr;
typedef std::map<UINT16,LimitPrizePtr> TMapID2PrizePtr;
struct SKey
{
    UINT64 _qwRoleID;
    UINT16 _wPrizeID;
    UINT16 _wNum;
    SKey(UINT64 qwRoleID,UINT32 wPrizeID)
    {
        _qwRoleID = qwRoleID;
        _wPrizeID = wPrizeID;
        _wNum = 0;
    }
    bool operator < (const SKey &oKey) const
    {
        if(_qwRoleID != oKey._qwRoleID)
            return _qwRoleID < oKey._qwRoleID;
        return _wPrizeID < oKey._wPrizeID;
    }
    void Add(UINT16 wTmp)
    {
        _wNum += wTmp;
    }
    UINT16 GetNum() { return _wNum; }
};
class CLimitPrizeMgr : public Singleton<CLimitPrizeMgr>
{
    public:
        CLimitPrizeMgr() {} 
        ~CLimitPrizeMgr() {} 
        bool LoadFromDB();
        void Load(const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize);
    public:
    private:
        std::set<SKey> setCache;// 临时数据
};
////////////////////////////////
class CGodMonsterUser
{
public:
    CGodMonsterUser(UINT64 qwUserID);
    virtual ~CGodMonsterUser();
    //喂养神兽
    EMonsterResult OneFeed(UINT32 dwFruit = 1);
    //购买限购物品
    EMonsterResult Buy(UINT16 wIndex,UINT16 wCount);
    //领奖
    EMonsterResult TakePrize(EMonsterPrizeType eType);
    //获得玩家在活动中的全部信息
    void GetMonsterUserInfo();
    void LoadFromDB(const SGuildUser2DB& sUser);
    void Update2DB();
    void AddLimitPrize(LimitPrizePtr pLimit);
    void BuyFruit(UINT32 dwCount);
public:
    UINT64 GetUserID() { return _qwRoleID; }
    UINT64 GetRoleID() { return _qwRoleID; }
    UINT64 GetGuildID() { return _qwGuildID; }
    void   SetGuildID(UINT64 qwGuildID) { _qwGuildID=qwGuildID; }
    UINT64 GetMonsterID() { return GetGuildID(); } 
    bool   IsGuildUser() { return _qwGuildID ? true : false; }
    UINT32 GetFruit() { return _dwFruit; }
    void   AddFruit(UINT32 dwTmp) { _dwFruit += dwTmp; }
    UINT32 GetDevote() { return _dwDevote; }
    void   SetDevote(UINT32 dwTmp) { _dwDevote = dwTmp; }
    UINT32 GetTotalScore(); 
    void   SetTotalDevote(UINT32 dwTmp) { _dwTotalScore = dwTmp; }
    UINT32 GetDayScore(); 
    void   GetPrizeInfo(TVecMonsterPrize &vecPrize);
    void   GetLimitInfo(TVecLimitPrize &vecLimitPrize);
    LimitPrizePtr GetLimitPrize(UINT16 wIndex);
    void   OnSuc(UINT16 wIndex,UINT16 wCount,UINT32 dwServerID,UINT16);
    bool   IsTake(EMonsterPrizeType eType);
public:
    bool   CheckFruit(UINT32 dwTmp) { return dwTmp <= _dwFruit; }
    void   DelFruit(UINT32 dwTmp)
    { 
        if(CheckFruit(dwTmp))
            _dwFruit -= dwTmp; 
    }
    void ResetTakeing() { _bTaking = false; }
    void ResetBuying() { _bBuying = false; }
private:
    UINT64 _qwRoleID;
    UINT64 _qwGuildID;
    UINT32 _dwFruit;
    UINT32 _dwDevote;
    UINT32 _dwTotalScore;
    TMapID2PrizePtr _mapID2Prize;
    bool _bTaking ; // 临时变量
    bool _bBuying; //临时变量
};
#endif 
typedef shared_ptr<CGodMonsterUser> GodMonsterUserPtr;
typedef std::map<UINT64,GodMonsterUserPtr> TMapID2MonsterUserPtr;
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

