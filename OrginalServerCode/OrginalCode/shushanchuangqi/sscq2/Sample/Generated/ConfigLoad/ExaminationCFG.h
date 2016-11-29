// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExaminationCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEXAMINATIONLOADER_H
#define _CEXAMINATIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SExaminationCFG
{
	/**
	题目编号
	**/
	UINT32	_ID;

	/**
	题目
	**/
	string	_Question;

	/**
	正确答案
	**/
	string	_AnswerR;

	/**
	错误答案1
	**/
	string	_AnswerW1;

	/**
	错误答案2
	**/
	string	_AnswerW2;

	/**
	错误答案3
	**/
	string	_AnswerW3;
}; // SExaminationCFG define end

//data loader for the excel table
class CExaminationLoader
{
public:
	std::vector<SExaminationCFG*> _vecData;

	~CExaminationLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

