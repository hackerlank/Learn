#pragma once
#include "LingShanProtSvr.h"
using namespace NLingShanProt;

class CLingShanProtS : public CLingShanProtSvr
{
    //接收：获取状态（回StatusNotify通知）
	virtual void OnRecv_GetStatus(
	);

	//接收：活动报名
	virtual bool OnRecv_Reg(
		shared_func<SRegAck>& fnAck //返回回调函数
	);

	//接收：当前棋盘状态
	virtual bool OnRecv_GetMatchInfo(
		shared_func<SGetMatchInfoAck>& fnAck //返回回调函数
	);

	//接收：获取自己的比赛信息
	virtual bool OnRecv_GetMathSelInfo(
		shared_func<SGetMathSelInfoAck>& fnAck //返回回调函数
	);

	//接收：更换模型信息
	virtual bool OnRecv_ChangeModel(
		UINT32 dwModelID, //模型id
		shared_func<SChangeModelAck>& fnAck //返回回调函数
	);


	//接收：移动选择
	virtual bool OnRecv_MoveSelect(
		UINT16 wPos, //位置
		shared_func<SMoveSelectAck>& fnAck //返回回调函数
	);

	//接收：获取活动信息
	virtual bool OnRecv_GetActInfo(
		shared_func<SGetActInfoAck>& fnAck //返回回调函数
	);

	//接收：聊天
	virtual bool OnRecv_Chat(
        const std::string& strChatMsg, //聊天内容 
		shared_func<SChatAck>& fnAck //返回回调函数
	);

	//接收：获取房间信息
	virtual bool OnRecv_GetRoomList(
		shared_func<SGetRoomListAck>& fnAck //返回回调函数
	);

	//接收：进入参观房间
	virtual bool OnRecv_EnterVisitRoom(
		UINT16 wRoomID, //房间id
		shared_func<SEnterVisitRoomAck>& fnAck //返回回调函数
	);

	//接收：离开参观房间
	virtual bool OnRecv_LeaveVisitRoom(
		shared_func<SLeaveVisitRoomAck>& fnAck //返回回调函数
	);

	//接收：获取动画播放信息
	virtual bool OnRecv_GetPlayMovieInfo(
		shared_func<SGetPlayMovieInfoAck>& fnAck //返回回调函数
	);

public:
public:
};
extern CLingShanProtS g_LingShanProtS;
