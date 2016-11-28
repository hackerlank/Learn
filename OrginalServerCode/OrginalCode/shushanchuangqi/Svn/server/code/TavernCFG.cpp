// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STavernCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TavernCFG.h"
#include "tinyxml.h"

CTavernLoader::~CTavernLoader()
{
	ClearData();
}

void CTavernLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STavernCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTavernLoader::LoadData(const std::string& strPath)
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
		STavernCFG* pData = new STavernCFG;
		const char* pstr_TemplateId = pDataElem->Attribute("TemplateId");
		if(pstr_TemplateId != NULL)
			pData->_TemplateId = (UINT16)atoi(pstr_TemplateId);
		else
			pData->_TemplateId = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Condition = pDataElem->Attribute("Condition");
		if(pstr_Condition != NULL)
			pData->_Condition = (UINT16)atoi(pstr_Condition);
		else
			pData->_Condition = 0;
		const char* pstr_TavernLevel = pDataElem->Attribute("TavernLevel");
		if(pstr_TavernLevel != NULL)
			pData->_TavernLevel = (UINT16)atoi(pstr_TavernLevel);
		else
			pData->_TavernLevel = 0;
		const char* pstr_TavernPIC = pDataElem->Attribute("TavernPIC");
		if(pstr_TavernPIC != NULL)
			pData->_TavernPIC = (UINT16)atoi(pstr_TavernPIC);
		else
			pData->_TavernPIC = 0;
		const char* pstr_Hero1 = pDataElem->Attribute("Hero1");
		if(pstr_Hero1 != NULL)
			pData->_Hero1 = (UINT16)atoi(pstr_Hero1);
		else
			pData->_Hero1 = 0;
		const char* pstr_Hero1Zoom = pDataElem->Attribute("Hero1Zoom");
		if(pstr_Hero1Zoom != NULL)
			pData->_Hero1Zoom = (FLOAT)atof(pstr_Hero1Zoom);
		else
			pData->_Hero1Zoom = 0.0f;
		const char* pstr_Hero1GetConId = pDataElem->Attribute("Hero1GetConId");
		if(pstr_Hero1GetConId != NULL)
			pData->_Hero1GetConId = (UINT16)atoi(pstr_Hero1GetConId);
		else
			pData->_Hero1GetConId = 0;
		const char* pstr_Hero2 = pDataElem->Attribute("Hero2");
		if(pstr_Hero2 != NULL)
			pData->_Hero2 = (UINT16)atoi(pstr_Hero2);
		else
			pData->_Hero2 = 0;
		const char* pstr_Hero2Zoom = pDataElem->Attribute("Hero2Zoom");
		if(pstr_Hero2Zoom != NULL)
			pData->_Hero2Zoom = (FLOAT)atof(pstr_Hero2Zoom);
		else
			pData->_Hero2Zoom = 0.0f;
		const char* pstr_Hero2GetConId = pDataElem->Attribute("Hero2GetConId");
		if(pstr_Hero2GetConId != NULL)
			pData->_Hero2GetConId = (UINT16)atoi(pstr_Hero2GetConId);
		else
			pData->_Hero2GetConId = 0;
		const char* pstr_Hero3 = pDataElem->Attribute("Hero3");
		if(pstr_Hero3 != NULL)
			pData->_Hero3 = (UINT16)atoi(pstr_Hero3);
		else
			pData->_Hero3 = 0;
		const char* pstr_Hero3Zoom = pDataElem->Attribute("Hero3Zoom");
		if(pstr_Hero3Zoom != NULL)
			pData->_Hero3Zoom = (FLOAT)atof(pstr_Hero3Zoom);
		else
			pData->_Hero3Zoom = 0.0f;
		const char* pstr_Hero3GetConId = pDataElem->Attribute("Hero3GetConId");
		if(pstr_Hero3GetConId != NULL)
			pData->_Hero3GetConId = (UINT16)atoi(pstr_Hero3GetConId);
		else
			pData->_Hero3GetConId = 0;
		const char* pstr_Hero4 = pDataElem->Attribute("Hero4");
		if(pstr_Hero4 != NULL)
			pData->_Hero4 = (UINT16)atoi(pstr_Hero4);
		else
			pData->_Hero4 = 0;
		const char* pstr_Hero4Zoom = pDataElem->Attribute("Hero4Zoom");
		if(pstr_Hero4Zoom != NULL)
			pData->_Hero4Zoom = (FLOAT)atof(pstr_Hero4Zoom);
		else
			pData->_Hero4Zoom = 0.0f;
		const char* pstr_Hero4GetConId = pDataElem->Attribute("Hero4GetConId");
		if(pstr_Hero4GetConId != NULL)
			pData->_Hero4GetConId = (UINT16)atoi(pstr_Hero4GetConId);
		else
			pData->_Hero4GetConId = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


