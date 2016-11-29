
#ifndef SHENGLING_H_
#define SHENGLING_H_

#include "User.h"
#include "VarDefine.h"
#include "Singleton.h"
#include "ShengLingProtS.h"
#include "RoleInfoDefine.h"
#include "ProtoCommon.h"

using namespace NVarDefine;
using namespace NShengLingProt;
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
enum EShengLing
{
    eShengLingNone,
    eShengLingIn,
    eShengLingOut
};

class CShengLing : public CPoolObj<CShengLing>
{
public:
    CShengLing(CPlayer &rPlayer);
    virtual ~CShengLing();

    void OnOpen(UINT8 &byUseEnter,UINT8 &byBuyEnter,UINT8 &byBuyEnterToday,bool &bContinue);
    //进入圣陵
    EShengLingResult OnEnter(SShengLingInfo &rInfo);
    //摇骰子
    EShengLingResult OnDrawDice(UINT8 &byNum,NShengLingProt::SPlayerInfo &sInfo,bool bControlDice,UINT64 &qwBattleID);
    //使用卡片
    EShengLingResult OnUseCard(ECardType eCardType,UINT8 byNum,SCard &sCard,NShengLingProt::SPlayerInfo &rInfo,UINT64 &qwBattleID);
    //玩家购买
    EShengLingResult OnBuy(EBuyType eBuyType,UINT8 byNum,UINT8 &byBuy,UINT8 &byUse,UINT8& byBuyToday);
    //玩家领奖
    EShengLingResult OnTakePrize(EGridType eType,UINT8 byIndex,UINT8 &byBit);
    //玩家 玩三消
    EShengLingResult AddScore(UINT16 wScore,UINT8 byStep,UINT16 wPassword,UINT16 &wPwd,UINT8 &byReminStep,UINT16 &wTotalScore);
    //玩家完成或者放弃小游戏 处理格子
    EShengLingResult OnFinishTrap();

    void OnLeave();
    void LoadFromDB(const TVecShengLingInfo2DB &rvecDBInfo,const TVecShengLingPrize2DB &rvecDBPrizeInfo);
    EShengLing  GetState() { return _eState; }
    void UserOffLine();
    void SyncData();
    bool RandAllGrid();
private:
    //策划需求，对生成格子进行调整（概率保护）
    bool RejustGrid(TVecGrid &vecGrid);
    void Rejust(UINT8 byUp,UINT8 byDown,UINT8 byNum,TVecGrid &vecGrid);
    UINT8 CheckRejust(UINT8 byUp,UINT8 byDown,UINT8 byNum,TVecGrid& vecGrid);
    bool CheckOneGrid(SGrid &rGrid,TVecGrid &vecGrid);
    void  SendPrizeInfo(TVecItemGenInfo &vecItem);
    //数据一致性检测
    bool CheckVarAndDB();

    UINT8 GetBigBoxIndex();
    bool CheckPlayEffect();
    void SetControlDiceSended(bool bFlag);
    bool CheckControlDiceSended();
    EShengLingResult SubMoneyInShengLing(CUserPtr pUser,UINT16 wGold);
    bool OnBattle(UINT32 dwEnemyID,UINT64 &qwBattleID,bool &bPlayerWin);
    bool CheckAllGridbyLevel(UINT8 byLevel);
    SGrid* GetGrid(UINT8 byLevel,UINT8 byIndex);
    void SetGridState(UINT8 byLevel,UINT8 byIndex,bool bState);
    bool GetPrize(SGrid &rGrid);
    bool ProcessGrid(SGrid &rGrid,UINT64 &qwBattleID);
    void Regen();
    bool ProcessDice(UINT8 byNum,UINT64 &qwBattleID,bool &bNext);
    void Update2DB(TVecGrid &vecGrid);
    void UpdatePrize2DB(EDataChange eDataChange,const TVecItemGenInfo &vecItem);
    TVecGrid* GetAllGridByLevel(UINT8 byLevel);
    bool CheckReflush(TVecGrid &vecGrid);
    bool RandOneGrid(SGrid &rGrid,bool bAll,bool bExceptMonster);
    bool GetBossAndBigBoxGrid(SGrid& rBossGrid1,SGrid& rBossGrid2,SGrid& rBigBoxGrid);
    bool GetCardInfo(TVecCard &vecCard);
    void GetPrizeInfo(TVecItemGenInfo &vecItem); 
    UINT8 GetUseLife();
    UINT8 GetBuyLife();
    UINT8 GetFreeLife();
    void  SetUseLife(UINT8 byTmp);
    void  SetBuyLife(UINT8 byTmp);

    UINT8 GetUseControlDice();
    UINT8 GetBuyControlDice();
    UINT8 GetFreeControlDice();
    void  SetUseControlDice(UINT8 byTmp);
    void  SetBuyControlDice(UINT8 byTmp);
    
    UINT8 GetUseEnter();
    UINT8 GetBuyEnter();
    UINT8 GetFreeEnter();
    void  SetUseEnter(UINT8 byTmp);
    void  SetBuyEnter(UINT8 byTmp);
    
    UINT8 GetUseTurnDice();
    UINT8 GetBuyTurnDice();
    UINT8 GetFreeTurnDice();
    void  SetUseTurnDice(UINT8 byTmp);
    void  SetBuyTurnDice(UINT8 byTmp);
   
    bool CheckEnter();
    bool CheckLife();
    bool CheckControlDice();
    bool CheckTurnDice();
    bool CheckPrizeState(UINT8 byIndex);
   
    void SubEnterNum(UINT8 byNum);
    void SubControlNum(UINT8 byNum);
    void SubTurnNum(UINT8 byNum);
    void SubLifeNum(UINT8 byNum);
   
    void AddEnterNum(UINT8 byNum);
    void AddControlNum(UINT8 byNum);
    void AddTurnNum(UINT8 byNum);
    void AddLifeNum(UINT8 byNum);

    UINT8 GetCurLevel();
    UINT8 GetCurIndex();
    void  SetCurLevel(UINT8 byTmp);
    void  SetCurIndex(UINT8 byTmp);

    UINT8 GetPreLevel();
    UINT8 GetPreIndex();
    void  SetPreLevel(UINT8 byTmp);
    void  SetPreIndex(UINT8 byTmp);

    UINT8 GetStep();
    UINT16 GetScore();
    UINT8 GetPrizeBit();
    void  SetStep(UINT8 byTmp);
    void  SetScore(UINT16 byTmp);
    void  SetPrizeBit(UINT8 byIndex);
    
    bool GetDir();
    void SetDir(bool bDir);

private:
    CPlayer &_rPlayer;
    bool _bLog;
    bool _bTest;
    bool _bLeave;
    bool _bNextDice;
    UINT16 _wPassword;
    std::map<UINT8,TVecGrid> _mapID2VecGridInfo;
    EShengLing _eState;
    UINT8 MAXLEVEL;
    bool  _bContinue;
    UINT64 _qwLastDrawDice;
    std::map<UINT16,UINT16> _mapID2Num; //奖励
};

#endif // CoinMGR_H_
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

