#include "Game2CenterGuildBattleC.h"

#include "NewGuildBattleMgr.h"

CGame2CenterGuildBattleC::~CGame2CenterGuildBattleC()
{
}

//接收：帮派等级更新
void CGame2CenterGuildBattleC::OnRecv_GuildLevelChanged(
        UINT64 qwGuildID, //帮派对应ID
        UINT16 wLevel //帮派等级
        )
{
    NNewGuildBattle::CBattleMgr::Instance().ChangeGuildLevel(qwGuildID, wLevel);

}

//接收：帮主更新
void CGame2CenterGuildBattleC::OnRecv_GuildOwnerChanged(
        UINT64 qwGuildID, //帮派对应ID
        const std::string& strGuildOwnerName //帮主名称
        )
{
    NNewGuildBattle::CBattleMgr::Instance().ChangeGuildOwnerName(qwGuildID, strGuildOwnerName);
}

//接收：帮派解散
void CGame2CenterGuildBattleC::OnRecv_GuildDisband(
        UINT64 qwGuildID //帮派对应ID
        )
{
    NNewGuildBattle::CBattleMgr::Instance().ClearGuild(qwGuildID);
}

//接收：可以发送新帮派战数据
void CGame2CenterGuildBattleC::OnRecv_ReadyToSendNewGuildBattle(
        )
{
    NNewGuildBattle::CBattleMgr::Instance().StartLoadData();
}
