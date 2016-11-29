// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterRecruitCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FighterRecruitCFG.h"
#include "tinyxml.h"

CFighterRecruitLoader::~CFighterRecruitLoader()
{
	ClearData();
}

void CFighterRecruitLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFighterRecruitCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFighterRecruitLoader::LoadData(const std::string& strPath)
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
		SFighterRecruitCFG* pData = new SFighterRecruitCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_CondID = pDataElem->Attribute("CondID");
		if(pstr_CondID != NULL)
			pData->_CondID = (UINT16)atoi(pstr_CondID);
		else
			pData->_CondID = 0;
		const char* pstr_Combination = pDataElem->Attribute("Combination");
		if(pstr_Combination != NULL)
			pData->_Combination = pstr_Combination;
		else
			pData->_Combination = "";
		const char* pstr_NeedPoint = pDataElem->Attribute("NeedPoint");
		if(pstr_NeedPoint != NULL)
			pData->_NeedPoint = (UINT8)atoi(pstr_NeedPoint);
		else
			pData->_NeedPoint = 0;
		const char* pstr_Exchange = pDataElem->Attribute("Exchange");
		if(pstr_Exchange != NULL)
			pData->_Exchange = (UINT32)atoi(pstr_Exchange);
		else
			pData->_Exchange = 0;
		const char* pstr_ChanceTask = pDataElem->Attribute("ChanceTask");
		if(pstr_ChanceTask != NULL)
			pData->_ChanceTask = (UINT16)atoi(pstr_ChanceTask);
		else
			pData->_ChanceTask = 0;
		const char* pstr_AppearLevel = pDataElem->Attribute("AppearLevel");
		if(pstr_AppearLevel != NULL)
			pData->_AppearLevel = (UINT8)atoi(pstr_AppearLevel);
		else
			pData->_AppearLevel = 0;
		const char* pstr_Introduce = pDataElem->Attribute("Introduce");
		if(pstr_Introduce != NULL)
			pData->_Introduce = pstr_Introduce;
		else
			pData->_Introduce = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


