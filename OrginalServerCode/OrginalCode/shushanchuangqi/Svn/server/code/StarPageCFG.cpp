// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStarPageCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StarPageCFG.h"
#include "tinyxml.h"

CStarPageLoader::~CStarPageLoader()
{
	ClearData();
}

void CStarPageLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStarPageCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStarPageLoader::LoadData(const std::string& strPath)
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
		SStarPageCFG* pData = new SStarPageCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_PageType = pDataElem->Attribute("PageType");
		if(pstr_PageType != NULL)
			pData->_PageType = (UINT8)atoi(pstr_PageType);
		else
			pData->_PageType = 0;
		const char* pstr_PageLevel = pDataElem->Attribute("PageLevel");
		if(pstr_PageLevel != NULL)
			pData->_PageLevel = (UINT8)atoi(pstr_PageLevel);
		else
			pData->_PageLevel = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


