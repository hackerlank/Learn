#pragma once

#include "ace\ACE.h"
#include "ace\Message_Block.h"

/*
#define MESSAGE_TYPE_TASK 0x01
#define MESSAGE_TYPE_KERNAL 0x02
#define MESSAGE_TYPE_TIMER 0x03
#define MESSAGE_TYPE_USER 0x04
*/

extern char public_send_buff[81920];

//#define MAX_MESSAGE_BODY_SIZE 4096

enum
{
	SERVICE_MESSAGE_ACT_READ = 0,
	SERVICE_MESSAGE_ACT_WRITE
};

enum
{
	SERVICE_MESSAGE_TYPE_CTRL = 0,
	SERVICE_MESSAGE_TYPE_TASK,//任务
	SERVICE_MESSAGE_TYPE_TIMER,//定时器
	SERVICE_MESSAGE_TYPE_OBJ_LOCATION,//
	SERVICE_MESSAGE_TYPE_DB_REQUEST,//db 请求
	SERVICE_MESSAGE_TYPE_DB_RESPONSE,//db server 返回
	SERVICE_MESSAGE_TYPE_DB_REQUEST_ACK,//db server 应答确认消息
	SERVICE_MESSAGE_TYPE_SYSTEM,//系统消息
	SERVICE_MESSAGE_TYPE_USER,//UserInfoMgr
};

#define SERVICE_MESSAGE_CTRL_NONE 0x00000000
#define SERVICE_MESSAGE_CTRL_NEED_QUERY_LOCATION 0x00000001
#define SERVICE_MESSAGE_CTRL_TO_INTERNET 0x40000000
#define SERVICE_MESSAGE_CTRL_FROM_INTERNET 0x80000000

#define MAKE_MSG_TYPE(g, t) ((g << 16) | t)

typedef struct tagObjAdr
{
	ACE_UINT32 unServiceID;
	ACE_UINT32 unAdapterID;
	ACE_UINT32 unObjID;
	ACE_UINT32 unTaskID;
}ObjAdr;

typedef struct tagPacketHead
{
	ACE_UINT32 unType;
	//ACE_UINT32 unSessionID;
	ACE_UINT32 unCtrlCode;
	//ACE_UINT32 unSN;
}PacketHead;

typedef struct tagServiceHead
{
	ObjAdr desAdr;
	ObjAdr srcAdr;
}ServiceHead;

/*
typedef struct tagClientHead
{
	ACE_UINT32 unMsgCount;
}ClientHead;
*/

typedef struct tagMsgInfoHead
{
	ACE_UINT32 unSig;
	ServiceHead s_head;
}MsgInfoHead;;


typedef struct tagMessageHead
{
	ACE_UINT32 unType;
	ACE_UINT32 unPacketNO;
}MessageHead;

typedef struct tagMessageInfo
{
	ACE_Message_Block *msg;
	PacketHead *p_head;
	MsgInfoHead *i_head;
	ServiceHead *s_head;
	//ClientHead *c_head;
	MessageHead *m_head;
	void *body;
	int nBodySize;
}MessageInfo;

extern int allocMessageWithInfo(MessageInfo &info, ACE_UINT32 unBodySize, ACE_UINT32 unType, ACE_UINT32 unDesServiceID, 
								ACE_UINT32 unDesAdapterID, ACE_UINT32 unDesObjID, ACE_UINT32 unSrcServiceID, ACE_UINT32 unSrcAdapterID, ACE_UINT32 unSrcObjID, ACE_UINT32 unMsgType);
extern int parseMsg(MessageInfo &info, ACE_Message_Block *msg);
extern ACE_Message_Block *allocServiceMessage(int nAct, ACE_UINT32 unBodySize = 4096);
extern void resetServiceMessage(ACE_Message_Block &msg, int nAct);

typedef struct tagMsgCommonRequest
{
	ACE_UINT32 unType;
	ACE_UINT32 unSize;
	char data[1];
}MsgCommonRequest;

typedef struct tagMsgCommonResponse
{
	ACE_UINT32 unType;
	ACE_UINT32 unSize;
	ACE_INT32 nRet;
	char data[1];
}MsgCommonResponse;

typedef struct tagMsgDBBaseResponse
{
	int nResult;
}MsgDBBaseResponse;

#define PACKET_HEAD_SIZE (sizeof(PacketHead) + sizeof(MsgInfoHead) + sizeof(MessageHead))

//订单信息
#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )
#define RECHARGE_ORDERID_LEN 32 //充值orderid长度
//#define  RECHARGE_STATE_TRUE 2 //可领取状态
#define  RECHARGE_STATE_FLAG 1 //已领取状态
#define  RECHARGE_STATE_FALSE 0//创建状态

#define  RECHARGE_ORDER_SUCCESS 0 //成功
#define  RECHARGE_ORDER_ERROR -1 //失败
#define  RECHARGE_ORDER_NOT_EXIST -2//订单号不存在
#define  RECHARGE_ORDER_COMPLETED -3//已领取
#define  RECHARGE_ORDER_USER_ID_ERROR -4//角色id不匹配
#define  RECHARGE_ORDER_PayState_ERROR -5//支付状态不是1
#define  RECHARGE_ORDER_ProductId_ERROR -6//商品id不一致
#define  RECHARGE_ORDER_ProductCount_ERROR -7//商品数量不一致
#define  RECHARGE_ORDER_Product_NOT_EXIST -8//商品不存在
#define  RECHARGE_ORDER_Renminbi_ERROR -9//充值人民币比实际需要的商品金额少
#define  RECHARGE_ORDER_ZONE_ERROR -10//区号不对

#define  RECHARGE_CHANNEL_LEN 16

typedef struct tagOrderInfo
{
	tagOrderInfo()
	{
		ZeroVar(*this);
	}
	char orderID[RECHARGE_ORDERID_LEN+1];//充值头
	ACE_UINT32  unCharacterID;//充值用户id
	ACE_UINT32 creat_time;//订单创建时间
	ACE_INT32	unProductId;//商品id
	ACE_UINT32 unProductCount;//购买商品数量
	ACE_INT32  state;//当前状态（是否已经领取）
	ACE_UINT32  unMoney;//充值金卡数量
	ACE_UINT32  unFlagEx;//送的钱
	ACE_UINT32 unRenminbi;
	char  strChannel[RECHARGE_CHANNEL_LEN + 1];//充值渠道id
	ACE_UINT32 unbitfield;
}OrderInfo;

#define  RECHARGE_MAX_PRODUCT 32
typedef struct tagProductList
{
	tagProductList()
	{
		ZeroVar(*this);
	}
	ACE_UINT32 unCount;
	ACE_UINT32 list[RECHARGE_MAX_PRODUCT];
}ProductList;

typedef struct tagVipInfo
{
	ACE_UINT32 vip_level;
	ACE_UINT32 vip_amount;
}VipInfo;

typedef struct tagVipGift
{
	tagVipGift()
	{
		ZeroVar(*this);
	}
	ACE_UINT32 unCount;
	ACE_UINT32 list[RECHARGE_MAX_PRODUCT];
}VipGift;