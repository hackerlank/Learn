
#ifndef GUILDXIHEMANAGER_H_
#define GUILDXIHEMANAGER_H_


#include "stdafx.h"
#include "GuildProtSvr.h"

using namespace NGuildProt;

class CUser;

class CGuildXiheManager : public Singleton<CGuildXiheManager>
{
public:
    CGuildXiheManager()  {}
    ~CGuildXiheManager() {}

    CGuildXihePtr GetGuildXihe(UINT64 qwRoleID);
    bool LoadXiheFromDB();
    void RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NGuildProt::TVecGuildXihe& vecSendData);
    void AddXiheTimer(UINT64 qwRoleID, UINT32 dwTime);
    void TimerCheck(time_t tNow);
    void GetXiheRequestInfo(UINT64 qwRoleID, TVecXiheRequest& vecRequest);

    EGuildXiheResult ShipGoods(CUserPtr pUser, UINT8 byType, UINT8 byPos, shared_func<CGuildProtSvr::SShipGoodsAck> fnAck);
    EGuildXiheResult HelpShipGoods(CUserPtr pUser, UINT8 byType, UINT64 qwOtherID, UINT8 byPos, shared_func<CGuildProtSvr::SHelpShipGoodsAck> fnAck);
    EGuildXiheResult DeliveryGoods(CGuildXihePtr pGuildXihe);
private:
    unordered_map<UINT64, CGuildXihePtr> _mapAllXiheShenche;
    multimap<UINT32, UINT64> _mapTimerXihe; //关联：时间<==>UserID
    static bool _bLoadFromDB;
};

#define GuildXiheManager CGuildXiheManager::Instance()

#endif // GUILDXIHEMANAGER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

