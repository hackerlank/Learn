// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyLotteryCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BeautyLotteryCFG.h"
#include "tinyxml.h"

CBeautyLotteryLoader::~CBeautyLotteryLoader()
{
	ClearData();
}

void CBeautyLotteryLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBeautyLotteryCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBeautyLotteryLoader::LoadData(const std::string& strPath)
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
		SBeautyLotteryCFG* pData = new SBeautyLotteryCFG;
		const char* pstr_PrizeType = pDataElem->Attribute("PrizeType");
		if(pstr_PrizeType != NULL)
			pData->_PrizeType = (UINT16)atoi(pstr_PrizeType);
		else
			pData->_PrizeType = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT32)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		const char* pstr_DropID = pDataElem->Attribute("DropID");
		if(pstr_DropID != NULL)
			pData->_DropID = (UINT16)atoi(pstr_DropID);
		else
			pData->_DropID = 0;
		const char* pstr_RandomDropID = pDataElem->Attribute("RandomDropID");
		if(pstr_RandomDropID != NULL)
			pData->_RandomDropID = (UINT16)atoi(pstr_RandomDropID);
		else
			pData->_RandomDropID = 0;
		const char* pstr_Count = pDataElem->Attribute("Count");
		if(pstr_Count != NULL)
			pData->_Count = (UINT32)atoi(pstr_Count);
		else
			pData->_Count = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


