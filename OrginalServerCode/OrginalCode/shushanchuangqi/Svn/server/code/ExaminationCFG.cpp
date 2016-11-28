// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExaminationCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ExaminationCFG.h"
#include "tinyxml.h"

CExaminationLoader::~CExaminationLoader()
{
	ClearData();
}

void CExaminationLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SExaminationCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CExaminationLoader::LoadData(const std::string& strPath)
{
	ClearData();
	TiXmlDocument doc;
	if(!doc.LoadFile(strPath.c_str(), TIXML_ENCODING_UTF8))
	{
		doc.Clear();
		return false;
	}
	TiXmlElement* pElemRoot = doc.RootElement();
	if(pElemRoot == NULL)
	{
		doc.Clear();
		return false;
	}
	TiXmlElement* pDataElem = pElemRoot->FirstChildElement("Row");
	while(pDataElem != NULL)
	{
		SExaminationCFG* pData = new SExaminationCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Question = pDataElem->Attribute("Question");
		if(pstr_Question != NULL)
			pData->_Question = pstr_Question;
		else
			pData->_Question = "";
		const char* pstr_AnswerR = pDataElem->Attribute("AnswerR");
		if(pstr_AnswerR != NULL)
			pData->_AnswerR = pstr_AnswerR;
		else
			pData->_AnswerR = "";
		const char* pstr_AnswerW1 = pDataElem->Attribute("AnswerW1");
		if(pstr_AnswerW1 != NULL)
			pData->_AnswerW1 = pstr_AnswerW1;
		else
			pData->_AnswerW1 = "";
		const char* pstr_AnswerW2 = pDataElem->Attribute("AnswerW2");
		if(pstr_AnswerW2 != NULL)
			pData->_AnswerW2 = pstr_AnswerW2;
		else
			pData->_AnswerW2 = "";
		const char* pstr_AnswerW3 = pDataElem->Attribute("AnswerW3");
		if(pstr_AnswerW3 != NULL)
			pData->_AnswerW3 = pstr_AnswerW3;
		else
			pData->_AnswerW3 = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


