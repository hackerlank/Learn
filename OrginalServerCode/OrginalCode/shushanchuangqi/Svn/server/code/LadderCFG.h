// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLadderCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLADDERLOADER_H
#define _CLADDERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLadderCFG
{
	/**
	排名
	**/
	UINT32	_RankId;

	/**
	积分
	**/
	UINT32	_Score;

	/**
	排名奖励掉落包
	**/
	UINT32	_RankLootId;

	/**
	历史最高排名奖励
	**/
	string	_RankHighestAward;

	/**
	机器人Id
	**/
	UINT16	_RobotMonsterId;
}; // SLadderCFG define end

//data loader for the excel table
class CLadderLoader
{
public:
	std::vector<SLadderCFG*> _vecData;

	~CLadderLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

