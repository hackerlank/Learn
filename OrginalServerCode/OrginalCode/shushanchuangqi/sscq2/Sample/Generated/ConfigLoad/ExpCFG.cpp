// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExpCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ExpCFG.h"
#include "tinyxml.h"

CExpLoader::~CExpLoader()
{
	ClearData();
}

void CExpLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SExpCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CExpLoader::LoadData(const std::string& strPath)
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
		SExpCFG* pData = new SExpCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT64)atoll(pstr_Exp);
		else
			pData->_Exp = 0;
		const char* pstr_WC1 = pDataElem->Attribute("WC1");
		if(pstr_WC1 != NULL)
			pData->_WC1 = (UINT16)atoi(pstr_WC1);
		else
			pData->_WC1 = 0;
		const char* pstr_WC2 = pDataElem->Attribute("WC2");
		if(pstr_WC2 != NULL)
			pData->_WC2 = (UINT16)atoi(pstr_WC2);
		else
			pData->_WC2 = 0;
		const char* pstr_SitBasicExp = pDataElem->Attribute("SitBasicExp");
		if(pstr_SitBasicExp != NULL)
			pData->_SitBasicExp = (UINT16)atoi(pstr_SitBasicExp);
		else
			pData->_SitBasicExp = 0;
		const char* pstr_SitBasicResourceType = pDataElem->Attribute("SitBasicResourceType");
		if(pstr_SitBasicResourceType != NULL)
			pData->_SitBasicResourceType = (UINT8)atoi(pstr_SitBasicResourceType);
		else
			pData->_SitBasicResourceType = 0;
		const char* pstr_SitBasicResourceValue = pDataElem->Attribute("SitBasicResourceValue");
		if(pstr_SitBasicResourceValue != NULL)
			pData->_SitBasicResourceValue = (UINT16)atoi(pstr_SitBasicResourceValue);
		else
			pData->_SitBasicResourceValue = 0;
		const char* pstr_StoveC = pDataElem->Attribute("StoveC");
		if(pstr_StoveC != NULL)
			pData->_StoveC = (UINT16)atoi(pstr_StoveC);
		else
			pData->_StoveC = 0;
		const char* pstr_StoveHelperAddition = pDataElem->Attribute("StoveHelperAddition");
		if(pstr_StoveHelperAddition != NULL)
			pData->_StoveHelperAddition = (UINT16)atoi(pstr_StoveHelperAddition);
		else
			pData->_StoveHelperAddition = 0;
		const char* pstr_LevelUpInfo = pDataElem->Attribute("LevelUpInfo");
		if(pstr_LevelUpInfo != NULL)
			pData->_LevelUpInfo = pstr_LevelUpInfo;
		else
			pData->_LevelUpInfo = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


