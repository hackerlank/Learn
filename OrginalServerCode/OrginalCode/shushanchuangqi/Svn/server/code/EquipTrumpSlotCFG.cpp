// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEquipTrumpSlotCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "EquipTrumpSlotCFG.h"
#include "tinyxml.h"

CEquipTrumpSlotLoader::~CEquipTrumpSlotLoader()
{
	ClearData();
}

void CEquipTrumpSlotLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SEquipTrumpSlotCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CEquipTrumpSlotLoader::LoadData(const std::string& strPath)
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
		SEquipTrumpSlotCFG* pData = new SEquipTrumpSlotCFG;
		const char* pstr_SlotId = pDataElem->Attribute("SlotId");
		if(pstr_SlotId != NULL)
			pData->_SlotId = (UINT8)atoi(pstr_SlotId);
		else
			pData->_SlotId = 0;
		const char* pstr_EquipTrumpType = pDataElem->Attribute("EquipTrumpType");
		if(pstr_EquipTrumpType != NULL)
			pData->_EquipTrumpType = (UINT8)atoi(pstr_EquipTrumpType);
		else
			pData->_EquipTrumpType = 0;
		const char* pstr_UnlockDujieLevel = pDataElem->Attribute("UnlockDujieLevel");
		if(pstr_UnlockDujieLevel != NULL)
			pData->_UnlockDujieLevel = (UINT16)atoi(pstr_UnlockDujieLevel);
		else
			pData->_UnlockDujieLevel = 0;
		const char* pstr_Lock = pDataElem->Attribute("Lock");
		if(pstr_Lock != NULL)
			pData->_Lock = (UINT8)atoi(pstr_Lock);
		else
			pData->_Lock = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


