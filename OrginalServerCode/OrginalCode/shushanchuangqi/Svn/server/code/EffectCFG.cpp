// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEffectCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "EffectCFG.h"
#include "tinyxml.h"

CEffectLoader::~CEffectLoader()
{
	ClearData();
}

void CEffectLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SEffectCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CEffectLoader::LoadData(const std::string& strPath)
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
		SEffectCFG* pData = new SEffectCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_EffectType = pDataElem->Attribute("EffectType");
		if(pstr_EffectType != NULL)
			pData->_EffectType = (UINT8)atoi(pstr_EffectType);
		else
			pData->_EffectType = 0;
		const char* pstr_BuffID = pDataElem->Attribute("BuffID");
		if(pstr_BuffID != NULL)
			pData->_BuffID = (UINT16)atoi(pstr_BuffID);
		else
			pData->_BuffID = 0;
		const char* pstr_EffectIcon = pDataElem->Attribute("EffectIcon");
		if(pstr_EffectIcon != NULL)
			pData->_EffectIcon = (UINT16)atoi(pstr_EffectIcon);
		else
			pData->_EffectIcon = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Effect = pDataElem->Attribute("Effect");
		if(pstr_Effect != NULL)
			pData->_Effect = (UINT32)atoi(pstr_Effect);
		else
			pData->_Effect = 0;
		const char* pstr_Description = pDataElem->Attribute("Description");
		if(pstr_Description != NULL)
			pData->_Description = pstr_Description;
		else
			pData->_Description = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


