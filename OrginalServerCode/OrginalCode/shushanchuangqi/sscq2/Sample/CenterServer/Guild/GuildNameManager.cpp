#include "GuildNameManager.h"

#include "GUIDMgr.h"
#include "Tokenizer.h"
#include "tinyxml.h"

#include "NameCheckMgr.h"

using namespace NGuildProt;

const UINT32 MAX_GUILD_NAME_LENGTH = 15;       // 最大5个中文 5*3
const UINT32 MIN_GUILD_NAME_LENGTH = 4;        // 最小4个英文 4*1，或者两个中文 2*3，取最小值 4

const UINT32 DEFAULT_GUILD_HIGH_MARK = 100;
const UINT32 DEFAULT_GUILD_LOW_MARK = 20;

bool CGuildNameManager::AddGuildName(UINT64 qwGuildID,const string& strName)
{
    string name = MakeName(qwGuildID,strName);
    bool result = _mapName.insert(make_pair(name,qwGuildID)).second;
    if (result)
        _mapID[qwGuildID] = name;
    return result;
}

bool CGuildNameManager::DelGuildName(const string& strName)
{
    auto it = _mapName.find(strName);
    if (it != _mapName.end())
        _mapName.erase(it);
    return true;
}

string CGuildNameManager::MakeName(UINT64 qwGuildID,const string& strName)
{ 
    //XXX: 如果合服，加上区号
    if (!_bIsMerged)
        return strName; 
    UINT16 wGroupID = CGUIDMgr::GetGroupId(qwGuildID);
    string strServerName;
    strServerName.clear();
    strServerName = strName + ".";
    char szServerGroupID[32] = {0};
    snprintf(szServerGroupID, sizeof(strServerName), "%d", wGroupID);
    strServerName += szServerGroupID;
    return strServerName;
}

UINT64 CGuildNameManager::GetGuildIDByName(const string& strName)
{
    auto it = _mapName.find(strName);
    if (it == _mapName.end())
    {
        return 0;
    }
    return it->second;
}

bool CGuildNameManager::CheckNameIsExist(const string& strName)
{
    auto it = _mapName.find(strName);
    return it != _mapName.end();
}

ECreateResult CGuildNameManager::CheckName(const string& strName)
{
    /*
       if(strName.size() > MAX_GUILD_NAME_LENGTH)
       return eGCreateNameTooLong;

       if(strName.size() < MIN_GUILD_NAME_LENGTH)
       return eGCreateNameTooShort;
       */
    ENameLenRes res = CNameCheckMgr::CheckNameValid(const_cast<string&>(strName), MIN_GUILD_NAME_LENGTH,MAX_GUILD_NAME_LENGTH);
    switch (res)
    {
        case eNameLenTooShort:
            {
                return eGCreateNameTooShort;
            }
            break;
        case eNameLenTooLong:
            {
                return  eGCreateNameTooLong;
            }
            break;
        case eNameValid:
            {
                return eGCreateNameInvalid;
            }
            break;
        default:
            break;
    }
    string strServerGuildName = MakeName(0, strName);
    /*
    if (!CNameCheckMgr::CheckNameValid(strServerGuildName))
    {
        LOG_CRI << "wrong name :" << strServerGuildName;
        return eGCreateNameInvalid;
    }
    */
    if (CheckNameIsExist(strServerGuildName))
        return eGCreateNameExisted;

    return eGCreateSuccess;
}


bool CGuildNameManager::Init(bool bIsMerged)
{
    _bIsMerged = bIsMerged;
    return true;
}

string CGuildNameManager::GetGuildName(UINT64 qwGuildID)
{
    auto iter = _mapID.find(qwGuildID);
    if (iter != _mapID.end())
        return iter->second;
    return "";
}

bool CGuildNameManager::HasGuild(UINT64 qwGuildID)
{
    return _mapID.find(qwGuildID) != _mapID.end();
}

