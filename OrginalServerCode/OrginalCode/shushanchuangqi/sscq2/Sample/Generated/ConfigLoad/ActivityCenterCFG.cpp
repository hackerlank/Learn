// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityCenterCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ActivityCenterCFG.h"
#include "tinyxml.h"

CActivityCenterLoader::~CActivityCenterLoader()
{
	ClearData();
}

void CActivityCenterLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SActivityCenterCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CActivityCenterLoader::LoadData(const std::string& strPath)
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
		SActivityCenterCFG* pData = new SActivityCenterCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Index = pDataElem->Attribute("Index");
		if(pstr_Index != NULL)
			pData->_Index = (UINT8)atoi(pstr_Index);
		else
			pData->_Index = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Alarm = pDataElem->Attribute("Alarm");
		if(pstr_Alarm != NULL)
			pData->_Alarm = pstr_Alarm;
		else
			pData->_Alarm = "";
		const char* pstr_Ready = pDataElem->Attribute("Ready");
		if(pstr_Ready != NULL)
			pData->_Ready = (UINT32)atoi(pstr_Ready);
		else
			pData->_Ready = 0;
		const char* pstr_Begin = pDataElem->Attribute("Begin");
		if(pstr_Begin != NULL)
			pData->_Begin = (UINT32)atoi(pstr_Begin);
		else
			pData->_Begin = 0;
		const char* pstr_End = pDataElem->Attribute("End");
		if(pstr_End != NULL)
			pData->_End = (UINT32)atoi(pstr_End);
		else
			pData->_End = 0;
		const char* pstr_bSync = pDataElem->Attribute("bSync");
		if(pstr_bSync != NULL)
			pData->_bSync = (UINT8)atoi(pstr_bSync);
		else
			pData->_bSync = 0;
		const char* pstr_Sync = pDataElem->Attribute("Sync");
		if(pstr_Sync != NULL)
			pData->_Sync = (UINT32)atoi(pstr_Sync);
		else
			pData->_Sync = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


