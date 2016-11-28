// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityPointCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ActivityPointCFG.h"
#include "tinyxml.h"

CActivityPointLoader::~CActivityPointLoader()
{
	ClearData();
}

void CActivityPointLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SActivityPointCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CActivityPointLoader::LoadData(const std::string& strPath)
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
		SActivityPointCFG* pData = new SActivityPointCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_strDesc = pDataElem->Attribute("strDesc");
		if(pstr_strDesc != NULL)
			pData->_strDesc = pstr_strDesc;
		else
			pData->_strDesc = "";
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_SkipLimit = pDataElem->Attribute("SkipLimit");
		if(pstr_SkipLimit != NULL)
			pData->_SkipLimit = (UINT16)atoi(pstr_SkipLimit);
		else
			pData->_SkipLimit = 0;
		const char* pstr_GetActivity = pDataElem->Attribute("GetActivity");
		if(pstr_GetActivity != NULL)
			pData->_GetActivity = (UINT8)atoi(pstr_GetActivity);
		else
			pData->_GetActivity = 0;
		const char* pstr_MaxTimes = pDataElem->Attribute("MaxTimes");
		if(pstr_MaxTimes != NULL)
			pData->_MaxTimes = pstr_MaxTimes;
		else
			pData->_MaxTimes = "";
		const char* pstr_Share = pDataElem->Attribute("Share");
		if(pstr_Share != NULL)
			pData->_Share = (UINT8)atoi(pstr_Share);
		else
			pData->_Share = 0;
		const char* pstr_Remind = pDataElem->Attribute("Remind");
		if(pstr_Remind != NULL)
			pData->_Remind = (UINT8)atoi(pstr_Remind);
		else
			pData->_Remind = 0;
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = pstr_Title;
		else
			pData->_Title = "";
		const char* pstr_Msg = pDataElem->Attribute("Msg");
		if(pstr_Msg != NULL)
			pData->_Msg = pstr_Msg;
		else
			pData->_Msg = "";
		const char* pstr_Summary = pDataElem->Attribute("Summary");
		if(pstr_Summary != NULL)
			pData->_Summary = pstr_Summary;
		else
			pData->_Summary = "";
		const char* pstr_Button = pDataElem->Attribute("Button");
		if(pstr_Button != NULL)
			pData->_Button = (UINT8)atoi(pstr_Button);
		else
			pData->_Button = 0;
		const char* pstr_Pic = pDataElem->Attribute("Pic");
		if(pstr_Pic != NULL)
			pData->_Pic = (UINT16)atoi(pstr_Pic);
		else
			pData->_Pic = 0;
		const char* pstr_ShareSort = pDataElem->Attribute("ShareSort");
		if(pstr_ShareSort != NULL)
			pData->_ShareSort = (UINT8)atoi(pstr_ShareSort);
		else
			pData->_ShareSort = 0;
		const char* pstr_ShareName = pDataElem->Attribute("ShareName");
		if(pstr_ShareName != NULL)
			pData->_ShareName = pstr_ShareName;
		else
			pData->_ShareName = "";
		const char* pstr_ShareDesc = pDataElem->Attribute("ShareDesc");
		if(pstr_ShareDesc != NULL)
			pData->_ShareDesc = pstr_ShareDesc;
		else
			pData->_ShareDesc = "";
		const char* pstr_ShareSummary = pDataElem->Attribute("ShareSummary");
		if(pstr_ShareSummary != NULL)
			pData->_ShareSummary = pstr_ShareSummary;
		else
			pData->_ShareSummary = "";
		const char* pstr_ShareAwardId = pDataElem->Attribute("ShareAwardId");
		if(pstr_ShareAwardId != NULL)
			pData->_ShareAwardId = pstr_ShareAwardId;
		else
			pData->_ShareAwardId = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


