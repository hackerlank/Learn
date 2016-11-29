// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STitleCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TitleCFG.h"
#include "tinyxml.h"

CTitleLoader::~CTitleLoader()
{
	ClearData();
}

void CTitleLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STitleCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTitleLoader::LoadData(const std::string& strPath)
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
		STitleCFG* pData = new STitleCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_RequireID = pDataElem->Attribute("RequireID");
		if(pstr_RequireID != NULL)
			pData->_RequireID = (UINT16)atoi(pstr_RequireID);
		else
			pData->_RequireID = 0;
		const char* pstr_Assets = pDataElem->Attribute("Assets");
		if(pstr_Assets != NULL)
			pData->_Assets = (UINT16)atoi(pstr_Assets);
		else
			pData->_Assets = 0;
		const char* pstr_PropID = pDataElem->Attribute("PropID");
		if(pstr_PropID != NULL)
			pData->_PropID = (UINT16)atoi(pstr_PropID);
		else
			pData->_PropID = 0;
		const char* pstr_Time = pDataElem->Attribute("Time");
		if(pstr_Time != NULL)
			pData->_Time = (UINT32)atoi(pstr_Time);
		else
			pData->_Time = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


