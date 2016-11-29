#ifndef TEAMMANAGER_H__
#define TEAMMANAGER_H__
#include "TeamGS.h"
#include "DungeonCFG.h"
#include <set>
#include <unordered_map>
using namespace NTeamGS;
enum  TeamType
{
    TeamDGN     =   3,
    PETPOS      =   250,
    BEAUTYPOS   =   252,
    ERRPOS      =   255,
    MAXHERO     =   2,
};

struct CTeamInfo
{
    public:
        bool CanJoin();
        UINT8 GetSize(){return _vecMems.size();}
        CTeamInfo();
        CTeamInfo(UINT32 dwTeamID,UINT16 wDgnType);
        UINT64 GetLeaderID();
        void SetTeamID(UINT32 dwTeamID){_dwTeamID = dwTeamID;}
        UINT32 GetTeamID(){return _dwTeamID;}
        UINT64  GetBeautyOwer();
        void SetBeautyOwer( UINT64 qwBeautyOwer);
        void FindBeautyOwer();
        void SetSetting(const TeamSetting& stSetting);
        const TeamSetting& GetSetting();
        UINT8 PlayerJoin(UINT64 qwRoleID);
        UINT8 PlayerLeave(UINT64 qwRoleID,UINT8 byPos);//返回0：正常，返回1：队长变更：返回2：队伍空
        void SetDgnType(UINT16 wDgnType){ _wDgnType = wDgnType;}
        UINT16 GetDgnType(){return _wDgnType;}
        const TVecUINT64& GetMemBers(){return _vecMems;}
        bool IsMember(UINT64 qwRoleID);
        void ChangeFreePos(UINT8 byPos1,UINT8 byPos2); 
        UINT8 GetFreePos();
        bool IsBattle(){return _bBattle;}
        void SetBattle(bool bBattle){ _bBattle = bBattle;};
        bool GetTeamInfoForList(TeamInfoForList &Info);
        void ChangLeader(UINT64 qwNewLeader);
        void SendMsgForAll(const string& strMsg);

    private:
        UINT32 _dwTeamID;
        UINT16 _wDgnType;
        UINT64 _qwBeautyOwner;
        TeamSetting _stSetting;
        TVecUINT64 _vecMems;
        std::set<UINT8> _setFreePos;
        bool _bBattle;
};

struct CMemInfo
{
    public:
        CMemInfo();
        CommonFighterPtr GetMainFighter();
        void SetRoleID(UINT64 qwRoleID){_qwRoleID = qwRoleID;}
        UINT64 GetRoleID(){return _qwRoleID;}
        void SetTeamID(UINT32 dwTeamID){_dwTeamID = dwTeamID;}
        UINT32 GetTeamID(){return _dwTeamID;}
        void SetStatus(EMemberStatus eStatus){_eStatus = eStatus;}
        EMemberStatus GetStatus(){return _eStatus;}
        void SetFighters(TVecTeamFighter &vecFigthers){_vecFigthers = vecFigthers;}
        TVecTeamFighter& GetFighters(){return _vecFigthers;}
        void Reset();
        UINT8 GetPos(){return _byPos;}
        void SetPos(UINT8 byPos){ _byPos = byPos;}
        string GetName();
        bool IsHaveBeauty() const;//是否有美女
    private:
        UINT64 _qwRoleID;
        UINT32 _dwTeamID;
        UINT8  _byPos;
        EMemberStatus _eStatus;
        TVecTeamFighter _vecFigthers;

};
class CTeamManager
{
    public:
        CTeamManager():_dwTeamBase(0), _dwRewardRate(10000){}
        const vector<UINT32>* GetTeamByType(UINT16 wDgnType); 
        CTeamInfo* GetTeamInfoByID(UINT32 dwTeamID); 
        CMemInfo * GetRoleInfoByID(UINT64 qwRoleID);
        const SDungeonCFG * GetDgnConfigByType(UINT16 wDgnType);
        bool Init();
        UINT32  CreateTeam(UINT64 qwRoleID,UINT16 wDgnType,const TeamSetting& stSetting,TVecTeamFighter& vecFighter);
        bool  JoinTeam(UINT64 qwRoleID,CTeamInfo *pTeam,TVecTeamFighter& vecFighter);
        bool  ResetFighter(CMemInfo * pMember,UINT8 byPos,const NTeamGS::CommonFighterPtr& pNewFighter);
        void  PlayerOffLine(UINT64 qwRoleID);
        bool  PlayerLeave(UINT64 qwRoleID);
        bool  PlayerLeave(CMemInfo *pMember);
        bool  PlayerReady(CMemInfo *pMember);
        bool  PlayerCancelReady(CMemInfo *pMember);
        //推送队伍信息
        void NoticeTeamInfo(UINT32 dwTeamID,UINT64 qwRoleID = 0);
        void SynPlayerTeam(UINT64 qwRoleID,bool bEnter);
        void SynPlayerTeamForJump(UINT64 qwRoleID);
        void ResetTeam(UINT32 dwTeamID);
        void ResetTeam(CTeamInfo* pTeam);
        void ResetNewDgn(CTeamInfo*pTeam,UINT16 wNewDgnType);
        UINT8 CalFighterPos(UINT64 qwFighterID,CMemInfo *pMember);
        void OpenQueryRoom(UINT64 qwRoleID,UINT16 wDgnType);
        void CloseQueryRoom(UINT64 qwRoleID);
        void UpdateQueryRoom(TeamListOP eOp,const TeamInfoForList &Info);
        void DisMiss(UINT32 dwTeamID);

        void SetRewardRate(UINT32 dwRewardRate);
        UINT32 GetRewardRate() const;
        UINT32 GetRewardRateByPerson( UINT8 byNum) const;

    private:
        unordered_map<UINT64,CMemInfo> _mapRole;//玩家的信息
        unordered_map<UINT32,CTeamInfo> _mapTeam;//队伍的信息
        unordered_map<UINT16,vector<UINT32> >   _mapType;//根据类型，得到同类型队伍
        map<UINT16,SDungeonCFG> _mapConfig;
        map<UINT16,set<UINT64> > _mapQuery;;

        UINT32 _dwTeamBase;

        UINT32 _dwRewardRate;   // 奖励加成系数万分比
};
extern CTeamManager g_TeamManager;
#endif //TEAMMANAGER_H__ 
