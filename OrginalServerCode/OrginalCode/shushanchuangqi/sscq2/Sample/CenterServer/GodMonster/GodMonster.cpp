
#include "stdafx.h"
#include "Protocols.h"
#include "GodMonster.h"
#include "GuildMgr.h"
#include "Guild.h"
#include "GodMonsterMgr.h"

CGodMonster::CGodMonster(UINT64 qwGuildID) :
    _qwGuildID(qwGuildID),
    _dwScore(0),
    _byPeroid(1)
{ }

CGodMonster::~CGodMonster() 
{
    
}

bool  CGodMonster::CheckUserByID(UINT64 qwRoleID)
{
    GodMonsterUserPtr p = GetUserInfoByID(qwRoleID);
    if(!p)
        return false;
    return true;
}

GodMonsterUserPtr CGodMonster::GetUserInfoByID(UINT64 qwRoleID)
{
    if(!qwRoleID)
        return NULL;
    auto it = _mapID2UserPtr.find(qwRoleID);
    if(it == _mapID2UserPtr.end())
    {
        //LOG_INF <<"qwRoleID(" << qwRoleID <<") notFinded.";
        return NULL;
    }
    return it->second;
}

bool  CGodMonster::AddUser(GodMonsterUserPtr pUser)
{
    UINT64 qwRoleID = pUser->GetRoleID();
    if(!CheckUserByID(qwRoleID))
    {
        if(!_mapID2UserPtr.insert(make_pair(qwRoleID,pUser)).second)
        {
            LOG_INF<<"Insert qwRoleID=" << qwRoleID<<" Err.";
            return false;
        }
    }
    pUser->Update2DB(); 
    return true;
}

void  CGodMonster::DeleteUser(UINT64 qwRoleID)
{
    if(CheckUserByID(qwRoleID))
    {
       auto it = _mapID2UserPtr.find(qwRoleID);
       _mapID2UserPtr.erase(it); 
    }
}

void CGodMonster::AddScore(UINT32 dwTmp)
{
    _dwScore += dwTmp;
    LOG_CRI <<" qwMonsterID="<<_qwGuildID<<",AddScore="<<dwTmp<<",总积分："<<_dwScore;
    CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(_qwGuildID);
    if(!pGuild)
        return ;
    //pGuild->SetScore(_dwScore);
    pGuild->SetDirty(eGDTBaseInfo);
    pGuild->Update2DB(pGuild,eOpUpdate,_qwGuildID);
    
    //判断神兽处于什么阶段
    UINT8 byOldPeroid = _byPeroid;
    GodMonsterCFGPtr pEx = g_GodMonsterMgr.GetConfig(eGodMonsterConfig,byOldPeroid + 1);
    if(_dwScore >= pEx->wFieldDown)
    {
        _byPeroid += 1;
        LOG_INF << "Monster(" <<_qwGuildID<<") grow next peroid("<<_byPeroid<<") Suc.";
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

