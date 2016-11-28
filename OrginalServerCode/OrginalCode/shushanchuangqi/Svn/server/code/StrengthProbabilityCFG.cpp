// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStrengthProbabilityCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StrengthProbabilityCFG.h"
#include "tinyxml.h"

CStrengthProbabilityLoader::~CStrengthProbabilityLoader()
{
	ClearData();
}

void CStrengthProbabilityLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStrengthProbabilityCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStrengthProbabilityLoader::LoadData(const std::string& strPath)
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
		SStrengthProbabilityCFG* pData = new SStrengthProbabilityCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Probability1 = pDataElem->Attribute("Probability1");
		if(pstr_Probability1 != NULL)
			pData->_Probability1 = (UINT32)atoi(pstr_Probability1);
		else
			pData->_Probability1 = 0;
		const char* pstr_Probability2 = pDataElem->Attribute("Probability2");
		if(pstr_Probability2 != NULL)
			pData->_Probability2 = (UINT32)atoi(pstr_Probability2);
		else
			pData->_Probability2 = 0;
		const char* pstr_Protect2 = pDataElem->Attribute("Protect2");
		if(pstr_Protect2 != NULL)
			pData->_Protect2 = (UINT16)atoi(pstr_Protect2);
		else
			pData->_Protect2 = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


