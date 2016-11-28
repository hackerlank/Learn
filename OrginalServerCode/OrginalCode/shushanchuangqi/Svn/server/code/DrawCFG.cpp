// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDrawCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DrawCFG.h"
#include "tinyxml.h"

CDrawLoader::~CDrawLoader()
{
	ClearData();
}

void CDrawLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDrawCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDrawLoader::LoadData(const std::string& strPath)
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
		SDrawCFG* pData = new SDrawCFG;
		const char* pstr_PlayerLevel = pDataElem->Attribute("PlayerLevel");
		if(pstr_PlayerLevel != NULL)
			pData->_PlayerLevel = (UINT16)atoi(pstr_PlayerLevel);
		else
			pData->_PlayerLevel = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_BasicType = pDataElem->Attribute("BasicType");
		if(pstr_BasicType != NULL)
			pData->_BasicType = (UINT16)atoi(pstr_BasicType);
		else
			pData->_BasicType = 0;
		const char* pstr_BasicPercent = pDataElem->Attribute("BasicPercent");
		if(pstr_BasicPercent != NULL)
			pData->_BasicPercent = (UINT16)atoi(pstr_BasicPercent);
		else
			pData->_BasicPercent = 0;
		const char* pstr_BasicValue1 = pDataElem->Attribute("BasicValue1");
		if(pstr_BasicValue1 != NULL)
			pData->_BasicValue1 = (UINT16)atoi(pstr_BasicValue1);
		else
			pData->_BasicValue1 = 0;
		const char* pstr_BasicValue2 = pDataElem->Attribute("BasicValue2");
		if(pstr_BasicValue2 != NULL)
			pData->_BasicValue2 = (UINT16)atoi(pstr_BasicValue2);
		else
			pData->_BasicValue2 = 0;
		const char* pstr_UnexpectedType = pDataElem->Attribute("UnexpectedType");
		if(pstr_UnexpectedType != NULL)
			pData->_UnexpectedType = (UINT16)atoi(pstr_UnexpectedType);
		else
			pData->_UnexpectedType = 0;
		const char* pstr_UnexpectedValue1 = pDataElem->Attribute("UnexpectedValue1");
		if(pstr_UnexpectedValue1 != NULL)
			pData->_UnexpectedValue1 = (UINT16)atoi(pstr_UnexpectedValue1);
		else
			pData->_UnexpectedValue1 = 0;
		const char* pstr_UnexpectedValue2 = pDataElem->Attribute("UnexpectedValue2");
		if(pstr_UnexpectedValue2 != NULL)
			pData->_UnexpectedValue2 = (UINT16)atoi(pstr_UnexpectedValue2);
		else
			pData->_UnexpectedValue2 = 0;
		const char* pstr_DrawSilverPrice = pDataElem->Attribute("DrawSilverPrice");
		if(pstr_DrawSilverPrice != NULL)
			pData->_DrawSilverPrice = (UINT32)atoi(pstr_DrawSilverPrice);
		else
			pData->_DrawSilverPrice = 0;
		const char* pstr_DrawGoldPrice = pDataElem->Attribute("DrawGoldPrice");
		if(pstr_DrawGoldPrice != NULL)
			pData->_DrawGoldPrice = (UINT16)atoi(pstr_DrawGoldPrice);
		else
			pData->_DrawGoldPrice = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


