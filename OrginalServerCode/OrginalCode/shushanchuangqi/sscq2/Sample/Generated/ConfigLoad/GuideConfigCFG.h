// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuideConfigCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUIDECONFIGLOADER_H
#define _CGUIDECONFIGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuideConfigCFG
{
	/**
	类型ID
	**/
	UINT16	_id;

	/**
	类型内容
	**/
	string	_content;
}; // SGuideConfigCFG define end

//data loader for the excel table
class CGuideConfigLoader
{
public:
	std::vector<SGuideConfigCFG*> _vecData;

	~CGuideConfigLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

