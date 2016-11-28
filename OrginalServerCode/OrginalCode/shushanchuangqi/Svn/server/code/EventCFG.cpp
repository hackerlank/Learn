// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEventCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "EventCFG.h"
#include "tinyxml.h"

CEventLoader::~CEventLoader()
{
	ClearData();
}

void CEventLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SEventCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CEventLoader::LoadData(const std::string& strPath)
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
		SEventCFG* pData = new SEventCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Total = pDataElem->Attribute("Total");
		if(pstr_Total != NULL)
			pData->_Total = (UINT8)atoi(pstr_Total);
		else
			pData->_Total = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_TypePara = pDataElem->Attribute("TypePara");
		if(pstr_TypePara != NULL)
			pData->_TypePara = pstr_TypePara;
		else
			pData->_TypePara = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


