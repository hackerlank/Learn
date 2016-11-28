// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillBaseCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SkillBaseCFG.h"
#include "tinyxml.h"

CSkillBaseLoader::~CSkillBaseLoader()
{
	ClearData();
}

void CSkillBaseLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSkillBaseCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSkillBaseLoader::LoadData(const std::string& strPath)
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
		SSkillBaseCFG* pData = new SSkillBaseCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_canBeCounter = pDataElem->Attribute("canBeCounter");
		if(pstr_canBeCounter != NULL)
			pData->_canBeCounter = (UINT8)atoi(pstr_canBeCounter);
		else
			pData->_canBeCounter = 0;
		const char* pstr_type = pDataElem->Attribute("type");
		if(pstr_type != NULL)
			pData->_type = (UINT16)atoi(pstr_type);
		else
			pData->_type = 0;
		const char* pstr_skillLink = pDataElem->Attribute("skillLink");
		if(pstr_skillLink != NULL)
			pData->_skillLink = (UINT8)atoi(pstr_skillLink);
		else
			pData->_skillLink = 0;
		const char* pstr_probEffect = pDataElem->Attribute("probEffect");
		if(pstr_probEffect != NULL)
			pData->_probEffect = pstr_probEffect;
		else
			pData->_probEffect = "";
		const char* pstr_effectid = pDataElem->Attribute("effectid");
		if(pstr_effectid != NULL)
			pData->_effectid = pstr_effectid;
		else
			pData->_effectid = "";
		const char* pstr_symbolName = pDataElem->Attribute("symbolName");
		if(pstr_symbolName != NULL)
			pData->_symbolName = pstr_symbolName;
		else
			pData->_symbolName = "";
		const char* pstr_symbol = pDataElem->Attribute("symbol");
		if(pstr_symbol != NULL)
			pData->_symbol = (UINT32)atoi(pstr_symbol);
		else
			pData->_symbol = 0;
		const char* pstr_advance = pDataElem->Attribute("advance");
		if(pstr_advance != NULL)
			pData->_advance = (UINT32)atoi(pstr_advance);
		else
			pData->_advance = 0;
		const char* pstr_career = pDataElem->Attribute("career");
		if(pstr_career != NULL)
			pData->_career = (UINT16)atoi(pstr_career);
		else
			pData->_career = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_LockTIPS = pDataElem->Attribute("LockTIPS");
		if(pstr_LockTIPS != NULL)
			pData->_LockTIPS = pstr_LockTIPS;
		else
			pData->_LockTIPS = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


