// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCampCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CampCFG.h"
#include "tinyxml.h"

CCampLoader::~CCampLoader()
{
	ClearData();
}

void CCampLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCampCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCampLoader::LoadData(const std::string& strPath)
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
		SCampCFG* pData = new SCampCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_ReliveMap = pDataElem->Attribute("ReliveMap");
		if(pstr_ReliveMap != NULL)
			pData->_ReliveMap = (UINT16)atoi(pstr_ReliveMap);
		else
			pData->_ReliveMap = 0;
		const char* pstr_ReliveX = pDataElem->Attribute("ReliveX");
		if(pstr_ReliveX != NULL)
			pData->_ReliveX = (FLOAT)atof(pstr_ReliveX);
		else
			pData->_ReliveX = 0.0f;
		const char* pstr_ReliveY = pDataElem->Attribute("ReliveY");
		if(pstr_ReliveY != NULL)
			pData->_ReliveY = (FLOAT)atof(pstr_ReliveY);
		else
			pData->_ReliveY = 0.0f;
		const char* pstr_CityID_1 = pDataElem->Attribute("CityID_1");
		if(pstr_CityID_1 != NULL)
			pData->_CityID_1 = (UINT16)atoi(pstr_CityID_1);
		else
			pData->_CityID_1 = 0;
		const char* pstr_WarID_1 = pDataElem->Attribute("WarID_1");
		if(pstr_WarID_1 != NULL)
			pData->_WarID_1 = (UINT16)atoi(pstr_WarID_1);
		else
			pData->_WarID_1 = 0;
		const char* pstr_CityID_2 = pDataElem->Attribute("CityID_2");
		if(pstr_CityID_2 != NULL)
			pData->_CityID_2 = (UINT16)atoi(pstr_CityID_2);
		else
			pData->_CityID_2 = 0;
		const char* pstr_WarID_2 = pDataElem->Attribute("WarID_2");
		if(pstr_WarID_2 != NULL)
			pData->_WarID_2 = (UINT16)atoi(pstr_WarID_2);
		else
			pData->_WarID_2 = 0;
		const char* pstr_MapID = pDataElem->Attribute("MapID");
		if(pstr_MapID != NULL)
			pData->_MapID = (UINT16)atoi(pstr_MapID);
		else
			pData->_MapID = 0;
		const char* pstr_EnterX = pDataElem->Attribute("EnterX");
		if(pstr_EnterX != NULL)
			pData->_EnterX = (FLOAT)atof(pstr_EnterX);
		else
			pData->_EnterX = 0.0f;
		const char* pstr_EnterY = pDataElem->Attribute("EnterY");
		if(pstr_EnterY != NULL)
			pData->_EnterY = (FLOAT)atof(pstr_EnterY);
		else
			pData->_EnterY = 0.0f;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


