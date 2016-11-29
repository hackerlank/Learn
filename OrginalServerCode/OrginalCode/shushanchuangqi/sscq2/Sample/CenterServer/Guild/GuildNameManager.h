#ifndef GUILD_NAME_MANAGER_H
#define GUILD_NAME_MANAGER_H

#include <Linux.h>
#include <Singleton.h>
using namespace std;
#include <map>
#include <functional>
#include <string>
#include <vector>

#include "GuildProt.h"

using namespace NGuildProt;

class CGuildNameManager: public Singleton<CGuildNameManager>
{
    public:
        CGuildNameManager():_bIsMerged(false){}
        //插入一条名字记录：用于创建角色成功
        bool  AddGuildName(UINT64 qwGuildID,const string& strName);
        //删除一条名字记录
        bool  DelGuildName(const string& strName);
        //根据名字得到帮派ID
        UINT64  GetGuildIDByName(const string& strName);
        //初始化
        bool Init(bool bIsMerged);

        // 检查名字
        ECreateResult CheckName(const string& strName);
        //重名检查:用于创建角色
        bool CheckNameIsExist(const string& strName);
        //根据取名string,和服标记，和GuildID,生成服务器唯一名字：用于从数据库加载后生成名字
        string MakeName(UINT64 qwGuildID,const string& strName);
        //检查是否有这个ID
        bool HasGuild(UINT64 qwGuildID);
        //根据ID得到名字
        string GetGuildName(UINT64 qwGuildID);
    private:
        //加载帮派的名字
        void InitGuildName();
    private:
        map<string,UINT64> _mapName;//名字索引
        map<UINT64,string> _mapID;//ID
        bool _bIsMerged;//是否已经合服
};
#endif // #ifndef GUILD_NAME_MANAGER_H
