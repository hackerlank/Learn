// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDujiePeriodCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DujiePeriodCFG.h"
#include "tinyxml.h"

CDujiePeriodLoader::~CDujiePeriodLoader()
{
	ClearData();
}

void CDujiePeriodLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDujiePeriodCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDujiePeriodLoader::LoadData(const std::string& strPath)
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
		SDujiePeriodCFG* pData = new SDujiePeriodCFG;
		const char* pstr_PeriodId = pDataElem->Attribute("PeriodId");
		if(pstr_PeriodId != NULL)
			pData->_PeriodId = (UINT8)atoi(pstr_PeriodId);
		else
			pData->_PeriodId = 0;
		const char* pstr_DujieLevel = pDataElem->Attribute("DujieLevel");
		if(pstr_DujieLevel != NULL)
			pData->_DujieLevel = (UINT16)atoi(pstr_DujieLevel);
		else
			pData->_DujieLevel = 0;
		const char* pstr_PeriodName = pDataElem->Attribute("PeriodName");
		if(pstr_PeriodName != NULL)
			pData->_PeriodName = pstr_PeriodName;
		else
			pData->_PeriodName = "";
		const char* pstr_NameColor = pDataElem->Attribute("NameColor");
		if(pstr_NameColor != NULL)
			pData->_NameColor = (UINT8)atoi(pstr_NameColor);
		else
			pData->_NameColor = 0;
		const char* pstr_Info = pDataElem->Attribute("Info");
		if(pstr_Info != NULL)
			pData->_Info = pstr_Info;
		else
			pData->_Info = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


