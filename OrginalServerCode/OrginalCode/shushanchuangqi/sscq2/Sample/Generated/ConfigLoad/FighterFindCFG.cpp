// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterFindCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FighterFindCFG.h"
#include "tinyxml.h"

CFighterFindLoader::~CFighterFindLoader()
{
	ClearData();
}

void CFighterFindLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFighterFindCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFighterFindLoader::LoadData(const std::string& strPath)
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
		SFighterFindCFG* pData = new SFighterFindCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Scene = pDataElem->Attribute("Scene");
		if(pstr_Scene != NULL)
			pData->_Scene = (UINT8)atoi(pstr_Scene);
		else
			pData->_Scene = 0;
		const char* pstr_GoldRandom = pDataElem->Attribute("GoldRandom");
		if(pstr_GoldRandom != NULL)
			pData->_GoldRandom = (FLOAT)atof(pstr_GoldRandom);
		else
			pData->_GoldRandom = 0.0f;
		const char* pstr_CouponRandom = pDataElem->Attribute("CouponRandom");
		if(pstr_CouponRandom != NULL)
			pData->_CouponRandom = (FLOAT)atof(pstr_CouponRandom);
		else
			pData->_CouponRandom = 0.0f;
		const char* pstr_SilverRandom = pDataElem->Attribute("SilverRandom");
		if(pstr_SilverRandom != NULL)
			pData->_SilverRandom = (FLOAT)atof(pstr_SilverRandom);
		else
			pData->_SilverRandom = 0.0f;
		const char* pstr_FighterProp = pDataElem->Attribute("FighterProp");
		if(pstr_FighterProp != NULL)
			pData->_FighterProp = pstr_FighterProp;
		else
			pData->_FighterProp = "";
		const char* pstr_PriceItem = pDataElem->Attribute("PriceItem");
		if(pstr_PriceItem != NULL)
			pData->_PriceItem = pstr_PriceItem;
		else
			pData->_PriceItem = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


