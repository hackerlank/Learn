// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEquipTrumpRecycleCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "EquipTrumpRecycleCFG.h"
#include "tinyxml.h"

CEquipTrumpRecycleLoader::~CEquipTrumpRecycleLoader()
{
	ClearData();
}

void CEquipTrumpRecycleLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SEquipTrumpRecycleCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CEquipTrumpRecycleLoader::LoadData(const std::string& strPath)
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
		SEquipTrumpRecycleCFG* pData = new SEquipTrumpRecycleCFG;
		const char* pstr_EquipTrumpId = pDataElem->Attribute("EquipTrumpId");
		if(pstr_EquipTrumpId != NULL)
			pData->_EquipTrumpId = (UINT16)atoi(pstr_EquipTrumpId);
		else
			pData->_EquipTrumpId = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_LootId = pDataElem->Attribute("LootId");
		if(pstr_LootId != NULL)
			pData->_LootId = (UINT32)atoi(pstr_LootId);
		else
			pData->_LootId = 0;
		const char* pstr_DropPreview = pDataElem->Attribute("DropPreview");
		if(pstr_DropPreview != NULL)
			pData->_DropPreview = pstr_DropPreview;
		else
			pData->_DropPreview = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


