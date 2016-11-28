// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CittaCFG.h"
#include "tinyxml.h"

CCittaLoader::~CCittaLoader()
{
	ClearData();
}

void CCittaLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCittaCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCittaLoader::LoadData(const std::string& strPath)
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
		SCittaCFG* pData = new SCittaCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_AttrCount = pDataElem->Attribute("AttrCount");
		if(pstr_AttrCount != NULL)
			pData->_AttrCount = (UINT8)atoi(pstr_AttrCount);
		else
			pData->_AttrCount = 0;
		const char* pstr_SkillCount = pDataElem->Attribute("SkillCount");
		if(pstr_SkillCount != NULL)
			pData->_SkillCount = (UINT8)atoi(pstr_SkillCount);
		else
			pData->_SkillCount = 0;
		const char* pstr_RangeMin = pDataElem->Attribute("RangeMin");
		if(pstr_RangeMin != NULL)
			pData->_RangeMin = (UINT32)atoi(pstr_RangeMin);
		else
			pData->_RangeMin = 0;
		const char* pstr_RangeMax = pDataElem->Attribute("RangeMax");
		if(pstr_RangeMax != NULL)
			pData->_RangeMax = (UINT32)atoi(pstr_RangeMax);
		else
			pData->_RangeMax = 0;
		const char* pstr_Skill = pDataElem->Attribute("Skill");
		if(pstr_Skill != NULL)
			pData->_Skill = pstr_Skill;
		else
			pData->_Skill = "";
		const char* pstr_Signet = pDataElem->Attribute("Signet");
		if(pstr_Signet != NULL)
			pData->_Signet = pstr_Signet;
		else
			pData->_Signet = "";
		const char* pstr_SilverCost = pDataElem->Attribute("SilverCost");
		if(pstr_SilverCost != NULL)
			pData->_SilverCost = (UINT32)atoi(pstr_SilverCost);
		else
			pData->_SilverCost = 0;
		const char* pstr_ResolveMaterial = pDataElem->Attribute("ResolveMaterial");
		if(pstr_ResolveMaterial != NULL)
			pData->_ResolveMaterial = (UINT32)atoi(pstr_ResolveMaterial);
		else
			pData->_ResolveMaterial = 0;
		const char* pstr_ResolveMin = pDataElem->Attribute("ResolveMin");
		if(pstr_ResolveMin != NULL)
			pData->_ResolveMin = (UINT32)atoi(pstr_ResolveMin);
		else
			pData->_ResolveMin = 0;
		const char* pstr_ResolveMax = pDataElem->Attribute("ResolveMax");
		if(pstr_ResolveMax != NULL)
			pData->_ResolveMax = (UINT32)atoi(pstr_ResolveMax);
		else
			pData->_ResolveMax = 0;
		const char* pstr_ResolveLoots = pDataElem->Attribute("ResolveLoots");
		if(pstr_ResolveLoots != NULL)
			pData->_ResolveLoots = (UINT32)atoi(pstr_ResolveLoots);
		else
			pData->_ResolveLoots = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


