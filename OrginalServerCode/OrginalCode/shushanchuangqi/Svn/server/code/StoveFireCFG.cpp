// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStoveFireCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StoveFireCFG.h"
#include "tinyxml.h"

CStoveFireLoader::~CStoveFireLoader()
{
	ClearData();
}

void CStoveFireLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStoveFireCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStoveFireLoader::LoadData(const std::string& strPath)
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
		SStoveFireCFG* pData = new SStoveFireCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Position = pDataElem->Attribute("Position");
		if(pstr_Position != NULL)
			pData->_Position = (UINT16)atoi(pstr_Position);
		else
			pData->_Position = 0;
		const char* pstr_LimitTimes = pDataElem->Attribute("LimitTimes");
		if(pstr_LimitTimes != NULL)
			pData->_LimitTimes = (UINT8)atoi(pstr_LimitTimes);
		else
			pData->_LimitTimes = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_VigorMax = pDataElem->Attribute("VigorMax");
		if(pstr_VigorMax != NULL)
			pData->_VigorMax = (UINT32)atoi(pstr_VigorMax);
		else
			pData->_VigorMax = 0;
		const char* pstr_StoveExp = pDataElem->Attribute("StoveExp");
		if(pstr_StoveExp != NULL)
			pData->_StoveExp = (UINT32)atoi(pstr_StoveExp);
		else
			pData->_StoveExp = 0;
		const char* pstr_LevelC = pDataElem->Attribute("LevelC");
		if(pstr_LevelC != NULL)
			pData->_LevelC = (UINT8)atoi(pstr_LevelC);
		else
			pData->_LevelC = 0;
		const char* pstr_RequiredItem = pDataElem->Attribute("RequiredItem");
		if(pstr_RequiredItem != NULL)
			pData->_RequiredItem = pstr_RequiredItem;
		else
			pData->_RequiredItem = "";
		const char* pstr_RewardItem = pDataElem->Attribute("RewardItem");
		if(pstr_RewardItem != NULL)
			pData->_RewardItem = pstr_RewardItem;
		else
			pData->_RewardItem = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


