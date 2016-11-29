// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemUpgradeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ItemUpgradeCFG.h"
#include "tinyxml.h"

CItemUpgradeLoader::~CItemUpgradeLoader()
{
	ClearData();
}

void CItemUpgradeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SItemUpgradeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CItemUpgradeLoader::LoadData(const std::string& strPath)
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
		SItemUpgradeCFG* pData = new SItemUpgradeCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_ItemID = pDataElem->Attribute("ItemID");
		if(pstr_ItemID != NULL)
			pData->_ItemID = (UINT16)atoi(pstr_ItemID);
		else
			pData->_ItemID = 0;
		const char* pstr_RequiredItem = pDataElem->Attribute("RequiredItem");
		if(pstr_RequiredItem != NULL)
			pData->_RequiredItem = pstr_RequiredItem;
		else
			pData->_RequiredItem = "";
		const char* pstr_RequiredSilver = pDataElem->Attribute("RequiredSilver");
		if(pstr_RequiredSilver != NULL)
			pData->_RequiredSilver = (UINT32)atoi(pstr_RequiredSilver);
		else
			pData->_RequiredSilver = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


