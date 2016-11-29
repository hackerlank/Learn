// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBattleArrayCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BattleArrayCFG.h"
#include "tinyxml.h"

CBattleArrayLoader::~CBattleArrayLoader()
{
	ClearData();
}

void CBattleArrayLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBattleArrayCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBattleArrayLoader::LoadData(const std::string& strPath)
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
		SBattleArrayCFG* pData = new SBattleArrayCFG;
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
		const char* pstr_Image = pDataElem->Attribute("Image");
		if(pstr_Image != NULL)
			pData->_Image = (UINT16)atoi(pstr_Image);
		else
			pData->_Image = 0;
		const char* pstr_NamePic = pDataElem->Attribute("NamePic");
		if(pstr_NamePic != NULL)
			pData->_NamePic = (UINT16)atoi(pstr_NamePic);
		else
			pData->_NamePic = 0;
		const char* pstr_MapId = pDataElem->Attribute("MapId");
		if(pstr_MapId != NULL)
			pData->_MapId = (UINT16)atoi(pstr_MapId);
		else
			pData->_MapId = 0;
		const char* pstr_RequiredLevel = pDataElem->Attribute("RequiredLevel");
		if(pstr_RequiredLevel != NULL)
			pData->_RequiredLevel = (UINT16)atoi(pstr_RequiredLevel);
		else
			pData->_RequiredLevel = 0;
		const char* pstr_PreID = pDataElem->Attribute("PreID");
		if(pstr_PreID != NULL)
			pData->_PreID = (UINT16)atoi(pstr_PreID);
		else
			pData->_PreID = 0;
		const char* pstr_PassPrize = pDataElem->Attribute("PassPrize");
		if(pstr_PassPrize != NULL)
			pData->_PassPrize = pstr_PassPrize;
		else
			pData->_PassPrize = "";
		const char* pstr_Des = pDataElem->Attribute("Des");
		if(pstr_Des != NULL)
			pData->_Des = pstr_Des;
		else
			pData->_Des = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


