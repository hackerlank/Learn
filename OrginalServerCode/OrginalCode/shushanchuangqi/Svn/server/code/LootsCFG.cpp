// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLootsCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LootsCFG.h"
#include "tinyxml.h"

CLootsLoader::~CLootsLoader()
{
	ClearData();
}

void CLootsLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLootsCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLootsLoader::LoadData(const std::string& strPath)
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
		SLootsCFG* pData = new SLootsCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_LootType = pDataElem->Attribute("LootType");
		if(pstr_LootType != NULL)
			pData->_LootType = (UINT8)atoi(pstr_LootType);
		else
			pData->_LootType = 0;
		const char* pstr_products = pDataElem->Attribute("products");
		if(pstr_products != NULL)
			pData->_products = pstr_products;
		else
			pData->_products = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


