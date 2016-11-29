
#ifndef GAMESCRIPT_H_
#define GAMESCRIPT_H_
#include "Script.h"

#define SCRIPT_TYPE_ITEMUSE 0x0001
#define SCRIPT_TYPE_ACT     0x0002
#define SCRIPT_TYPE_SYS     0x0004
#define SCRIPT_TYPE_TASK    0x0008
#define SCRIPT_TYPE_NPC     0x0010
#define SCRIPT_TYPE_DGN     0x0020
#define SCRIPT_TYPE_GATHER  0x0040
#define SCRIPT_TYPE_AREA    0x0080



#define SCRIPT_TYPE_ALL     SCRIPT_TYPE_ITEMUSE|SCRIPT_TYPE_ACT|SCRIPT_TYPE_SYS|SCRIPT_TYPE_TASK|SCRIPT_TYPE_NPC|SCRIPT_TYPE_DGN|SCRIPT_TYPE_GATHER|SCRIPT_TYPE_AREA

class CUser;
class CItem;
class CDungeon;

class CGameScript : public CScript
{
    public:
        void SetUser(CUser* pUser) { _pUser = pUser; }
        void SetOther(CUser* pUser) { _pOther = pUser; }
        CUser* GetUser() { return _pUser; }
        CUser* GetOther() { return _pOther; }

    public:
        CGameScript() : _pUser(NULL), _pOther(NULL), _bHasItemUseNormal(false) {}
        ~CGameScript() {}

        bool ReloadScripts(int flag = SCRIPT_TYPE_ALL);
        bool HasUseFunction(UINT16 wItemID);
        virtual void SetGlobals();
        virtual bool Register();

        UINT16 ItemUseNormal(CUser& rUser, CItem& rItem, UINT16 wCount, UINT64 qwMercenID = 0, CUser* pOtherUser = NULL);
        UINT16 ItemUseNormal(CUser& rUser, UINT16 wItemID, UINT16 wCount, UINT8 byBind, UINT64 qwMercenID = 0, CUser* pOtherUser = NULL);

    private:
        UINT16 _ItemUseNormal(CUser& rUser, UINT16 wItemID, UINT16 wCount, UINT8 byBind, UINT64 qwMercenID, CUser* pOtherUser);
    public:
        // Task
        bool HasOnAcceptTaskFunction(UINT16 wTaskID);
        bool HasCanFinishTaskFunction(UINT16 wTaskID);
        bool HasOnGiveUpTaskFunction(UINT16 wTaskID);
        bool HasOnFinishTaskFunction(UINT16 wTaskID);
        bool HasCanAcceptTaskFunction(UINT16 wTaskID);
        bool HasDoCaseForDgnFunction(UINT16 wTaskID);

        void OnFinishTask(UINT16 wTaskID,CUser& rUser);
        void OnAcceptTask(UINT16 wTaskID,CUser& rUser);
        bool CanFinishTask(UINT16 wTaskID,CUser& rUser);
        void OnGiveUpTask(UINT16 wTaskID,CUser& rUser);
        bool CanAcceptTask(UINT16 wTaskID,CUser& rUser);
        void DoCaseForDgn(UINT16 wTaskID,UINT16 wDgnId,CUser& rUser);
        //NPC
        bool NpcTalk(string &strText,const string &strFunName,UINT16 wNPCTypeId,CUser& rUser);
        //Dungeon
        bool Dungeon_HasOnEnterLimit(UINT16 wDgnId);
        bool Dungeon_HasOnInit(UINT16 wDgnId);
        bool Dungeon_HasOnTimer(UINT16 wDgnId);
        bool Dungeon_HasOnEnd(UINT16 wDgnId);
        bool Dungeon_HasOnFinish(UINT16 wDgnId);

        UINT8 Dungeon_OnEnterLimit(UINT16 wDgnId,CUser& rUser);
        void Dungeon_OnInit(UINT16 wDgnId,CDungeon* pDgn);
        void Dungeon_OnTimer(UINT16 wDgnId,CDungeon* pDgn,UINT16 wTimerId);
        void Dungeon_OnEnd(UINT16 wDgnId,CDungeon* pDgn);
        void Dungeon_OnFinish(UINT16 wDgnId,CDungeon* pDgn);
        //Gather
        bool HasCanGatherFunction(UINT16 wGatherID);
        bool HasOnFinishGatherFunction(UINT16 wGatherID);

        UINT8 CanGather(UINT16 wGatherID,CUser& rUser);
        void  OnFinishGather(UINT16 wGatherID,CUser& rUser);
        //Area
        bool HasInAreaFunction(UINT16 wArea);
        void InArea(UINT16 wArea,CUser& rUser);
        //Trump
        UINT32 TrumpUpgrade(UINT16 wItemCount, CUser& rUser);
        UINT16 TrumpUpgradeOneKey(CUser& rUser);
        //Time
        UINT32 GetSharpDay(UINT32 dwTime);
    private:
        CUser* _pUser;
        CUser* _pOther;
        bool _bHasItemUseNormal;
};
typedef shared_ptr<CGameScript> CGameScriptPtr;

#endif // GAMESCRIPT_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

