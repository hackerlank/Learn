// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEventCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEVENTLOADER_H
#define _CEVENTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEventCFG
{
	/**
	事件id
	**/
	UINT16	_ID;

	/**
	是否累计
	**/
	UINT8	_Total;

	/**
	事件类型
	**/
	UINT8	_Type;

	/**
	事件参数
	**/
	string	_TypePara;
}; // SEventCFG define end

//data loader for the excel table
class CEventLoader
{
public:
	std::vector<SEventCFG*> _vecData;

	~CEventLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

