// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDayActCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DayActCFG.h"
#include "tinyxml.h"

CDayActLoader::~CDayActLoader()
{
	ClearData();
}

void CDayActLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDayActCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDayActLoader::LoadData(const std::string& strPath)
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
		SDayActCFG* pData = new SDayActCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_ActType = pDataElem->Attribute("ActType");
		if(pstr_ActType != NULL)
			pData->_ActType = (UINT8)atoi(pstr_ActType);
		else
			pData->_ActType = 0;
		const char* pstr_SpecialType = pDataElem->Attribute("SpecialType");
		if(pstr_SpecialType != NULL)
			pData->_SpecialType = (UINT8)atoi(pstr_SpecialType);
		else
			pData->_SpecialType = 0;
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
		const char* pstr_OpenDay = pDataElem->Attribute("OpenDay");
		if(pstr_OpenDay != NULL)
			pData->_OpenDay = (UINT8)atoi(pstr_OpenDay);
		else
			pData->_OpenDay = 0;
		const char* pstr_AlarmTime = pDataElem->Attribute("AlarmTime");
		if(pstr_AlarmTime != NULL)
			pData->_AlarmTime = pstr_AlarmTime;
		else
			pData->_AlarmTime = "";
		const char* pstr_ReadyTime = pDataElem->Attribute("ReadyTime");
		if(pstr_ReadyTime != NULL)
			pData->_ReadyTime = pstr_ReadyTime;
		else
			pData->_ReadyTime = "";
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
		const char* pstr_dwParam = pDataElem->Attribute("dwParam");
		if(pstr_dwParam != NULL)
			pData->_dwParam = (UINT32)atoi(pstr_dwParam);
		else
			pData->_dwParam = 0;
		const char* pstr_strParam = pDataElem->Attribute("strParam");
		if(pstr_strParam != NULL)
			pData->_strParam = pstr_strParam;
		else
			pData->_strParam = "";
		const char* pstr_Script = pDataElem->Attribute("Script");
		if(pstr_Script != NULL)
			pData->_Script = pstr_Script;
		else
			pData->_Script = "";
		const char* pstr_CrossServer = pDataElem->Attribute("CrossServer");
		if(pstr_CrossServer != NULL)
			pData->_CrossServer = (int)atoi(pstr_CrossServer)>0?true:false;
		else
			pData->_CrossServer = false;
		const char* pstr_IsRestartCheck = pDataElem->Attribute("IsRestartCheck");
		if(pstr_IsRestartCheck != NULL)
			pData->_IsRestartCheck = (int)atoi(pstr_IsRestartCheck)>0?true:false;
		else
			pData->_IsRestartCheck = false;
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT32)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		const char* pstr_Limit = pDataElem->Attribute("Limit");
		if(pstr_Limit != NULL)
			pData->_Limit = pstr_Limit;
		else
			pData->_Limit = "";
		const char* pstr_Reward = pDataElem->Attribute("Reward");
		if(pstr_Reward != NULL)
			pData->_Reward = pstr_Reward;
		else
			pData->_Reward = "";
		const char* pstr_QqRemind = pDataElem->Attribute("QqRemind");
		if(pstr_QqRemind != NULL)
			pData->_QqRemind = pstr_QqRemind;
		else
			pData->_QqRemind = "";
		const char* pstr_Description = pDataElem->Attribute("Description");
		if(pstr_Description != NULL)
			pData->_Description = pstr_Description;
		else
			pData->_Description = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


