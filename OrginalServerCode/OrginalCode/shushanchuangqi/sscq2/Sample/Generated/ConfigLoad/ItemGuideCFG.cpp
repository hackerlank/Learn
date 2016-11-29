// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemGuideCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ItemGuideCFG.h"
#include "tinyxml.h"

CItemGuideLoader::~CItemGuideLoader()
{
	ClearData();
}

void CItemGuideLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SItemGuideCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CItemGuideLoader::LoadData(const std::string& strPath)
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
		SItemGuideCFG* pData = new SItemGuideCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Tips = pDataElem->Attribute("Tips");
		if(pstr_Tips != NULL)
			pData->_Tips = pstr_Tips;
		else
			pData->_Tips = "";
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Tag = pDataElem->Attribute("Tag");
		if(pstr_Tag != NULL)
			pData->_Tag = (UINT32)atoi(pstr_Tag);
		else
			pData->_Tag = 0;
		const char* pstr_TagName = pDataElem->Attribute("TagName");
		if(pstr_TagName != NULL)
			pData->_TagName = pstr_TagName;
		else
			pData->_TagName = "";
		const char* pstr_SkipLimit = pDataElem->Attribute("SkipLimit");
		if(pstr_SkipLimit != NULL)
			pData->_SkipLimit = (UINT16)atoi(pstr_SkipLimit);
		else
			pData->_SkipLimit = 0;
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT8)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


