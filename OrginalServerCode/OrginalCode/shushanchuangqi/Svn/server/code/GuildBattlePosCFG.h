// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildBattlePosCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDBATTLEPOSLOADER_H
#define _CGUILDBATTLEPOSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildBattlePosCFG
{
	/**
	位置编号
	**/
	UINT8	_Id;

	/**
	位置X坐标
	**/
	UINT16	_PosX;

	/**
	位置Y坐标
	**/
	UINT16	_PosY;

	/**
	角色朝向角度
	**/
	UINT16	_direction;
}; // SGuildBattlePosCFG define end

//data loader for the excel table
class CGuildBattlePosLoader
{
public:
	std::vector<SGuildBattlePosCFG*> _vecData;

	~CGuildBattlePosLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

