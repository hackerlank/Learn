#pragma once
#include "RoleEnterGameProtSvr.h"

using namespace NRoleEnterGameProt;
using namespace NRoleInfoDefine;
class SDBRoleData;
class CRoleEnterGameProtSvrS : public CRoleEnterGameProtSvr 
{
public:
    
  virtual void OnRecv_EnterGameReq(
          const SEnterParam& stEnterParam //创角信息
	);

     //接收：创建角色请求
     virtual void OnRecv_CreateRoleReq(
             const SCreateRoleInfo& stCreateInfo //创角信息
             );
     //接收：玩家请求推荐名字
	virtual void OnRecv_PlayerRamdomNameReq(
        UINT8 byIsMale
	) ;
    //接收：玩家请求角色信息
    virtual void OnRecv_GetUserInfo(
	);
private:
    void InitUserInfoFromDB(SDBRoleData& pRoleData,RoleEnterGameData& stRoleEnterInfo);

};
