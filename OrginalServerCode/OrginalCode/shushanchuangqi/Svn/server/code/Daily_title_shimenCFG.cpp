// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_title_shimenCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "Daily_title_shimenCFG.h"
#include "tinyxml.h"

CDaily_title_shimenLoader::~CDaily_title_shimenLoader()
{
	ClearData();
}

void CDaily_title_shimenLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDaily_title_shimenCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDaily_title_shimenLoader::LoadData(const std::string& strPath)
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
		SDaily_title_shimenCFG* pData = new SDaily_title_shimenCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_RU = pDataElem->Attribute("RU");
		if(pstr_RU != NULL)
			pData->_RU = pstr_RU;
		else
			pData->_RU = "";
		const char* pstr_SHI = pDataElem->Attribute("SHI");
		if(pstr_SHI != NULL)
			pData->_SHI = pstr_SHI;
		else
			pData->_SHI = "";
		const char* pstr_DAO = pDataElem->Attribute("DAO");
		if(pstr_DAO != NULL)
			pData->_DAO = pstr_DAO;
		else
			pData->_DAO = "";
		const char* pstr_MO = pDataElem->Attribute("MO");
		if(pstr_MO != NULL)
			pData->_MO = pstr_MO;
		else
			pData->_MO = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


