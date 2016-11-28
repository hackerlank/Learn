// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdldanlulevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ComdldanlulevelCFG.h"
#include "tinyxml.h"

CComdldanlulevelLoader::~CComdldanlulevelLoader()
{
	ClearData();
}

void CComdldanlulevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SComdldanlulevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CComdldanlulevelLoader::LoadData(const std::string& strPath)
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
		SComdldanlulevelCFG* pData = new SComdldanlulevelCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Outputincrease = pDataElem->Attribute("Outputincrease");
		if(pstr_Outputincrease != NULL)
			pData->_Outputincrease = (UINT8)atoi(pstr_Outputincrease);
		else
			pData->_Outputincrease = 0;
		const char* pstr_Yuanqireduce = pDataElem->Attribute("Yuanqireduce");
		if(pstr_Yuanqireduce != NULL)
			pData->_Yuanqireduce = (UINT8)atoi(pstr_Yuanqireduce);
		else
			pData->_Yuanqireduce = 0;
		const char* pstr_Silvercost = pDataElem->Attribute("Silvercost");
		if(pstr_Silvercost != NULL)
			pData->_Silvercost = (UINT16)atoi(pstr_Silvercost);
		else
			pData->_Silvercost = 0;
		const char* pstr_Couponcost = pDataElem->Attribute("Couponcost");
		if(pstr_Couponcost != NULL)
			pData->_Couponcost = (UINT16)atoi(pstr_Couponcost);
		else
			pData->_Couponcost = 0;
		const char* pstr_Goldcost = pDataElem->Attribute("Goldcost");
		if(pstr_Goldcost != NULL)
			pData->_Goldcost = (UINT16)atoi(pstr_Goldcost);
		else
			pData->_Goldcost = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


