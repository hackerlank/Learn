// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ActivityCFG.h"
#include "tinyxml.h"

CActivityLoader::~CActivityLoader()
{
	ClearData();
}

void CActivityLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SActivityCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CActivityLoader::LoadData(const std::string& strPath)
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
		SActivityCFG* pData = new SActivityCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Activity = pDataElem->Attribute("Activity");
		if(pstr_Activity != NULL)
			pData->_Activity = (UINT16)atoi(pstr_Activity);
		else
			pData->_Activity = 0;
		const char* pstr_LootID = pDataElem->Attribute("LootID");
		if(pstr_LootID != NULL)
			pData->_LootID = (UINT32)atoi(pstr_LootID);
		else
			pData->_LootID = 0;
		const char* pstr_VIPLevel = pDataElem->Attribute("VIPLevel");
		if(pstr_VIPLevel != NULL)
			pData->_VIPLevel = (UINT8)atoi(pstr_VIPLevel);
		else
			pData->_VIPLevel = 0;
		const char* pstr_VIPLootID = pDataElem->Attribute("VIPLootID");
		if(pstr_VIPLootID != NULL)
			pData->_VIPLootID = (UINT32)atoi(pstr_VIPLootID);
		else
			pData->_VIPLootID = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


