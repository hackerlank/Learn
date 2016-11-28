// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildLevelCFG.h"
#include "tinyxml.h"

CGuildLevelLoader::~CGuildLevelLoader()
{
	ClearData();
}

void CGuildLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildLevelLoader::LoadData(const std::string& strPath)
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
		SGuildLevelCFG* pData = new SGuildLevelCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT32)atoi(pstr_Exp);
		else
			pData->_Exp = 0;
		const char* pstr_OriginExp = pDataElem->Attribute("OriginExp");
		if(pstr_OriginExp != NULL)
			pData->_OriginExp = (UINT32)atoi(pstr_OriginExp);
		else
			pData->_OriginExp = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		const char* pstr_Tower = pDataElem->Attribute("Tower");
		if(pstr_Tower != NULL)
			pData->_Tower = (UINT8)atoi(pstr_Tower);
		else
			pData->_Tower = 0;
		const char* pstr_LingBuyLimit = pDataElem->Attribute("LingBuyLimit");
		if(pstr_LingBuyLimit != NULL)
			pData->_LingBuyLimit = (UINT16)atoi(pstr_LingBuyLimit);
		else
			pData->_LingBuyLimit = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


