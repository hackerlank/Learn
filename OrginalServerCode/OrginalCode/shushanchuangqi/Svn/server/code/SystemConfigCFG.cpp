// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSystemConfigCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SystemConfigCFG.h"
#include "tinyxml.h"

CSystemConfigLoader::~CSystemConfigLoader()
{
	ClearData();
}

void CSystemConfigLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSystemConfigCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSystemConfigLoader::LoadData(const std::string& strPath)
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
		SSystemConfigCFG* pData = new SSystemConfigCFG;
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
		const char* pstr_Config = pDataElem->Attribute("Config");
		if(pstr_Config != NULL)
			pData->_Config = (UINT16)atoi(pstr_Config);
		else
			pData->_Config = 0;
		const char* pstr_Block = pDataElem->Attribute("Block");
		if(pstr_Block != NULL)
			pData->_Block = (UINT8)atoi(pstr_Block);
		else
			pData->_Block = 0;
		const char* pstr_PreviewICON = pDataElem->Attribute("PreviewICON");
		if(pstr_PreviewICON != NULL)
			pData->_PreviewICON = (UINT32)atoi(pstr_PreviewICON);
		else
			pData->_PreviewICON = 0;
		const char* pstr_PreviewLv = pDataElem->Attribute("PreviewLv");
		if(pstr_PreviewLv != NULL)
			pData->_PreviewLv = (UINT16)atoi(pstr_PreviewLv);
		else
			pData->_PreviewLv = 0;
		const char* pstr_PreviewDes = pDataElem->Attribute("PreviewDes");
		if(pstr_PreviewDes != NULL)
			pData->_PreviewDes = pstr_PreviewDes;
		else
			pData->_PreviewDes = "";
		const char* pstr_PreviewBlock = pDataElem->Attribute("PreviewBlock");
		if(pstr_PreviewBlock != NULL)
			pData->_PreviewBlock = (UINT8)atoi(pstr_PreviewBlock);
		else
			pData->_PreviewBlock = 0;
		const char* pstr_MainButton = pDataElem->Attribute("MainButton");
		if(pstr_MainButton != NULL)
			pData->_MainButton = (UINT16)atoi(pstr_MainButton);
		else
			pData->_MainButton = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


