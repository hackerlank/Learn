// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFeedbackBagCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FeedbackBagCFG.h"
#include "tinyxml.h"

CFeedbackBagLoader::~CFeedbackBagLoader()
{
	ClearData();
}

void CFeedbackBagLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFeedbackBagCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFeedbackBagLoader::LoadData(const std::string& strPath)
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
		SFeedbackBagCFG* pData = new SFeedbackBagCFG;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
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
		const char* pstr_OldCost = pDataElem->Attribute("OldCost");
		if(pstr_OldCost != NULL)
			pData->_OldCost = (UINT16)atoi(pstr_OldCost);
		else
			pData->_OldCost = 0;
		const char* pstr_NewCost = pDataElem->Attribute("NewCost");
		if(pstr_NewCost != NULL)
			pData->_NewCost = (UINT16)atoi(pstr_NewCost);
		else
			pData->_NewCost = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		const char* pstr_BuyNum = pDataElem->Attribute("BuyNum");
		if(pstr_BuyNum != NULL)
			pData->_BuyNum = (UINT16)atoi(pstr_BuyNum);
		else
			pData->_BuyNum = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


