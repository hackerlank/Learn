#pragma once
#include "Game2DBCommClt.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;
using namespace NGame2DBComm;

class CPlayer;
class CUser;
class CGame2DBCommC : public CGame2DBCommClt
{
    public:
        //接收：帐号协议代理发送请求
        virtual void OnRecv_UserPackageProxy(
                UINT64 qwUsrID, //帐号ID
                UINT32 dwGateID, //所在网关服务器ID
                const TVecString& vecPackage //协议包列表
                );

        //  virtual void OnRecv_UserLogoutNtf(UINT64 qwUserId,NServerCommon::ELeaveType type);
        //接收：DB向GameSever推送角色信息/
        virtual void OnRecv_UserLoginNtf(
                EEnterType eEnterType, //进入的类型
                const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
                const TVecString& vecEnterString, //平台相关参数
                UINT32 dwGateId, //网关Id
                UINT64 qwUserId, //用户Id
                const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
                ) ;


        //接收：账号重新进入通知
        virtual void OnRecv_UserReEnterNotify(
                UINT64 qwUsrID, //账号ID
                UINT32 dwGateID, //所在网关服务器ID
                const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
                const TVecString& vecEnterString //平台相关参数
                ) ;

        //接收：账号退出DBServer通知
        virtual void OnRecv_UserLogoutNtf(
                UINT64 qwUsrID, //账号ID
                NServerCommon::ELeaveType eLeaveType //下线类型
                ) ;
        //接收：离线事件通知
        virtual void OnRecv_NewOffEventNotice(
                UINT64 qwUsrID, //账号ID
                const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
                );
        //接收：新帮派战历史记录获取返回
        virtual void OnRecv_NewGuildBattleHistoryNotify(
                UINT32 dwCurSize, //已发送条数
                UINT32 dwTotalSize, //总条数
                const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
                );


                void TimerCheck();
                bool IsDBInited() const { return _bDBInited; }
                CGame2DBCommC() : _bDBInited(false), _bTimerClosed(false) { }

                bool PlayerEnterMap(CPlayer& rPlayer);
                void UserReEnterGame(CUser& rUser, UINT32 dwGateID, EEnterType eEnterType,const NProtoCommon::TVecPlatformParam& vecPlatformParam, const TVecString& vecString, const NRoleInfoDefine::RoleDataInfo *pRoleData = NULL);
                bool PlayerReEnterGame(CPlayer& rPlayer);
                bool SaveDataReq(CUser& rUser, ESaveType eSaveType,const TVecPlatformParam& vecPlatformParam );
                bool SaveDataReq(CPlayer& rPlayer, ESaveType eSaveType,const TVecPlatformParam& vecPlatformParam );
                static void OnReturn_SaveUserDataReq(
                        UINT8 byRet_, //0为成功，1为失败，2为超时
                        UINT64 qwUsrID, //(本地保存的函数参数)账号ID
                        ESaveType eSaveType //(本地保存的函数参数)保存类型
                        );
                bool PlayerEnterSwitch(CPlayer& rPlayer);
                void OnLogin(CUser& rUser, EEnterType eEnterType);
                bool EnterWorldMap(CPlayer& rPlayer);
                bool EnterDgn(CPlayer& rPlayer);
                void UserLoadOverFromClient(CPlayer& rPlayer,UINT8 byLoadRet);


    private:
                void CheckFirstLogin(CPlayer& rPlayer);
                //      void AddLoadWait(UINT64 dwUserId,bool bReEnter,EEnterType eEnterType);
                //      void UserLoadOver(CPlayer& rPlayer,UINT8 byLoadRet,bool bReEnter,EEnterType eEnterType);

    private:
                bool _bDBInited;
                bool _bTimerClosed;
                //        map<UINT64,WaitEnterMapData> _mapWaitEnterMap;
};
