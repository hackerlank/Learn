// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildTechCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildTechCFG.h"
#include "tinyxml.h"

CGuildTechLoader::~CGuildTechLoader()
{
	ClearData();
}

void CGuildTechLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildTechCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildTechLoader::LoadData(const std::string& strPath)
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
		SGuildTechCFG* pData = new SGuildTechCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Attr_ID = pDataElem->Attribute("Attr_ID");
		if(pstr_Attr_ID != NULL)
			pData->_Attr_ID = pstr_Attr_ID;
		else
			pData->_Attr_ID = "";
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
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT32)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		const char* pstr_Value = pDataElem->Attribute("Value");
		if(pstr_Value != NULL)
			pData->_Value = (UINT32)atoi(pstr_Value);
		else
			pData->_Value = 0;
		const char* pstr_RoleLevel = pDataElem->Attribute("RoleLevel");
		if(pstr_RoleLevel != NULL)
			pData->_RoleLevel = (UINT16)atoi(pstr_RoleLevel);
		else
			pData->_RoleLevel = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


