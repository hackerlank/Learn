﻿// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STaskDropCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TaskDropCFG.h"
#include "tinyxml.h"

CTaskDropLoader::~CTaskDropLoader()
{
	ClearData();
}

void CTaskDropLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STaskDropCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTaskDropLoader::LoadData(const std::string& strPath)
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
		STaskDropCFG* pData = new STaskDropCFG;
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
		const char* pstr_TaskID = pDataElem->Attribute("TaskID");
		if(pstr_TaskID != NULL)
			pData->_TaskID = (UINT16)atoi(pstr_TaskID);
		else
			pData->_TaskID = 0;
		const char* pstr_ItemID = pDataElem->Attribute("ItemID");
		if(pstr_ItemID != NULL)
			pData->_ItemID = (UINT16)atoi(pstr_ItemID);
		else
			pData->_ItemID = 0;
		const char* pstr_ItemName = pDataElem->Attribute("ItemName");
		if(pstr_ItemName != NULL)
			pData->_ItemName = pstr_ItemName;
		else
			pData->_ItemName = "";
		const char* pstr_DropRate = pDataElem->Attribute("DropRate");
		if(pstr_DropRate != NULL)
			pData->_DropRate = (UINT16)atoi(pstr_DropRate);
		else
			pData->_DropRate = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


