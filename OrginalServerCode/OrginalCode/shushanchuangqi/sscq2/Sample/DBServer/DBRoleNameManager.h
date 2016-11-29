#ifndef ROLENAMEMANAGER_H__
#define ROLENAMEMANAGER_H__

#include <Linux.h>
#include <Singleton.h>
using namespace std;
#include <map>
#include <functional>
#include <string>
#include <vector>
#define RandomMaxTimes 1000
#define MinNameNums  1
#define MaxNameNums  1
typedef function<void(INT8,UINT32)> QueryFun;

class RoleNameManager: public Singleton<RoleNameManager>
{
    public:
        RoleNameManager():_dwUserNum(0) {}
        virtual ~RoleNameManager() {}

        //插入一条名字记录：用于创建角色成功
        bool  AddPlayerName(UINT64 qwRoleId, const string& strName, bool DBmark=false);
        //根据名字得到玩家Id
        UINT64  GetPlayerIdByName(const string& strName);
        //初始化
        bool Init(bool bIsMerge,QueryFun fun);
        //重名检查:用于创建角色
        bool CheckNameIsExist(const string& strName);
        //根据取名string,和服标记，和RoleId,生成服务器唯一名字：用于从数据库加载后生成名字
        string MakeName(UINT64 qwRoleId,const string& strName);
        //检查是否有这个Id
        bool HasRole(UINT64 qwRoleId);
        //根据Id得到名字
        string GetPlayerName(UINT64 qwRoleId);
    public:
        bool LoadRandomName(const string& strFileName);//加载随机名字文件
        bool CreateRandomName(UINT64 qwRoleId,bool bIsMale,string& strPlayerName);//生成一个随机名字
        void GetAllUserIDAndName();
    private:
        //加载玩家的名字
        void LoadUserName(QueryFun fun);
    private:
        map<string,UINT64> _mapName;//名字索引
        map<UINT64,string> _mapId;//ID
        bool _bIsMerge;//是否已经合服
        vector<string> _vecRandomMaleSurname;//男姓
        vector<string> _vecRandomMaleName;//男名
        vector<string> _vecRandomFemaleSurname;//女姓
        vector<string> _vecRandomFemaleName;//女名
        UINT32 _dwUserNum;



};
#endif
