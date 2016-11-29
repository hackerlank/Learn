#pragma once
#include "DBRoleData.h"
#include <Singleton.h>
#include <queue>
#include <RoleEnterGameProt.h>
#include <unordered_map>

using namespace NRoleEnterGameProt;
using namespace NProtoCommon;

const UINT32 MAX_ROLENAME_LENGTH = 15;       // 最大5个中文 5*3
const UINT32 MIN_ROLENAME_LENGTH = 4;        // 最小4个英文 4*1，或者两个中文 2*3，取最小值 4
typedef function<void(SDBRoleData*, EEnterResult)>  LoadUserFun;
typedef vector<LoadUserFun> VecLoadFun;
enum ELoadSource
{
    eLoadUpdate,//更新加载
    eLoadOterSvr,//其他服务加载
    eLoadOnLine,//上线加载
 };
typedef map<ELoadSource,VecLoadFun> mapLoadFun;
struct SDBRoleData;
class CDBRoleMgr : public Singleton<CDBRoleMgr>
{
    public:
        CDBRoleMgr() {}
        virtual ~CDBRoleMgr();

        SDBRoleData* GetRoleData(UINT64 qwRoleID);
        void CreateRole(UINT64 qwRoleID,const SCreateRoleInfo & stCreateData, function<void(SDBRoleData*, ECreateRoleResult)> cb);

        //    void CheckNameAvailable(const string& strName, function<void(ECreateRoleResult)> cb);
        //    void GetRoleIDbyName(const string& strName, function<void(UINT64)> cb);

        void LoadRoleData(UINT64 qwRoleID,ELoadSource eSource, function<void(SDBRoleData*, EEnterResult)> funcLoaded);
        bool CheckRoleState(SDBRoleData* pData,bool IsUpdate);
        //bool EnterGame(SDBRoleData& rRoleData);

        bool EnterGame(SDBRoleData& rRoleData, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString);
        void SavePlayer(bool bIsALL);
        bool SendDataToGameServer(SDBRoleData& rRoleData,EEnterType eEnterType,const TVecPlatformParam &vecPlatformParam, const TVecString& vecString);

        void GateOff(UINT32 dwGateId);
        //UINT32 GetGameSvrIDByMapID(SDBRoleData& rRoleData);
        UINT8 GetFreeDBLine(UINT64 qwRoleID);
        void TimerCheck(time_t tNow);
        //收到一条更新消息
        void OnRecv_RoleDataUpdate(
                UINT64 qwRoleId, //角色Id
                EDataType eDataType, //更新数据块
                EDataChange eUpdateType, //更新类型，增加，删除，修改
                const std::string& strData //更新数据
                );
        bool EnterGame(SDBRoleData& rRoleData);
        bool ReEnterGame(SDBRoleData& rRoleData,UINT32 dwGateId, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString);
        bool AddLoadOrCreate(UINT64 qwRoleId);
        void RemoveLoadOrCreate(UINT64 qwRoleId);
        void KickUserOffLine(UINT64 qwUsrID, bool bException = false);
        bool JumpToCrossServer(SDBRoleData& rRoleData, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString);
        bool JumpGameServer(SDBRoleData& rRoleData, const TVecPlatformParam& vecPlatformParam, const TVecString& vecString);
        void GetAllInfo(NRoleInfoDefine::RoleDataInfo &rInfo,SDBRoleData& rRoleData);
        bool JumpFromCrossServer(SDBRoleData& rRoleData ,const TVecPlatformParam& vecPlatformParam, const TVecString& vecString);

        // 更新角色数据
        //void UpdateRoleData(UINT64 uRoleID, const TVecSaveData& vecData);

        // 防沉迷检查：登陆检查
        //void CheckWallow(SDBRoleData& rRoleData);
        // 更新防沉迷：登出更新
        //void UpdateWallow(SDBRoleData& rRoleData);

        void NoticeLeaveAway(UINT64 qwRoleID);
        bool  OnRecv_SaveOffLineDgnInfo(
                UINT64 qwUsrID, //账号ID
                UINT32 dwDgnType, //副本类型
                UINT8 byIsFail //0:表示成功保存，1：表示失败保存
                ); 

        void GetAllPlatformParam(UINT32 dwPageSize);

        void SendPlatformParamToCenter(UINT32 dwTotalPage, UINT32 dwTotalSize, const TVecUINT64& rvecRoleID, const TVecPlatformParam& rvecPlatform) const;

    private:
            // 获得角色在服务器的名字，以后方便合服
            //  string GetRoleServerName(const string& strClientName, UINT64 qwRoleID);

    private:
            bool AddRoleData(SDBRoleData& rRoleData);
            void DelRoleData(SDBRoleData* pRoleData);
            void DoCreateRole( SDBRoleData* pRoleData,const RoleBaseInfo &stCreatedata ,function<void(SDBRoleData*, ECreateRoleResult)> cb );

            void QueryPlatformParamData(UINT32 dwPageSize,QueryFun queryfun);
         
            void DoLoadOver(UINT64 qwRoleID,SDBRoleData* pRoleData,
                    EEnterResult result);
            bool InsertLoad(UINT64 qwRoleID,ELoadSource eSource,LoadUserFun fun);
    private:
            unordered_map<UINT64, SDBRoleData*> _mapRole2Data;
            queue<UINT64> _queueUpdate;
            queue<UINT64> _queueOffLine;
            set<UINT64> _setLoadOrCreate;
            unordered_map<UINT64,UINT32> _mapLeaveAway;
            map<UINT64,mapLoadFun > map_InLoad;
};

