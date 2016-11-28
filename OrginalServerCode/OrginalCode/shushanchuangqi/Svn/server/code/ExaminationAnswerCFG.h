// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExaminationAnswerCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEXAMINATIONANSWERLOADER_H
#define _CEXAMINATIONANSWERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SExaminationAnswerCFG
{
	/**
	题目编号
	**/
	UINT32	_ID;

	/**
	正确答案位置
	**/
	string	_AnswerPosition;
}; // SExaminationAnswerCFG define end

//data loader for the excel table
class CExaminationAnswerLoader
{
public:
	std::vector<SExaminationAnswerCFG*> _vecData;

	~CExaminationAnswerLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

