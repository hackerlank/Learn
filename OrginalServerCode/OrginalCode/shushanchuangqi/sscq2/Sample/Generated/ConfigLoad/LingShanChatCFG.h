// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanChatCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLINGSHANCHATLOADER_H
#define _CLINGSHANCHATLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLingShanChatCFG
{
	/**
	表情id
	**/
	UINT16	_ID;
}; // SLingShanChatCFG define end

//data loader for the excel table
class CLingShanChatLoader
{
public:
	std::vector<SLingShanChatCFG*> _vecData;

	~CLingShanChatLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

