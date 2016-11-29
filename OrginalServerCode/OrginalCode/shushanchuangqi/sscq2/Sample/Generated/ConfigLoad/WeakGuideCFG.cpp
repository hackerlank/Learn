// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SWeakGuideCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "WeakGuideCFG.h"
#include "tinyxml.h"

CWeakGuideLoader::~CWeakGuideLoader()
{
	ClearData();
}

void CWeakGuideLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SWeakGuideCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CWeakGuideLoader::LoadData(const std::string& strPath)
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
		SWeakGuideCFG* pData = new SWeakGuideCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Parameter = pDataElem->Attribute("Parameter");
		if(pstr_Parameter != NULL)
			pData->_Parameter = (UINT32)atoi(pstr_Parameter);
		else
			pData->_Parameter = 0;
		const char* pstr_value = pDataElem->Attribute("value");
		if(pstr_value != NULL)
			pData->_value = (UINT32)atoi(pstr_value);
		else
			pData->_value = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


