// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAreaCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AreaCFG.h"
#include "tinyxml.h"

CAreaLoader::~CAreaLoader()
{
	ClearData();
}

void CAreaLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAreaCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAreaLoader::LoadData(const std::string& strPath)
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
		SAreaCFG* pData = new SAreaCFG;
		const char* pstr_areaId = pDataElem->Attribute("areaId");
		if(pstr_areaId != NULL)
			pData->_areaId = (UINT16)atoi(pstr_areaId);
		else
			pData->_areaId = 0;
		const char* pstr_areaName = pDataElem->Attribute("areaName");
		if(pstr_areaName != NULL)
			pData->_areaName = pstr_areaName;
		else
			pData->_areaName = "";
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
		const char* pstr_IsSafe = pDataElem->Attribute("IsSafe");
		if(pstr_IsSafe != NULL)
			pData->_IsSafe = (UINT8)atoi(pstr_IsSafe);
		else
			pData->_IsSafe = 0;
		const char* pstr_IsDel = pDataElem->Attribute("IsDel");
		if(pstr_IsDel != NULL)
			pData->_IsDel = (UINT8)atoi(pstr_IsDel);
		else
			pData->_IsDel = 0;
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
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


