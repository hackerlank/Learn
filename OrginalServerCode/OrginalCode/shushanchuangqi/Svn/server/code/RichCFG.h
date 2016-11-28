// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SRichCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CRICHLOADER_H
#define _CRICHLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SRichCFG
{
	/**
	层数Id
	**/
	UINT8	_ID;

	/**
	小宝箱掉落包
	**/
	UINT16	_SmallBoxDropGroup;

	/**
	大宝箱掉落组
	**/
	UINT16	_BigBoxDropGroup;

	/**
	超级宝箱掉落组
	**/
	UINT16	_SuperBoxDropGroup;

	/**
	普通怪组
	**/
	string	_NormalDropGroup;

	/**
	精英怪组
	**/
	string	_EliteDropGroup;

	/**
	Boss怪组
	**/
	string	_BossDropGroup;

	/**
	三消奖励组1
	**/
	string	_ChrushDropGroup1;

	/**
	三消奖励组2
	**/
	string	_ChrushDropGroup2;

	/**
	三消奖励组3
	**/
	string	_ChrushDropGroup3;

	/**
	三消奖励组4
	**/
	string	_ChrushDropGroup4;

	/**
	拼图奖励
	**/
	string	_PicDropGroup;

	/**
	抽卡掉落组
	**/
	string	_DrawDropGroup;

	/**
	大宝箱奖励预览
	**/
	UINT16	_SuperBoxPV;

	/**
	进入预告
	**/
	string	_WelcomeWord;
}; // SRichCFG define end

//data loader for the excel table
class CRichLoader
{
public:
	std::vector<SRichCFG*> _vecData;

	~CRichLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

