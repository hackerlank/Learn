// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityPointCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTIVITYPOINTLOADER_H
#define _CACTIVITYPOINTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActivityPointCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	检测点
	**/
	UINT16	_Type;

	/**
	描述
	**/
	string	_strDesc;

	/**
	等级限制
	**/
	UINT16	_Level;

	/**
	跳转限制
	**/
	UINT16	_SkipLimit;

	/**
	单次活跃度
	**/
	UINT8	_GetActivity;

	/**
	参数
	**/
	string	_MaxTimes;

	/**
	是否可被分享
	**/
	UINT8	_Share;

	/**
	退出游戏时是否要提醒
	**/
	UINT8	_Remind;

	/**
	分享标题
	**/
	string	_Title;

	/**
	分享内容
	**/
	string	_Msg;

	/**
	宣传口号
	**/
	string	_Summary;

	/**
	按钮
	**/
	UINT8	_Button;

	/**
	图片
	**/
	UINT16	_Pic;

	/**
	排序
	**/
	UINT8	_ShareSort;

	/**
	分享名称
	**/
	string	_ShareName;

	/**
	分享描述
	**/
	string	_ShareDesc;

	/**
	分享宣传语
	**/
	string	_ShareSummary;

	/**
	分享奖励
	**/
	string	_ShareAwardId;
}; // SActivityPointCFG define end

//data loader for the excel table
class CActivityPointLoader
{
public:
	std::vector<SActivityPointCFG*> _vecData;

	~CActivityPointLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

