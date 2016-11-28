// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMallCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "MallCFG.h"
#include "tinyxml.h"

CMallLoader::~CMallLoader()
{
	ClearData();
}

void CMallLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SMallCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CMallLoader::LoadData(const std::string& strPath)
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
		SMallCFG* pData = new SMallCFG;
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
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_ItemNum = pDataElem->Attribute("ItemNum");
		if(pstr_ItemNum != NULL)
			pData->_ItemNum = (UINT16)atoi(pstr_ItemNum);
		else
			pData->_ItemNum = 0;
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
		const char* pstr_VIP = pDataElem->Attribute("VIP");
		if(pstr_VIP != NULL)
			pData->_VIP = (UINT8)atoi(pstr_VIP);
		else
			pData->_VIP = 0;
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT16)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		const char* pstr_DayCntLimit = pDataElem->Attribute("DayCntLimit");
		if(pstr_DayCntLimit != NULL)
			pData->_DayCntLimit = pstr_DayCntLimit;
		else
			pData->_DayCntLimit = "";
		const char* pstr_AvailableCon = pDataElem->Attribute("AvailableCon");
		if(pstr_AvailableCon != NULL)
			pData->_AvailableCon = (UINT16)atoi(pstr_AvailableCon);
		else
			pData->_AvailableCon = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


