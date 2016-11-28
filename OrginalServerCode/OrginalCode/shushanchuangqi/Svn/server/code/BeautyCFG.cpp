// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BeautyCFG.h"
#include "tinyxml.h"

CBeautyLoader::~CBeautyLoader()
{
	ClearData();
}

void CBeautyLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBeautyCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBeautyLoader::LoadData(const std::string& strPath)
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
		SBeautyCFG* pData = new SBeautyCFG;
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
		const char* pstr_CondID = pDataElem->Attribute("CondID");
		if(pstr_CondID != NULL)
			pData->_CondID = (UINT32)atoi(pstr_CondID);
		else
			pData->_CondID = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_NPCID = pDataElem->Attribute("NPCID");
		if(pstr_NPCID != NULL)
			pData->_NPCID = (UINT32)atoi(pstr_NPCID);
		else
			pData->_NPCID = 0;
		const char* pstr_Model2D = pDataElem->Attribute("Model2D");
		if(pstr_Model2D != NULL)
			pData->_Model2D = (UINT8)atoi(pstr_Model2D);
		else
			pData->_Model2D = 0;
		const char* pstr_AppearLevel = pDataElem->Attribute("AppearLevel");
		if(pstr_AppearLevel != NULL)
			pData->_AppearLevel = (UINT8)atoi(pstr_AppearLevel);
		else
			pData->_AppearLevel = 0;
		const char* pstr_EffectAppear = pDataElem->Attribute("EffectAppear");
		if(pstr_EffectAppear != NULL)
			pData->_EffectAppear = pstr_EffectAppear;
		else
			pData->_EffectAppear = "";
		const char* pstr_EffectDisappear = pDataElem->Attribute("EffectDisappear");
		if(pstr_EffectDisappear != NULL)
			pData->_EffectDisappear = pstr_EffectDisappear;
		else
			pData->_EffectDisappear = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


