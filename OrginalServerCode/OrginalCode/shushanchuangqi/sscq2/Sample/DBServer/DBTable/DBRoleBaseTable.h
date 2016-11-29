#ifndef  DBROLEBASETABLE_H__
#define  DBROLEBASETABLE_H__

#include "DBTableBase.h"

class DBRoleBaseTable : public TableRowBase, public RoleBaseInfo
{
    public:
        friend class BRoleBaseTableManager;

    public:
        enum EUpdateColumn
        {
            UPCOL(strName),
            UPCOL(byLevel),
            UPCOL(qwExp),
            UPCOL(eCareer),
            UPCOL(eSex),
            UPCOL(wMapID),
            UPCOL(fX),
            UPCOL(fY),
            UPCOL(byNation),
            UPCOL(byGMLvl),
            UPCOL(dwTotalRecharge),
            UPCOL(dwLoginTime),
            UPCOL(dwOfflineTime),
            UPCOL(dwLockExpireTime),
            UPCOL(dwForbExpireTime),
            UPCOL(dwGold),
            UPCOL(dwFreeGold),
            UPCOL(dwSilver),
            UPCOL(dwCoupon),
            UPCOL(dwSoul),
            UPCOL(dwPrestige),
            UPCOL(dwHonor),
            UPCOL(dwPExp),
            UPCOL(dwAction),
            UPCOL(dwPoten),
            UPCOL(dwReiki),
            UPCOL(dwDemonSoul),
            UPCOL(dwSoulAttack),
            UPCOL(dwSoulHp),
            UPCOL(dwSoulCritical),
            UPCOL(dwSoulCounter),
            UPCOL(dwSoulSpeed),
            UPCOL(dwSoulDefence),
            UPCOL(dwSoulHit),
            UPCOL(dwSoulDodge),
            UPCOL(dwLoveHeart),
            UPCOL(dwBlueFairyFate),
            UPCOL(dwPurpleFairyFate),
            UPCOL(dwOrangeFairyFate),
            UPCOL(dwDuJieFu),
            UPCOL(dwBTPoint),
            UPCOL(szOwnTitle),
            UPCOL(szEquipTitle),
            UPCOL(byDomain),
            UPCOL(byDomainLvl),
            UPCOL(byDisplayLvl),
            UPCOL(byDomainYear),
            UPCOL(szOpenId),
            UPCOL(szOpenKey),
            UPCOL(qwInvitedID),
            UPCOL(byWallow),
            UPCOL(qwDgnId),
            UPCOL(dwDgnTypeID),
            UPCOL(wDgnMapId),
            UPCOL(fDgnfX),
            UPCOL(fDgnfY),
            UPCOL(dwPendSilver),
            UPCOL(dwPendCoupon),
            UPCOL(dwPendExp),
            UPCOL(dwPendGold),
            UPCOL(strSign),
            UPCOL(wMood),
            UPCOL(dwDemonTowerFloorID),
            UPCOL(dwDemonTowerPrizeFloorID),
            UPCOL(strGuide),
            UPCOL(szIcon),
            UPCOL(szIconDel),
            UPCOL(szIconActive),
            UPCOL(dwPackNextUnlockTime),
            UPCOL(dwActivity),
            UPCOL(dwStampHuang),
            UPCOL(dwStampXuan),
            UPCOL(dwStampDi),
            UPCOL(dwStampTian),
            UPCOL(dwStampXing),
            UPCOL(dwStampYue),
            UPCOL(dwStampDi2),
            UPCOL(dwStampXian),
            UPCOL(dwStampSheng),
            UPCOL(dwStampFo),
            UPCOL(wAchievementLevel),
            UPCOL(dwAchievementAP),
            UPCOL(wCollectLevel),
            UPCOL(byYDLevel),
            UPCOL(dwCollectAP),
            UPCOL(qwSittingPlayer),
            UPCOL(dwIndulgeKickTime),
            UPCOL(dwCreateTime),
            UPCOL(strCreateIP),
            UPCOL(strLoginIP),
            UPCOL(wLastSaveMapID),
            UPCOL(fLastSaveX),
            UPCOL(fLastSaveY),
            UPCOL(szDgnStarAward),
            UPCOL(dwLuckyCoupon),
            UPCOL(Max),
        };

    public:
        virtual void  InitDataByStr(string&  strData);
        virtual bool  UpdateDataByStr(string& strData);
        virtual bool  GetInsertSqlStr(string& sqlstr);
        virtual bool  GetUpdateSqlStr(string& sqlstr);
        virtual void  ResetChange(void);
        virtual void  InitDataByDBRow(const mysqlpp::Row &row);

        DBRoleBaseTable(const UINT64& qwOwerId) : _qwRoleID(qwOwerId)
    {}

        void Login();
        void LoginOff();
        void Freeze(UINT32 dwTimer);//封号
        void ForbitChat(UINT32 dwTimer);//禁言
        void UpdateLoginIP(const string& strIP);

    private:
        bitset<UPCOL(Max)> _setChanged;
        const UINT64& _qwRoleID;
};

class DBRoleBaseTableManager : public TableManagerBaseForRole 
{ 
    public:
        DBRoleBaseTableManager(UINT64 sqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeRoleBaseInfo,sqwRoleID,byLine), _RoleData(_qwRoleID)
    {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData) {}
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        UINT16 GetMapID() const { return _RoleData.wMapID; }
        virtual UINT32 GetUpdataNum();
        void Login();
        void LoginOff();
        void Freeze(UINT32 dwTimer);//封号
        void ForbitChat(UINT32 dwTimer);//禁言
        void UpdateLoginIP(const string& strLoginIP);
        UINT32 GetFreezeTimer();
        UINT32 GetForbitChatTimer();

    private:
        DBRoleBaseTable _RoleData;
};
#endif

