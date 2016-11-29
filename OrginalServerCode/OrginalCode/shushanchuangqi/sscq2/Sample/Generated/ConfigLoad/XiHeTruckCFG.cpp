// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SXiHeTruckCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "XiHeTruckCFG.h"
#include "tinyxml.h"

CXiHeTruckLoader::~CXiHeTruckLoader()
{
	ClearData();
}

void CXiHeTruckLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SXiHeTruckCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CXiHeTruckLoader::LoadData(const std::string& strPath)
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
		SXiHeTruckCFG* pData = new SXiHeTruckCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Goods = pDataElem->Attribute("Goods");
		if(pstr_Goods != NULL)
			pData->_Goods = pstr_Goods;
		else
			pData->_Goods = "";
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		const char* pstr_GuildMoney = pDataElem->Attribute("GuildMoney");
		if(pstr_GuildMoney != NULL)
			pData->_GuildMoney = (UINT32)atoi(pstr_GuildMoney);
		else
			pData->_GuildMoney = 0;
		const char* pstr_Value = pDataElem->Attribute("Value");
		if(pstr_Value != NULL)
			pData->_Value = (UINT16)atoi(pstr_Value);
		else
			pData->_Value = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = pstr_Level;
		else
			pData->_Level = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


