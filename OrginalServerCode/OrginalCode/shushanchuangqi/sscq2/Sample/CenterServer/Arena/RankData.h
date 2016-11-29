#ifndef RANKDATA_H__
#define RANKDATA_H__
#include "ArenaGS.h"
#include "ArenaCFG.h"
using namespace NArenaGS;
struct RankNode
{
    UINT32 dwPreNum;//记录该节点前面的玩家
    vector<UINT64> vecPlayer;
    RankNode()
    {
        dwPreNum = 0;
    }
};

class CRankData
{
    public:
        CRankData()
        {
        }
        CRankData(const SArenaCFG *pConfig);
        void  UpdateForCal(map<EArenaLevel,vector<UINT64> > &rmapUpdate,UINT32 dwNow,set<UINT64> &setSame);
        void  PlayerAddScore(INT32 dwAddScore,SArenaPlayerData *Player,TSetUINT64& rSetUpdate);
        UINT32  NewPlayerEnter(UINT64 qwRoleId);
        bool  InsertPlayerForDB(const SArenaPlayerData *pPlayer);
        UINT32  InsertErrPlayerForDB(const SArenaPlayerData *pPlayer); 
        void  InsertPlayerForCal(vector<UINT64>& rVec);
        const SArenaCFG * GetConfig(){return &_Config;}
        void SetPreNumAllForDB();
        UINT32 GetPreNumByScore(UINT32 dwScore);
        void GetPlayerListByRank(TVecUINT64& vecPlayer,UINT32 dwFrom,UINT16 wNum);        
        UINT32 GetRankAward(UINT32 dwRank);
        UINT32 GetLevelAward();
        //UINT32 GetSameDaysAward(UINT32 dwDays);
        void FindRandom(TVecUINT64 &vecSel,UINT64 qwExtraID,UINT8 byNum);
        UINT32 GetExtraScore(UINT8 byLevel);
        UINT32 GetPlayerSize();
        bool CheckPlayer(SArenaPlayerData *pPlayer);
        EArenaLevel CalPlayerNewLevel(SArenaPlayerData *pPlayer/*,UINT32 &dwSameDays,*/,UINT32 &dwCurRank);
        void ResetConfig(const SArenaCFG *pConfig);
    private:
        void SetPreNum(UINT32 dwPreScore,UINT32 dwNowScore,bool bNewNote);//重新设置两个积分的节点数据
    private:
        SArenaCFG _Config;
        TVecUINT32 _vecRankAward;
        TVecUINT32 _vecExtraScore;//对应段位差1，2，3，4
        map<UINT32,RankNode,greater<UINT32> > _mapScore;//相同积分玩家
};
#endif //RANKDATA_H__
