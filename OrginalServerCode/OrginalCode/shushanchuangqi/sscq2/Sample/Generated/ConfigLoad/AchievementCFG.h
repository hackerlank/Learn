// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAchievementCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACHIEVEMENTLOADER_H
#define _CACHIEVEMENTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAchievementCFG
{
	/**
	成就ID
	**/
	UINT16	_ID;

	/**
	成就大类
	**/
	UINT16	_Type;

	/**
	成就子类1
	**/
	UINT16	_Type1;

	/**
	成就子类2
	**/
	UINT16	_Type2;

	/**
	职业
	**/
	UINT8	_Career;

	/**
	成就名
	**/
	string	_Name;

	/**
	成就描述
	**/
	string	_Desc;

	/**
	事件id
	**/
	UINT16	_EventID;

	/**
	事件序列
	**/
	string	_EventGroup;

	/**
	文字资源名
	**/
	string	_AssetsText;

	/**
	成就点
	**/
	UINT16	_AP;

	/**
	特殊奖励类型
	**/
	UINT16	_AwardType;

	/**
	特殊奖励参数
	**/
	UINT16	_AwardPara;

	/**
	完成奖励
	**/
	string	_AwardId;

	/**
	描述
	**/
	string	_AwardInfo;

	/**
	是否可被分享
	**/
	UINT8	_Share;

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
}; // SAchievementCFG define end

//data loader for the excel table
class CAchievementLoader
{
public:
	std::vector<SAchievementCFG*> _vecData;

	~CAchievementLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

