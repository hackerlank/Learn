// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStoveFireLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StoveFireLevelCFG.h"
#include "tinyxml.h"

CStoveFireLevelLoader::~CStoveFireLevelLoader()
{
	ClearData();
}

void CStoveFireLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStoveFireLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStoveFireLevelLoader::LoadData(const std::string& strPath)
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
		SStoveFireLevelCFG* pData = new SStoveFireLevelCFG;
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
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Appear = pDataElem->Attribute("Appear");
		if(pstr_Appear != NULL)
			pData->_Appear = (UINT16)atoi(pstr_Appear);
		else
			pData->_Appear = 0;
		const char* pstr_LowLine = pDataElem->Attribute("LowLine");
		if(pstr_LowLine != NULL)
			pData->_LowLine = (UINT8)atoi(pstr_LowLine);
		else
			pData->_LowLine = 0;
		const char* pstr_MaxLine = pDataElem->Attribute("MaxLine");
		if(pstr_MaxLine != NULL)
			pData->_MaxLine = (UINT32)atoi(pstr_MaxLine);
		else
			pData->_MaxLine = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


