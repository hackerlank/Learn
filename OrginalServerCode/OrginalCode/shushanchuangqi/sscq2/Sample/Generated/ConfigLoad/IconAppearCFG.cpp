// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SIconAppearCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "IconAppearCFG.h"
#include "tinyxml.h"

CIconAppearLoader::~CIconAppearLoader()
{
	ClearData();
}

void CIconAppearLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SIconAppearCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CIconAppearLoader::LoadData(const std::string& strPath)
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
		SIconAppearCFG* pData = new SIconAppearCFG;
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
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Parameter = pDataElem->Attribute("Parameter");
		if(pstr_Parameter != NULL)
			pData->_Parameter = pstr_Parameter;
		else
			pData->_Parameter = "";
		const char* pstr_RechageOpen = pDataElem->Attribute("RechageOpen");
		if(pstr_RechageOpen != NULL)
			pData->_RechageOpen = (UINT8)atoi(pstr_RechageOpen);
		else
			pData->_RechageOpen = 0;
		const char* pstr_data = pDataElem->Attribute("data");
		if(pstr_data != NULL)
			pData->_data = pstr_data;
		else
			pData->_data = "";
		const char* pstr_IsActivity = pDataElem->Attribute("IsActivity");
		if(pstr_IsActivity != NULL)
			pData->_IsActivity = (UINT8)atoi(pstr_IsActivity);
		else
			pData->_IsActivity = 0;
		const char* pstr_activityID = pDataElem->Attribute("activityID");
		if(pstr_activityID != NULL)
			pData->_activityID = (UINT32)atoi(pstr_activityID);
		else
			pData->_activityID = 0;
		const char* pstr_tips = pDataElem->Attribute("tips");
		if(pstr_tips != NULL)
			pData->_tips = pstr_tips;
		else
			pData->_tips = "";
		const char* pstr_Des = pDataElem->Attribute("Des");
		if(pstr_Des != NULL)
			pData->_Des = pstr_Des;
		else
			pData->_Des = "";
		const char* pstr_Clusion = pDataElem->Attribute("Clusion");
		if(pstr_Clusion != NULL)
			pData->_Clusion = pstr_Clusion;
		else
			pData->_Clusion = "";
		const char* pstr_Coexist = pDataElem->Attribute("Coexist");
		if(pstr_Coexist != NULL)
			pData->_Coexist = pstr_Coexist;
		else
			pData->_Coexist = "";
		const char* pstr_FullScn = pDataElem->Attribute("FullScn");
		if(pstr_FullScn != NULL)
			pData->_FullScn = (UINT8)atoi(pstr_FullScn);
		else
			pData->_FullScn = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


