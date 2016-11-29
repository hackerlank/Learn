// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDragonBallCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDRAGONBALLLOADER_H
#define _CDRAGONBALLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDragonBallCFG
{
	/**
	期数
	**/
	UINT16	_cid;

	/**
	天数
	**/
	UINT8	_Daytime;

	/**
	比例
	**/
	UINT8	_Fanl;

	/**
	额度
	**/
	UINT32	_Cost;

	/**
	等级
	**/
	string	_Desc;

	/**
	奖励
	**/
	string	_Award;
}; // SDragonBallCFG define end

//data loader for the excel table
class CDragonBallLoader
{
public:
	std::vector<SDragonBallCFG*> _vecData;

	~CDragonBallLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

