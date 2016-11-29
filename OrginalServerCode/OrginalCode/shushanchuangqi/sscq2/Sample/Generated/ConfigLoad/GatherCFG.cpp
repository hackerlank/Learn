// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGatherCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GatherCFG.h"
#include "tinyxml.h"

CGatherLoader::~CGatherLoader()
{
	ClearData();
}

void CGatherLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGatherCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGatherLoader::LoadData(const std::string& strPath)
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
		SGatherCFG* pData = new SGatherCFG;
		const char* pstr_wGatherId = pDataElem->Attribute("wGatherId");
		if(pstr_wGatherId != NULL)
			pData->_wGatherId = (UINT16)atoi(pstr_wGatherId);
		else
			pData->_wGatherId = 0;
		const char* pstr_strName = pDataElem->Attribute("strName");
		if(pstr_strName != NULL)
			pData->_strName = pstr_strName;
		else
			pData->_strName = "";
		const char* pstr_AssetType = pDataElem->Attribute("AssetType");
		if(pstr_AssetType != NULL)
			pData->_AssetType = (UINT8)atoi(pstr_AssetType);
		else
			pData->_AssetType = 0;
		const char* pstr_AssetParam1 = pDataElem->Attribute("AssetParam1");
		if(pstr_AssetParam1 != NULL)
			pData->_AssetParam1 = (UINT16)atoi(pstr_AssetParam1);
		else
			pData->_AssetParam1 = 0;
		const char* pstr_AssetParam3 = pDataElem->Attribute("AssetParam3");
		if(pstr_AssetParam3 != NULL)
			pData->_AssetParam3 = pstr_AssetParam3;
		else
			pData->_AssetParam3 = "";
		const char* pstr_AssetAdjust = pDataElem->Attribute("AssetAdjust");
		if(pstr_AssetAdjust != NULL)
			pData->_AssetAdjust = (FLOAT)atof(pstr_AssetAdjust);
		else
			pData->_AssetAdjust = 0.0f;
		const char* pstr_AssetShadow = pDataElem->Attribute("AssetShadow");
		if(pstr_AssetShadow != NULL)
			pData->_AssetShadow = (FLOAT)atof(pstr_AssetShadow);
		else
			pData->_AssetShadow = 0.0f;
		const char* pstr_ApearEffect = pDataElem->Attribute("ApearEffect");
		if(pstr_ApearEffect != NULL)
			pData->_ApearEffect = (UINT16)atoi(pstr_ApearEffect);
		else
			pData->_ApearEffect = 0;
		const char* pstr_strCost = pDataElem->Attribute("strCost");
		if(pstr_strCost != NULL)
			pData->_strCost = pstr_strCost;
		else
			pData->_strCost = "";
		const char* pstr_wGatherTimer = pDataElem->Attribute("wGatherTimer");
		if(pstr_wGatherTimer != NULL)
			pData->_wGatherTimer = (UINT16)atoi(pstr_wGatherTimer);
		else
			pData->_wGatherTimer = 0;
		const char* pstr_wGatherNum = pDataElem->Attribute("wGatherNum");
		if(pstr_wGatherNum != NULL)
			pData->_wGatherNum = (UINT16)atoi(pstr_wGatherNum);
		else
			pData->_wGatherNum = 0;
		const char* pstr_byEmptyPack = pDataElem->Attribute("byEmptyPack");
		if(pstr_byEmptyPack != NULL)
			pData->_byEmptyPack = (UINT8)atoi(pstr_byEmptyPack);
		else
			pData->_byEmptyPack = 0;
		const char* pstr_dwDropId = pDataElem->Attribute("dwDropId");
		if(pstr_dwDropId != NULL)
			pData->_dwDropId = (UINT32)atoi(pstr_dwDropId);
		else
			pData->_dwDropId = 0;
		const char* pstr_byIsTask = pDataElem->Attribute("byIsTask");
		if(pstr_byIsTask != NULL)
			pData->_byIsTask = (UINT8)atoi(pstr_byIsTask);
		else
			pData->_byIsTask = 0;
		const char* pstr_Asset = pDataElem->Attribute("Asset");
		if(pstr_Asset != NULL)
			pData->_Asset = pstr_Asset;
		else
			pData->_Asset = "";
		const char* pstr_Disappear = pDataElem->Attribute("Disappear");
		if(pstr_Disappear != NULL)
			pData->_Disappear = pstr_Disappear;
		else
			pData->_Disappear = "";
		const char* pstr_IsPublic = pDataElem->Attribute("IsPublic");
		if(pstr_IsPublic != NULL)
			pData->_IsPublic = (UINT8)atoi(pstr_IsPublic);
		else
			pData->_IsPublic = 0;
		const char* pstr_IsShowName = pDataElem->Attribute("IsShowName");
		if(pstr_IsShowName != NULL)
			pData->_IsShowName = (UINT8)atoi(pstr_IsShowName);
		else
			pData->_IsShowName = 0;
		const char* pstr_IsMotion = pDataElem->Attribute("IsMotion");
		if(pstr_IsMotion != NULL)
			pData->_IsMotion = (UINT8)atoi(pstr_IsMotion);
		else
			pData->_IsMotion = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


