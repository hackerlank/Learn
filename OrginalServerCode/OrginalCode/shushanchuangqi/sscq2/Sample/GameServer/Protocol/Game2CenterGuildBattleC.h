#ifndef GAME_2_CENTER_GUILD_BATTLE_C_H
#define GAME_2_CENTER_GUILD_BATTLE_C_H

#pragma once

#include "Game2CenterGuildBattleClt.h"

using namespace NGame2CenterGuildBattle;

class CGame2CenterGuildBattleC : public CGame2CenterGuildBattleClt
{
    public:
        virtual ~CGame2CenterGuildBattleC();

        //接收：帮派等级更新
        virtual void OnRecv_GuildLevelChanged(
                UINT64 qwGuildID, //帮派对应ID
                UINT16 wLevel //帮派等级
                );

        //接收：帮主更新
        virtual void OnRecv_GuildOwnerChanged(
                UINT64 qwGuildID, //帮派对应ID
                const std::string& strGuildOwnerName //帮主名称
                );

        //接收：帮派解散
        virtual void OnRecv_GuildDisband(
                UINT64 qwGuildID //帮派对应ID
                );

        //接收：可以发送新帮派战数据
        virtual void OnRecv_ReadyToSendNewGuildBattle(
                );

};

#endif // #ifndef GAME_2_CENTER_GUILD_BATTLE_C_H
