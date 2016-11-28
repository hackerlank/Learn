// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSevenDaysTargetCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SevenDaysTargetCFG.h"
#include "tinyxml.h"

CSevenDaysTargetLoader::~CSevenDaysTargetLoader()
{
	ClearData();
}

void CSevenDaysTargetLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSevenDaysTargetCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSevenDaysTargetLoader::LoadData(const std::string& strPath)
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
		SSevenDaysTargetCFG* pData = new SSevenDaysTargetCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Day = pDataElem->Attribute("Day");
		if(pstr_Day != NULL)
			pData->_Day = (UINT16)atoi(pstr_Day);
		else
			pData->_Day = 0;
		const char* pstr_EventID = pDataElem->Attribute("EventID");
		if(pstr_EventID != NULL)
			pData->_EventID = pstr_EventID;
		else
			pData->_EventID = "";
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


