// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFoundationCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FoundationCFG.h"
#include "tinyxml.h"

CFoundationLoader::~CFoundationLoader()
{
	ClearData();
}

void CFoundationLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFoundationCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFoundationLoader::LoadData(const std::string& strPath)
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
		SFoundationCFG* pData = new SFoundationCFG;
		const char* pstr_Uid = pDataElem->Attribute("Uid");
		if(pstr_Uid != NULL)
			pData->_Uid = (UINT8)atoi(pstr_Uid);
		else
			pData->_Uid = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = pstr_Type;
		else
			pData->_Type = "";
		const char* pstr_Spend = pDataElem->Attribute("Spend");
		if(pstr_Spend != NULL)
			pData->_Spend = (UINT32)atoi(pstr_Spend);
		else
			pData->_Spend = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = pstr_Level;
		else
			pData->_Level = "";
		const char* pstr_Rebate = pDataElem->Attribute("Rebate");
		if(pstr_Rebate != NULL)
			pData->_Rebate = pstr_Rebate;
		else
			pData->_Rebate = "";
		const char* pstr_Reward = pDataElem->Attribute("Reward");
		if(pstr_Reward != NULL)
			pData->_Reward = pstr_Reward;
		else
			pData->_Reward = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


