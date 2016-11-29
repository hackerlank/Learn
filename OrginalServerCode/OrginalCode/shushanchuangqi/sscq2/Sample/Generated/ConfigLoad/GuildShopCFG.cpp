// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildShopCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildShopCFG.h"
#include "tinyxml.h"

CGuildShopLoader::~CGuildShopLoader()
{
	ClearData();
}

void CGuildShopLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildShopCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildShopLoader::LoadData(const std::string& strPath)
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
		SGuildShopCFG* pData = new SGuildShopCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Item = pDataElem->Attribute("Item");
		if(pstr_Item != NULL)
			pData->_Item = pstr_Item;
		else
			pData->_Item = "";
		const char* pstr_Price = pDataElem->Attribute("Price");
		if(pstr_Price != NULL)
			pData->_Price = (UINT32)atoi(pstr_Price);
		else
			pData->_Price = 0;
		const char* pstr_GuildLevel = pDataElem->Attribute("GuildLevel");
		if(pstr_GuildLevel != NULL)
			pData->_GuildLevel = (UINT8)atoi(pstr_GuildLevel);
		else
			pData->_GuildLevel = 0;
		const char* pstr_DayCntLimit = pDataElem->Attribute("DayCntLimit");
		if(pstr_DayCntLimit != NULL)
			pData->_DayCntLimit = (UINT16)atoi(pstr_DayCntLimit);
		else
			pData->_DayCntLimit = 0;
		const char* pstr_AvailableCon = pDataElem->Attribute("AvailableCon");
		if(pstr_AvailableCon != NULL)
			pData->_AvailableCon = (UINT16)atoi(pstr_AvailableCon);
		else
			pData->_AvailableCon = 0;
		const char* pstr_StoreNum = pDataElem->Attribute("StoreNum");
		if(pstr_StoreNum != NULL)
			pData->_StoreNum = (UINT16)atoi(pstr_StoreNum);
		else
			pData->_StoreNum = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


