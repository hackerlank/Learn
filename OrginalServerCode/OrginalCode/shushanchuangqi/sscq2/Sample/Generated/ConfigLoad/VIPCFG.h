// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SVIPCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CVIPLOADER_H
#define _CVIPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SVIPCFG
{
	/**
	等级
	**/
	UINT8	_Level;

	/**
	总充值金额
	**/
	UINT32	_Total;
}; // SVIPCFG define end

//data loader for the excel table
class CVIPLoader
{
public:
	std::vector<SVIPCFG*> _vecData;

	~CVIPLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

