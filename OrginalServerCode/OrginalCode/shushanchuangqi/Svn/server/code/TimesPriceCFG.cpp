// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STimesPriceCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TimesPriceCFG.h"
#include "tinyxml.h"

CTimesPriceLoader::~CTimesPriceLoader()
{
	ClearData();
}

void CTimesPriceLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STimesPriceCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTimesPriceLoader::LoadData(const std::string& strPath)
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
		STimesPriceCFG* pData = new STimesPriceCFG;
		const char* pstr_BoughtTimes = pDataElem->Attribute("BoughtTimes");
		if(pstr_BoughtTimes != NULL)
			pData->_BoughtTimes = (UINT32)atoi(pstr_BoughtTimes);
		else
			pData->_BoughtTimes = 0;
		const char* pstr_HeroDungeon = pDataElem->Attribute("HeroDungeon");
		if(pstr_HeroDungeon != NULL)
			pData->_HeroDungeon = (UINT32)atoi(pstr_HeroDungeon);
		else
			pData->_HeroDungeon = 0;
		const char* pstr_AdventureDungeon = pDataElem->Attribute("AdventureDungeon");
		if(pstr_AdventureDungeon != NULL)
			pData->_AdventureDungeon = (UINT32)atoi(pstr_AdventureDungeon);
		else
			pData->_AdventureDungeon = 0;
		const char* pstr_Arena = pDataElem->Attribute("Arena");
		if(pstr_Arena != NULL)
			pData->_Arena = (UINT32)atoi(pstr_Arena);
		else
			pData->_Arena = 0;
		const char* pstr_MoneyTree = pDataElem->Attribute("MoneyTree");
		if(pstr_MoneyTree != NULL)
			pData->_MoneyTree = (UINT32)atoi(pstr_MoneyTree);
		else
			pData->_MoneyTree = 0;
		const char* pstr_CtrlDice = pDataElem->Attribute("CtrlDice");
		if(pstr_CtrlDice != NULL)
			pData->_CtrlDice = (UINT16)atoi(pstr_CtrlDice);
		else
			pData->_CtrlDice = 0;
		const char* pstr_ComeBack = pDataElem->Attribute("ComeBack");
		if(pstr_ComeBack != NULL)
			pData->_ComeBack = (UINT16)atoi(pstr_ComeBack);
		else
			pData->_ComeBack = 0;
		const char* pstr_RichLife = pDataElem->Attribute("RichLife");
		if(pstr_RichLife != NULL)
			pData->_RichLife = (UINT16)atoi(pstr_RichLife);
		else
			pData->_RichLife = 0;
		const char* pstr_RichTimes = pDataElem->Attribute("RichTimes");
		if(pstr_RichTimes != NULL)
			pData->_RichTimes = (UINT16)atoi(pstr_RichTimes);
		else
			pData->_RichTimes = 0;
		const char* pstr_LilianTimes = pDataElem->Attribute("LilianTimes");
		if(pstr_LilianTimes != NULL)
			pData->_LilianTimes = (UINT16)atoi(pstr_LilianTimes);
		else
			pData->_LilianTimes = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


