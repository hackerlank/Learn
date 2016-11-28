// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFriendInvitePrizeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFRIENDINVITEPRIZELOADER_H
#define _CFRIENDINVITEPRIZELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFriendInvitePrizeCFG
{
	/**
	奖励idID
	**/
	UINT32	_ID;

	/**
	所属切页
	**/
	UINT8	_MainId;

	/**
	奖励类型
	**/
	UINT8	_Type;

	/**
	发送邀请好友数量
	**/
	UINT32	_SendInviteCnt;

	/**
	好友等级
	**/
	UINT8	_FriendLevel;

	/**
	好友vip等级
	**/
	UINT8	_VipLevel;

	/**
	好友冲值金额
	**/
	UINT32	_BuyGold;

	/**
	达到前面条件的好友数量
	**/
	UINT32	_GoodFriendCnt;

	/**
	奖励id
	**/
	string	_Prize;
}; // SFriendInvitePrizeCFG define end

//data loader for the excel table
class CFriendInvitePrizeLoader
{
public:
	std::vector<SFriendInvitePrizeCFG*> _vecData;

	~CFriendInvitePrizeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

