// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAchievementCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "AchievementCFG.h"
#include "tinyxml.h"

CAchievementLoader::~CAchievementLoader()
{
	ClearData();
}

void CAchievementLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SAchievementCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CAchievementLoader::LoadData(const std::string& strPath)
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
		SAchievementCFG* pData = new SAchievementCFG;
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
		const char* pstr_Type1 = pDataElem->Attribute("Type1");
		if(pstr_Type1 != NULL)
			pData->_Type1 = (UINT16)atoi(pstr_Type1);
		else
			pData->_Type1 = 0;
		const char* pstr_Type2 = pDataElem->Attribute("Type2");
		if(pstr_Type2 != NULL)
			pData->_Type2 = (UINT16)atoi(pstr_Type2);
		else
			pData->_Type2 = 0;
		const char* pstr_Career = pDataElem->Attribute("Career");
		if(pstr_Career != NULL)
			pData->_Career = (UINT8)atoi(pstr_Career);
		else
			pData->_Career = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_EventID = pDataElem->Attribute("EventID");
		if(pstr_EventID != NULL)
			pData->_EventID = (UINT16)atoi(pstr_EventID);
		else
			pData->_EventID = 0;
		const char* pstr_EventGroup = pDataElem->Attribute("EventGroup");
		if(pstr_EventGroup != NULL)
			pData->_EventGroup = pstr_EventGroup;
		else
			pData->_EventGroup = "";
		const char* pstr_AssetsText = pDataElem->Attribute("AssetsText");
		if(pstr_AssetsText != NULL)
			pData->_AssetsText = pstr_AssetsText;
		else
			pData->_AssetsText = "";
		const char* pstr_AP = pDataElem->Attribute("AP");
		if(pstr_AP != NULL)
			pData->_AP = (UINT16)atoi(pstr_AP);
		else
			pData->_AP = 0;
		const char* pstr_AwardType = pDataElem->Attribute("AwardType");
		if(pstr_AwardType != NULL)
			pData->_AwardType = (UINT16)atoi(pstr_AwardType);
		else
			pData->_AwardType = 0;
		const char* pstr_AwardPara = pDataElem->Attribute("AwardPara");
		if(pstr_AwardPara != NULL)
			pData->_AwardPara = (UINT16)atoi(pstr_AwardPara);
		else
			pData->_AwardPara = 0;
		const char* pstr_AwardId = pDataElem->Attribute("AwardId");
		if(pstr_AwardId != NULL)
			pData->_AwardId = pstr_AwardId;
		else
			pData->_AwardId = "";
		const char* pstr_AwardInfo = pDataElem->Attribute("AwardInfo");
		if(pstr_AwardInfo != NULL)
			pData->_AwardInfo = pstr_AwardInfo;
		else
			pData->_AwardInfo = "";
		const char* pstr_Share = pDataElem->Attribute("Share");
		if(pstr_Share != NULL)
			pData->_Share = (UINT8)atoi(pstr_Share);
		else
			pData->_Share = 0;
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


