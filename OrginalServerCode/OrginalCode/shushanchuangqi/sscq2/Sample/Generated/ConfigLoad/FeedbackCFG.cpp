// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFeedbackCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FeedbackCFG.h"
#include "tinyxml.h"

CFeedbackLoader::~CFeedbackLoader()
{
	ClearData();
}

void CFeedbackLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFeedbackCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFeedbackLoader::LoadData(const std::string& strPath)
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
		SFeedbackCFG* pData = new SFeedbackCFG;
		const char* pstr_Id = pDataElem->Attribute("Id");
		if(pstr_Id != NULL)
			pData->_Id = (UINT16)atoi(pstr_Id);
		else
			pData->_Id = 0;
		const char* pstr_BgDay = pDataElem->Attribute("BgDay");
		if(pstr_BgDay != NULL)
			pData->_BgDay = (UINT16)atoi(pstr_BgDay);
		else
			pData->_BgDay = 0;
		const char* pstr_EndDay = pDataElem->Attribute("EndDay");
		if(pstr_EndDay != NULL)
			pData->_EndDay = (UINT16)atoi(pstr_EndDay);
		else
			pData->_EndDay = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Quality = pDataElem->Attribute("Quality");
		if(pstr_Quality != NULL)
			pData->_Quality = (UINT8)atoi(pstr_Quality);
		else
			pData->_Quality = 0;
		const char* pstr_Term = pDataElem->Attribute("Term");
		if(pstr_Term != NULL)
			pData->_Term = (UINT16)atoi(pstr_Term);
		else
			pData->_Term = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		const char* pstr_Random1 = pDataElem->Attribute("Random1");
		if(pstr_Random1 != NULL)
			pData->_Random1 = pstr_Random1;
		else
			pData->_Random1 = "";
		const char* pstr_Link = pDataElem->Attribute("Link");
		if(pstr_Link != NULL)
			pData->_Link = pstr_Link;
		else
			pData->_Link = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


