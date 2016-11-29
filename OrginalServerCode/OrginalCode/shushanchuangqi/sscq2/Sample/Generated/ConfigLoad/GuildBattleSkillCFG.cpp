// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildBattleSkillCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildBattleSkillCFG.h"
#include "tinyxml.h"

CGuildBattleSkillLoader::~CGuildBattleSkillLoader()
{
	ClearData();
}

void CGuildBattleSkillLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildBattleSkillCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildBattleSkillLoader::LoadData(const std::string& strPath)
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
		SGuildBattleSkillCFG* pData = new SGuildBattleSkillCFG;
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
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_BuffID = pDataElem->Attribute("BuffID");
		if(pstr_BuffID != NULL)
			pData->_BuffID = (UINT16)atoi(pstr_BuffID);
		else
			pData->_BuffID = 0;
		const char* pstr_PriceType = pDataElem->Attribute("PriceType");
		if(pstr_PriceType != NULL)
			pData->_PriceType = pstr_PriceType;
		else
			pData->_PriceType = "";
		const char* pstr_Price = pDataElem->Attribute("Price");
		if(pstr_Price != NULL)
			pData->_Price = (UINT16)atoi(pstr_Price);
		else
			pData->_Price = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


