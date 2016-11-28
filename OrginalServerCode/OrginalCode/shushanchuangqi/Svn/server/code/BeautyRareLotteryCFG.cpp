// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyRareLotteryCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "BeautyRareLotteryCFG.h"
#include "tinyxml.h"

CBeautyRareLotteryLoader::~CBeautyRareLotteryLoader()
{
	ClearData();
}

void CBeautyRareLotteryLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SBeautyRareLotteryCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CBeautyRareLotteryLoader::LoadData(const std::string& strPath)
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
		SBeautyRareLotteryCFG* pData = new SBeautyRareLotteryCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Loots = pDataElem->Attribute("Loots");
		if(pstr_Loots != NULL)
			pData->_Loots = (UINT16)atoi(pstr_Loots);
		else
			pData->_Loots = 0;
		const char* pstr_Rare = pDataElem->Attribute("Rare");
		if(pstr_Rare != NULL)
			pData->_Rare = (UINT8)atoi(pstr_Rare);
		else
			pData->_Rare = 0;
		const char* pstr_ItemID = pDataElem->Attribute("ItemID");
		if(pstr_ItemID != NULL)
			pData->_ItemID = (UINT32)atoi(pstr_ItemID);
		else
			pData->_ItemID = 0;
		const char* pstr_ItemCount = pDataElem->Attribute("ItemCount");
		if(pstr_ItemCount != NULL)
			pData->_ItemCount = (UINT32)atoi(pstr_ItemCount);
		else
			pData->_ItemCount = 0;
		const char* pstr_Probablity = pDataElem->Attribute("Probablity");
		if(pstr_Probablity != NULL)
			pData->_Probablity = (UINT32)atoi(pstr_Probablity);
		else
			pData->_Probablity = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


