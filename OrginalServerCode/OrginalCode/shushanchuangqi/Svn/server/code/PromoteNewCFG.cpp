// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromoteNewCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "PromoteNewCFG.h"
#include "tinyxml.h"

CPromoteNewLoader::~CPromoteNewLoader()
{
	ClearData();
}

void CPromoteNewLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SPromoteNewCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CPromoteNewLoader::LoadData(const std::string& strPath)
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
		SPromoteNewCFG* pData = new SPromoteNewCFG;
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
		const char* pstr_Page = pDataElem->Attribute("Page");
		if(pstr_Page != NULL)
			pData->_Page = (UINT8)atoi(pstr_Page);
		else
			pData->_Page = 0;
		const char* pstr_PageName = pDataElem->Attribute("PageName");
		if(pstr_PageName != NULL)
			pData->_PageName = pstr_PageName;
		else
			pData->_PageName = "";
		const char* pstr_Include = pDataElem->Attribute("Include");
		if(pstr_Include != NULL)
			pData->_Include = pstr_Include;
		else
			pData->_Include = "";
		const char* pstr_startLevel = pDataElem->Attribute("startLevel");
		if(pstr_startLevel != NULL)
			pData->_startLevel = (UINT8)atoi(pstr_startLevel);
		else
			pData->_startLevel = 0;
		const char* pstr_EndLevel = pDataElem->Attribute("EndLevel");
		if(pstr_EndLevel != NULL)
			pData->_EndLevel = (UINT8)atoi(pstr_EndLevel);
		else
			pData->_EndLevel = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


