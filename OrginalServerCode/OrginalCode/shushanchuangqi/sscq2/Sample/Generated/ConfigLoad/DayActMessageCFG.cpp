// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDayActMessageCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DayActMessageCFG.h"
#include "tinyxml.h"

CDayActMessageLoader::~CDayActMessageLoader()
{
	ClearData();
}

void CDayActMessageLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDayActMessageCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDayActMessageLoader::LoadData(const std::string& strPath)
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
		SDayActMessageCFG* pData = new SDayActMessageCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_ActType = pDataElem->Attribute("ActType");
		if(pstr_ActType != NULL)
			pData->_ActType = (UINT8)atoi(pstr_ActType);
		else
			pData->_ActType = 0;
		const char* pstr_DayActId = pDataElem->Attribute("DayActId");
		if(pstr_DayActId != NULL)
			pData->_DayActId = pstr_DayActId;
		else
			pData->_DayActId = "";
		const char* pstr_WeekDay = pDataElem->Attribute("WeekDay");
		if(pstr_WeekDay != NULL)
			pData->_WeekDay = (UINT8)atoi(pstr_WeekDay);
		else
			pData->_WeekDay = 0;
		const char* pstr_Moth = pDataElem->Attribute("Moth");
		if(pstr_Moth != NULL)
			pData->_Moth = (UINT8)atoi(pstr_Moth);
		else
			pData->_Moth = 0;
		const char* pstr_MothDay = pDataElem->Attribute("MothDay");
		if(pstr_MothDay != NULL)
			pData->_MothDay = (UINT8)atoi(pstr_MothDay);
		else
			pData->_MothDay = 0;
		const char* pstr_AppearTime = pDataElem->Attribute("AppearTime");
		if(pstr_AppearTime != NULL)
			pData->_AppearTime = pstr_AppearTime;
		else
			pData->_AppearTime = "";
		const char* pstr_BeginTime = pDataElem->Attribute("BeginTime");
		if(pstr_BeginTime != NULL)
			pData->_BeginTime = pstr_BeginTime;
		else
			pData->_BeginTime = "";
		const char* pstr_EndTime = pDataElem->Attribute("EndTime");
		if(pstr_EndTime != NULL)
			pData->_EndTime = pstr_EndTime;
		else
			pData->_EndTime = "";
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT32)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


