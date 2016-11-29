// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeastCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BeastCFG.h"
#include "tinyxml.h"

CBeastLoader::~CBeastLoader()
{
	ClearData();
}

void CBeastLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBeastCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBeastLoader::LoadData(const std::string& strPath)
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
		SBeastCFG* pData = new SBeastCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Page = pDataElem->Attribute("Page");
		if(pstr_Page != NULL)
			pData->_Page = (UINT8)atoi(pstr_Page);
		else
			pData->_Page = 0;
		const char* pstr_UnlockItem = pDataElem->Attribute("UnlockItem");
		if(pstr_UnlockItem != NULL)
			pData->_UnlockItem = (UINT32)atoi(pstr_UnlockItem);
		else
			pData->_UnlockItem = 0;
		const char* pstr_ItemNum = pDataElem->Attribute("ItemNum");
		if(pstr_ItemNum != NULL)
			pData->_ItemNum = (UINT16)atoi(pstr_ItemNum);
		else
			pData->_ItemNum = 0;
		const char* pstr_AttrIdx_1 = pDataElem->Attribute("AttrIdx_1");
		if(pstr_AttrIdx_1 != NULL)
			pData->_AttrIdx_1 = (UINT16)atoi(pstr_AttrIdx_1);
		else
			pData->_AttrIdx_1 = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


