// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBuffCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BuffCFG.h"
#include "tinyxml.h"

CBuffLoader::~CBuffLoader()
{
	ClearData();
}

void CBuffLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBuffCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBuffLoader::LoadData(const std::string& strPath)
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
		SBuffCFG* pData = new SBuffCFG;
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
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		const char* pstr_DescTime = pDataElem->Attribute("DescTime");
		if(pstr_DescTime != NULL)
			pData->_DescTime = pstr_DescTime;
		else
			pData->_DescTime = "";
		const char* pstr_BattleType = pDataElem->Attribute("BattleType");
		if(pstr_BattleType != NULL)
			pData->_BattleType = (UINT8)atoi(pstr_BattleType);
		else
			pData->_BattleType = 0;
		const char* pstr_EffectType = pDataElem->Attribute("EffectType");
		if(pstr_EffectType != NULL)
			pData->_EffectType = (UINT8)atoi(pstr_EffectType);
		else
			pData->_EffectType = 0;
		const char* pstr_Param1 = pDataElem->Attribute("Param1");
		if(pstr_Param1 != NULL)
			pData->_Param1 = pstr_Param1;
		else
			pData->_Param1 = "";
		const char* pstr_UseTime = pDataElem->Attribute("UseTime");
		if(pstr_UseTime != NULL)
			pData->_UseTime = (UINT32)atoi(pstr_UseTime);
		else
			pData->_UseTime = 0;
		const char* pstr_Time = pDataElem->Attribute("Time");
		if(pstr_Time != NULL)
			pData->_Time = (UINT32)atoi(pstr_Time);
		else
			pData->_Time = 0;
		const char* pstr_TotalTime = pDataElem->Attribute("TotalTime");
		if(pstr_TotalTime != NULL)
			pData->_TotalTime = (UINT32)atoi(pstr_TotalTime);
		else
			pData->_TotalTime = 0;
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = pstr_Icon;
		else
			pData->_Icon = "";
		const char* pstr_MapID = pDataElem->Attribute("MapID");
		if(pstr_MapID != NULL)
			pData->_MapID = pstr_MapID;
		else
			pData->_MapID = "";
		const char* pstr_Show = pDataElem->Attribute("Show");
		if(pstr_Show != NULL)
			pData->_Show = (UINT8)atoi(pstr_Show);
		else
			pData->_Show = 0;
		const char* pstr_IsSame = pDataElem->Attribute("IsSame");
		if(pstr_IsSame != NULL)
			pData->_IsSame = pstr_IsSame;
		else
			pData->_IsSame = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


