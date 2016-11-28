// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SResistCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ResistCFG.h"
#include "tinyxml.h"

CResistLoader::~CResistLoader()
{
	ClearData();
}

void CResistLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SResistCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CResistLoader::LoadData(const std::string& strPath)
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
		SResistCFG* pData = new SResistCFG;
		const char* pstr_wResistId = pDataElem->Attribute("wResistId");
		if(pstr_wResistId != NULL)
			pData->_wResistId = (UINT16)atoi(pstr_wResistId);
		else
			pData->_wResistId = 0;
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


