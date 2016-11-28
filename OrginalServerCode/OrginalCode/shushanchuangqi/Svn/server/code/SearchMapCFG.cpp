// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSearchMapCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SearchMapCFG.h"
#include "tinyxml.h"

CSearchMapLoader::~CSearchMapLoader()
{
	ClearData();
}

void CSearchMapLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSearchMapCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSearchMapLoader::LoadData(const std::string& strPath)
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
		SSearchMapCFG* pData = new SSearchMapCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Map = pDataElem->Attribute("Map");
		if(pstr_Map != NULL)
			pData->_Map = pstr_Map;
		else
			pData->_Map = "";
		const char* pstr_Boss = pDataElem->Attribute("Boss");
		if(pstr_Boss != NULL)
			pData->_Boss = (UINT32)atoi(pstr_Boss);
		else
			pData->_Boss = 0;
		const char* pstr_MonsterGroup = pDataElem->Attribute("MonsterGroup");
		if(pstr_MonsterGroup != NULL)
			pData->_MonsterGroup = pstr_MonsterGroup;
		else
			pData->_MonsterGroup = "";
		const char* pstr_Money = pDataElem->Attribute("Money");
		if(pstr_Money != NULL)
			pData->_Money = (UINT32)atoi(pstr_Money);
		else
			pData->_Money = 0;
		const char* pstr_Pexp = pDataElem->Attribute("Pexp");
		if(pstr_Pexp != NULL)
			pData->_Pexp = (UINT32)atoi(pstr_Pexp);
		else
			pData->_Pexp = 0;
		const char* pstr_ClearTime = pDataElem->Attribute("ClearTime");
		if(pstr_ClearTime != NULL)
			pData->_ClearTime = (UINT16)atoi(pstr_ClearTime);
		else
			pData->_ClearTime = 0;
		const char* pstr_TimeAward = pDataElem->Attribute("TimeAward");
		if(pstr_TimeAward != NULL)
			pData->_TimeAward = (UINT16)atoi(pstr_TimeAward);
		else
			pData->_TimeAward = 0;
		const char* pstr_FinishCost = pDataElem->Attribute("FinishCost");
		if(pstr_FinishCost != NULL)
			pData->_FinishCost = (UINT16)atoi(pstr_FinishCost);
		else
			pData->_FinishCost = 0;
		const char* pstr_FinishAward = pDataElem->Attribute("FinishAward");
		if(pstr_FinishAward != NULL)
			pData->_FinishAward = (UINT16)atoi(pstr_FinishAward);
		else
			pData->_FinishAward = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


