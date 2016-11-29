// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_shimentaskColorCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "Daily_shimentaskColorCFG.h"
#include "tinyxml.h"

CDaily_shimentaskColorLoader::~CDaily_shimentaskColorLoader()
{
	ClearData();
}

void CDaily_shimentaskColorLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDaily_shimentaskColorCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDaily_shimentaskColorLoader::LoadData(const std::string& strPath)
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
		SDaily_shimentaskColorCFG* pData = new SDaily_shimentaskColorCFG;
		const char* pstr_TaskId = pDataElem->Attribute("TaskId");
		if(pstr_TaskId != NULL)
			pData->_TaskId = (UINT16)atoi(pstr_TaskId);
		else
			pData->_TaskId = 0;
		const char* pstr_level = pDataElem->Attribute("level");
		if(pstr_level != NULL)
			pData->_level = (UINT16)atoi(pstr_level);
		else
			pData->_level = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_LootId = pDataElem->Attribute("LootId");
		if(pstr_LootId != NULL)
			pData->_LootId = (UINT32)atoi(pstr_LootId);
		else
			pData->_LootId = 0;
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT32)atoi(pstr_Exp);
		else
			pData->_Exp = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


