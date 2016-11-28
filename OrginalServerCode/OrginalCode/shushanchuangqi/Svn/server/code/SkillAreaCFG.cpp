// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillAreaCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SkillAreaCFG.h"
#include "tinyxml.h"

CSkillAreaLoader::~CSkillAreaLoader()
{
	ClearData();
}

void CSkillAreaLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSkillAreaCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSkillAreaLoader::LoadData(const std::string& strPath)
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
		SSkillAreaCFG* pData = new SSkillAreaCFG;
		const char* pstr_wID = pDataElem->Attribute("wID");
		if(pstr_wID != NULL)
			pData->_wID = (UINT16)atoi(pstr_wID);
		else
			pData->_wID = 0;
		const char* pstr_strName = pDataElem->Attribute("strName");
		if(pstr_strName != NULL)
			pData->_strName = pstr_strName;
		else
			pData->_strName = "";
		const char* pstr_bySelectType = pDataElem->Attribute("bySelectType");
		if(pstr_bySelectType != NULL)
			pData->_bySelectType = (UINT8)atoi(pstr_bySelectType);
		else
			pData->_bySelectType = 0;
		const char* pstr_byRateType = pDataElem->Attribute("byRateType");
		if(pstr_byRateType != NULL)
			pData->_byRateType = (UINT8)atoi(pstr_byRateType);
		else
			pData->_byRateType = 0;
		const char* pstr_strFighterID = pDataElem->Attribute("strFighterID");
		if(pstr_strFighterID != NULL)
			pData->_strFighterID = pstr_strFighterID;
		else
			pData->_strFighterID = "";
		const char* pstr_byHasMainTarget = pDataElem->Attribute("byHasMainTarget");
		if(pstr_byHasMainTarget != NULL)
			pData->_byHasMainTarget = (UINT8)atoi(pstr_byHasMainTarget);
		else
			pData->_byHasMainTarget = 0;
		const char* pstr_bySide = pDataElem->Attribute("bySide");
		if(pstr_bySide != NULL)
			pData->_bySide = (UINT8)atoi(pstr_bySide);
		else
			pData->_bySide = 0;
		const char* pstr_strArea = pDataElem->Attribute("strArea");
		if(pstr_strArea != NULL)
			pData->_strArea = pstr_strArea;
		else
			pData->_strArea = "";
		const char* pstr_strFactor = pDataElem->Attribute("strFactor");
		if(pstr_strFactor != NULL)
			pData->_strFactor = pstr_strFactor;
		else
			pData->_strFactor = "";
		const char* pstr_strRepeatFactor = pDataElem->Attribute("strRepeatFactor");
		if(pstr_strRepeatFactor != NULL)
			pData->_strRepeatFactor = pstr_strRepeatFactor;
		else
			pData->_strRepeatFactor = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


