// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShareCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSHARELOADER_H
#define _CSHARELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SShareCFG
{
	/**
	ID
	**/
	UINT16	_ID;

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
}; // SShareCFG define end

//data loader for the excel table
class CShareLoader
{
public:
	std::vector<SShareCFG*> _vecData;

	~CShareLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

