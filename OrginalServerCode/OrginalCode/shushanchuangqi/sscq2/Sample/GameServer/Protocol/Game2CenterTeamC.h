#pragma once
#include "Game2CenterTeamClt.h"
#include "RoleInfoDefine.h"
using namespace NGame2CenterTeam;


class CGame2CenterTeamC : public CGame2CenterTeamClt
{
    public:
        //接收：玩家请求加入，创建队伍
	virtual bool OnRecv_CanEnterCreateTeam(
		UINT64 qwUsrID, //帐号ID
        UINT8 byHeroNum, //1,需要将，0，不需要将
        UINT16 wDgnType, //副本模板
		shared_func<SCanEnterCreateTeamAck>& fnAck //返回回调函数
	);
    //接收：根据实例拉取将外观
	virtual bool OnRecv_GetFighterFeatureByInsID(
		UINT64 qwUsrID, //帐号ID
		UINT64 qwFighterID, //将ID
		shared_func<SGetFighterFeatureByInsIDAck>& fnAck //返回回调函数
	);
	//接收：玩家加入/离开队伍信息同步
	virtual void OnRecv_SynTeam(
		UINT64 qwUsrID, //帐号ID
		EPlayerTeam eStatus //玩家操作
	);
	//接收：获取玩家战斗信息
	virtual bool OnRecv_GetPlayerBattleInfo(
        UINT64 qwUsrID, //帐号ID
		UINT8 byPlayerPos, //玩家所在的队伍位置
		const TVecUINT64& vecFigther, //散仙唯一ID
        const TVecUINT8& vecPos, //玩家序列位置
        UINT8 byNeedPet, //0,不需要阵灵，1需要阵灵
		UINT16 wDgnType, //副本类型
		shared_func<SGetPlayerBattleInfoAck>& fnAck //返回回调函数
	);
    //接收：请求发起战斗
	virtual bool OnRecv_StartBattle(
        UINT64 qwUsrID, //帐号ID
		UINT16 wDgnType, //副本类型
		const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
		shared_func<SStartBattleAck>& fnAck //返回回调函数
	) ;
	//接收：通告战斗结果
	virtual void OnRecv_NoticeTeamReport(
		UINT64 qwUsrID, //帐号ID
		UINT16 wDgnType, //副本类型
		const TeamReport& stTeamReport, //副本类型
		UINT32 dwRewardRate //奖励系数
	);
   public:
    //将升级,主将换装
    void UpFighter2Center(UINT64 qwUsrID,UINT64 qwFighterID);
    //其他外观：如职业，性别，阵灵等，以后做 
    void SyncBeautyInfo(UINT64 qwRoleId);

   private:
    NTeamGS::CommonFighterPtr GetTeamFighterByID(CPlayerPtr pPlayer,UINT64 qwFighterID);
    
};

extern CGame2CenterTeamC g_Game2CenterTeamC;

