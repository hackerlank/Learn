// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityOperatingCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ActivityOperatingCFG.h"
#include "tinyxml.h"

CActivityOperatingLoader::~CActivityOperatingLoader()
{
	ClearData();
}

void CActivityOperatingLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SActivityOperatingCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CActivityOperatingLoader::LoadData(const std::string& strPath)
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
		SActivityOperatingCFG* pData = new SActivityOperatingCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Stye = pDataElem->Attribute("Stye");
		if(pstr_Stye != NULL)
			pData->_Stye = (UINT16)atoi(pstr_Stye);
		else
			pData->_Stye = 0;
		const char* pstr_TotalType = pDataElem->Attribute("TotalType");
		if(pstr_TotalType != NULL)
			pData->_TotalType = (UINT16)atoi(pstr_TotalType);
		else
			pData->_TotalType = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_SortOn = pDataElem->Attribute("SortOn");
		if(pstr_SortOn != NULL)
			pData->_SortOn = (UINT16)atoi(pstr_SortOn);
		else
			pData->_SortOn = 0;
		const char* pstr_Client_Type = pDataElem->Attribute("Client_Type");
		if(pstr_Client_Type != NULL)
			pData->_Client_Type = (UINT16)atoi(pstr_Client_Type);
		else
			pData->_Client_Type = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_ConfigID = pDataElem->Attribute("ConfigID");
		if(pstr_ConfigID != NULL)
			pData->_ConfigID = (UINT16)atoi(pstr_ConfigID);
		else
			pData->_ConfigID = 0;
		const char* pstr_Time1 = pDataElem->Attribute("Time1");
		if(pstr_Time1 != NULL)
			pData->_Time1 = pstr_Time1;
		else
			pData->_Time1 = "";
		const char* pstr_Time2 = pDataElem->Attribute("Time2");
		if(pstr_Time2 != NULL)
			pData->_Time2 = pstr_Time2;
		else
			pData->_Time2 = "";
		const char* pstr_Time3 = pDataElem->Attribute("Time3");
		if(pstr_Time3 != NULL)
			pData->_Time3 = pstr_Time3;
		else
			pData->_Time3 = "";
		const char* pstr_Time4 = pDataElem->Attribute("Time4");
		if(pstr_Time4 != NULL)
			pData->_Time4 = pstr_Time4;
		else
			pData->_Time4 = "";
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_IconUrl = pDataElem->Attribute("IconUrl");
		if(pstr_IconUrl != NULL)
			pData->_IconUrl = (UINT16)atoi(pstr_IconUrl);
		else
			pData->_IconUrl = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


