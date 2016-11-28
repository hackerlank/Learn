// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSevenConsumeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SevenConsumeCFG.h"
#include "tinyxml.h"

CSevenConsumeLoader::~CSevenConsumeLoader()
{
	ClearData();
}

void CSevenConsumeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSevenConsumeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSevenConsumeLoader::LoadData(const std::string& strPath)
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
		SSevenConsumeCFG* pData = new SSevenConsumeCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Limit = pDataElem->Attribute("Limit");
		if(pstr_Limit != NULL)
			pData->_Limit = (UINT16)atoi(pstr_Limit);
		else
			pData->_Limit = 0;
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


