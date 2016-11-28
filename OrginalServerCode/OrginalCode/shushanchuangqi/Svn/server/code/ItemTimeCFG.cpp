// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemTimeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ItemTimeCFG.h"
#include "tinyxml.h"

CItemTimeLoader::~CItemTimeLoader()
{
	ClearData();
}

void CItemTimeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SItemTimeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CItemTimeLoader::LoadData(const std::string& strPath)
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
		SItemTimeCFG* pData = new SItemTimeCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_StartType = pDataElem->Attribute("StartType");
		if(pstr_StartType != NULL)
			pData->_StartType = (UINT8)atoi(pstr_StartType);
		else
			pData->_StartType = 0;
		const char* pstr_TipType = pDataElem->Attribute("TipType");
		if(pstr_TipType != NULL)
			pData->_TipType = (UINT8)atoi(pstr_TipType);
		else
			pData->_TipType = 0;
		const char* pstr_Disposal = pDataElem->Attribute("Disposal");
		if(pstr_Disposal != NULL)
			pData->_Disposal = (UINT8)atoi(pstr_Disposal);
		else
			pData->_Disposal = 0;
		const char* pstr_DueType = pDataElem->Attribute("DueType");
		if(pstr_DueType != NULL)
			pData->_DueType = (UINT8)atoi(pstr_DueType);
		else
			pData->_DueType = 0;
		const char* pstr_RemTime = pDataElem->Attribute("RemTime");
		if(pstr_RemTime != NULL)
			pData->_RemTime = (UINT32)atoi(pstr_RemTime);
		else
			pData->_RemTime = 0;
		const char* pstr_ExpireTime = pDataElem->Attribute("ExpireTime");
		if(pstr_ExpireTime != NULL)
			pData->_ExpireTime = pstr_ExpireTime;
		else
			pData->_ExpireTime = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


