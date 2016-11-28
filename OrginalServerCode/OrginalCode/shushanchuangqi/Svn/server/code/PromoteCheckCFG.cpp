// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromoteCheckCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "PromoteCheckCFG.h"
#include "tinyxml.h"

CPromoteCheckLoader::~CPromoteCheckLoader()
{
	ClearData();
}

void CPromoteCheckLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SPromoteCheckCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CPromoteCheckLoader::LoadData(const std::string& strPath)
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
		SPromoteCheckCFG* pData = new SPromoteCheckCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Type = pDataElem->Attribute("Type");
		if(pstr_Type != NULL)
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_CheckPoint = pDataElem->Attribute("CheckPoint");
		if(pstr_CheckPoint != NULL)
			pData->_CheckPoint = (UINT8)atoi(pstr_CheckPoint);
		else
			pData->_CheckPoint = 0;
		const char* pstr_NotSatisfied = pDataElem->Attribute("NotSatisfied");
		if(pstr_NotSatisfied != NULL)
			pData->_NotSatisfied = pstr_NotSatisfied;
		else
			pData->_NotSatisfied = "";
		const char* pstr_Meet = pDataElem->Attribute("Meet");
		if(pstr_Meet != NULL)
			pData->_Meet = pstr_Meet;
		else
			pData->_Meet = "";
		const char* pstr_Guide = pDataElem->Attribute("Guide");
		if(pstr_Guide != NULL)
			pData->_Guide = pstr_Guide;
		else
			pData->_Guide = "";
		const char* pstr_ButtonName = pDataElem->Attribute("ButtonName");
		if(pstr_ButtonName != NULL)
			pData->_ButtonName = pstr_ButtonName;
		else
			pData->_ButtonName = "";
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT8)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		const char* pstr_unMeet = pDataElem->Attribute("unMeet");
		if(pstr_unMeet != NULL)
			pData->_unMeet = pstr_unMeet;
		else
			pData->_unMeet = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


