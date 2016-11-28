// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExchangeMallCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ExchangeMallCFG.h"
#include "tinyxml.h"

CExchangeMallLoader::~CExchangeMallLoader()
{
	ClearData();
}

void CExchangeMallLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SExchangeMallCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CExchangeMallLoader::LoadData(const std::string& strPath)
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
		SExchangeMallCFG* pData = new SExchangeMallCFG;
		const char* pstr_Id = pDataElem->Attribute("Id");
		if(pstr_Id != NULL)
			pData->_Id = (UINT32)atoi(pstr_Id);
		else
			pData->_Id = 0;
		const char* pstr_ItemId = pDataElem->Attribute("ItemId");
		if(pstr_ItemId != NULL)
			pData->_ItemId = (UINT16)atoi(pstr_ItemId);
		else
			pData->_ItemId = 0;
		const char* pstr_ItemCount = pDataElem->Attribute("ItemCount");
		if(pstr_ItemCount != NULL)
			pData->_ItemCount = (UINT16)atoi(pstr_ItemCount);
		else
			pData->_ItemCount = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_MoneyType = pDataElem->Attribute("MoneyType");
		if(pstr_MoneyType != NULL)
			pData->_MoneyType = (UINT8)atoi(pstr_MoneyType);
		else
			pData->_MoneyType = 0;
		const char* pstr_Price = pDataElem->Attribute("Price");
		if(pstr_Price != NULL)
			pData->_Price = (UINT32)atoi(pstr_Price);
		else
			pData->_Price = 0;
		const char* pstr_AppearCon = pDataElem->Attribute("AppearCon");
		if(pstr_AppearCon != NULL)
			pData->_AppearCon = (UINT16)atoi(pstr_AppearCon);
		else
			pData->_AppearCon = 0;
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


