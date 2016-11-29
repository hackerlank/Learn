
#pragma once
#include "TeamGSSvr.h"
using namespace NTeamGS; 
typedef boost::function<void (ETEAMResult eResult,const NBattleGS::TVecBattleFighter& vecFighter,const TVecUINT64& vecErrPlayer)> ResultFun;
struct SynRecord
{
    public:
    SynRecord(ResultFun fun):_fun(fun),_eResult(ETeam_Suc){}
    void Finish(ETEAMResult eResult,const NBattleGS::TVecBattleFighter &vecFighter,UINT64 qwRoleID =0 )
    {
        if(eResult != ETeam_Suc)
        {
            if(qwRoleID != 0)
            {
                _vecErr.push_back(qwRoleID);
            }
            _eResult = eResult;
        }
        else 
        {
            _vecFighter.insert(_vecFighter.end(),vecFighter.begin(),vecFighter.end());
        }

    }
    ~SynRecord()
    {
        _fun(_eResult,_vecFighter,_vecErr);
    }
   private:
    ResultFun _fun;
    NBattleGS::TVecBattleFighter _vecFighter;
    TVecUINT64 _vecErr;
    ETEAMResult _eResult;
};
typedef shared_ptr<SynRecord> SynRecordPtr;
class CTeamGSS : public CTeamGSSvr
{
public:	
	//接收：根据模板查询可加入房间
	virtual bool OnRecv_GetTeamList(
		UINT16 DgnType, //房间ID
		shared_func<SGetTeamListAck>& fnAck //返回回调函数
	);
    //接收：停止查询
	virtual void OnRecv_StopTeamList(
	) ;
	//接收：请求创建房间
	virtual bool OnRecv_CreateTeam(
		UINT16 DgnType, //副本类型
        const TeamSetting& stSetting, //队伍设置
		shared_func<SCreateTeamAck>& fnAck //返回回调函数
	);

	//接收：请求加入房间
	virtual bool OnRecv_EnterTeam(
        UINT32 dwTeamID, //房间ID
        UINT32 dwPassWord,
		shared_func<SEnterTeamAck>& fnAck //返回回调函数
	);

	//接收：请求更换将
	virtual bool OnRecv_ResetFigter(
		UINT64 qwNewFighter, //新将
        UINT8 byPos, //将位置 
		shared_func<SResetFigterAck>& fnAck //返回回调函数
	);

	//接收：交换自己的将位置
	virtual bool OnRecv_ChangeSelfPos(
		UINT8 byPos1, //第1个位置
		UINT8 byPos2, //第2个位置
		shared_func<SChangeSelfPosAck>& fnAck //返回回调函数
	) ;

    //接收：交换列的位置
	virtual bool OnRecv_ChangeArrayPos(
		UINT8 byPos1, //第1个位置
		UINT8 byPos2, //第2个位置
		shared_func<SChangeArrayPosAck>& fnAck //返回回调函数
	) ;

	//接收：请求离开房间
	virtual bool OnRecv_LeaveTeam(
		shared_func<SLeaveTeamAck>& fnAck //返回回调函数
	);

	//接收：玩家已经准备好
	virtual bool OnRecv_DoReady(
		shared_func<SDoReadyAck>& fnAck //返回回调函数
	);

   //接收：玩家取消准备好
	virtual bool OnRecv_CancelDoReady(
		shared_func<SCancelDoReadyAck>& fnAck //返回回调函数
	) ;

	//接收：请求进入副本
	virtual bool OnRecv_EnterDgn(
		shared_func<SEnterDgnAck>& fnAck //返回回调函数
	);

	//接收：请求踢玩家出队伍
	virtual bool OnRecv_KickOffPlayer(
		UINT64 qwRoleID, //踢的人
		shared_func<SKickOffPlayerAck>& fnAck //返回回调函数
	);

	//接收：请求获得队伍信息
	virtual bool OnRecv_GetTeamInfo(
		shared_func<SGetTeamInfoAck>& fnAck //返回回调函数
	);
   //接收：换副本请求
	virtual bool OnRecv_ChangDgnType(
		UINT16 NewDgnType, //新副本类型
		shared_func<SChangDgnTypeAck>& fnAck //返回回调函数
	) ;
    //接收：换阵灵请求
	virtual bool OnRecv_ChangPet(
		UINT64 qwRoleID, //阵灵的主人
		shared_func<SChangPetAck>& fnAck //返回回调函数
	);
	//接收：更改设置请求
	virtual bool OnRecv_ChangSetting(
		const TeamSetting& stSetting, //队伍设置
		shared_func<SChangSettingAck>& fnAck //返回回调函数
	) ;
	//接收：换队长
	virtual bool OnRecv_ChangLeader(
		UINT64 qwNewLeader, //新队长ID
		shared_func<SChangLeaderAck>& fnAck //返回回调函数
	);

public:
    void SendSysMsgIDNotify(ETEAMResult  eResult,UINT64 qwRoleId);
    void GetMultiPlayerBattleInfo(const TVecUINT64& vecTeamUser,UINT32 dwTeamID,UINT16 wDgnType,ResultFun fun);
};

extern CTeamGSS g_CTeamGSS;
