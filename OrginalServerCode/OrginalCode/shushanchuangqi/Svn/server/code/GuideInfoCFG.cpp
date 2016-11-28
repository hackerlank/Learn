// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuideInfoCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuideInfoCFG.h"
#include "tinyxml.h"

CGuideInfoLoader::~CGuideInfoLoader()
{
	ClearData();
}

void CGuideInfoLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuideInfoCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuideInfoLoader::LoadData(const std::string& strPath)
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
		SGuideInfoCFG* pData = new SGuideInfoCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_TaskId = pDataElem->Attribute("TaskId");
		if(pstr_TaskId != NULL)
			pData->_TaskId = (UINT32)atoi(pstr_TaskId);
		else
			pData->_TaskId = 0;
		const char* pstr_GuideStep = pDataElem->Attribute("GuideStep");
		if(pstr_GuideStep != NULL)
			pData->_GuideStep = (UINT8)atoi(pstr_GuideStep);
		else
			pData->_GuideStep = 0;
		const char* pstr_GuideInfo = pDataElem->Attribute("GuideInfo");
		if(pstr_GuideInfo != NULL)
			pData->_GuideInfo = pstr_GuideInfo;
		else
			pData->_GuideInfo = "";
		const char* pstr_NpcIcon = pDataElem->Attribute("NpcIcon");
		if(pstr_NpcIcon != NULL)
			pData->_NpcIcon = pstr_NpcIcon;
		else
			pData->_NpcIcon = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


