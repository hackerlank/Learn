// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStovePropCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StovePropCFG.h"
#include "tinyxml.h"

CStovePropLoader::~CStovePropLoader()
{
	ClearData();
}

void CStovePropLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStovePropCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStovePropLoader::LoadData(const std::string& strPath)
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
		SStovePropCFG* pData = new SStovePropCFG;
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
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = (UINT16)atoi(pstr_Icon);
		else
			pData->_Icon = 0;
		const char* pstr_Model = pDataElem->Attribute("Model");
		if(pstr_Model != NULL)
			pData->_Model = (UINT16)atoi(pstr_Model);
		else
			pData->_Model = 0;
		const char* pstr_BornFires = pDataElem->Attribute("BornFires");
		if(pstr_BornFires != NULL)
			pData->_BornFires = pstr_BornFires;
		else
			pData->_BornFires = "";
		const char* pstr_GetCondId = pDataElem->Attribute("GetCondId");
		if(pstr_GetCondId != NULL)
			pData->_GetCondId = (UINT16)atoi(pstr_GetCondId);
		else
			pData->_GetCondId = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


