// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SXinfaCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "XinfaCFG.h"
#include "tinyxml.h"

CXinfaLoader::~CXinfaLoader()
{
	ClearData();
}

void CXinfaLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SXinfaCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CXinfaLoader::LoadData(const std::string& strPath)
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
		SXinfaCFG* pData = new SXinfaCFG;
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
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Limit = pDataElem->Attribute("Limit");
		if(pstr_Limit != NULL)
			pData->_Limit = (UINT8)atoi(pstr_Limit);
		else
			pData->_Limit = 0;
		const char* pstr_Effect = pDataElem->Attribute("Effect");
		if(pstr_Effect != NULL)
			pData->_Effect = (UINT16)atoi(pstr_Effect);
		else
			pData->_Effect = 0;
		const char* pstr_NeedItem = pDataElem->Attribute("NeedItem");
		if(pstr_NeedItem != NULL)
			pData->_NeedItem = pstr_NeedItem;
		else
			pData->_NeedItem = "";
		const char* pstr_Description = pDataElem->Attribute("Description");
		if(pstr_Description != NULL)
			pData->_Description = pstr_Description;
		else
			pData->_Description = "";
		const char* pstr_Remark = pDataElem->Attribute("Remark");
		if(pstr_Remark != NULL)
			pData->_Remark = pstr_Remark;
		else
			pData->_Remark = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


