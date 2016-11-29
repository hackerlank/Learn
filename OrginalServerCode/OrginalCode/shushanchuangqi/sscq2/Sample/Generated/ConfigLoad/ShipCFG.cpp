// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShipCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ShipCFG.h"
#include "tinyxml.h"

CShipLoader::~CShipLoader()
{
	ClearData();
}

void CShipLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SShipCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CShipLoader::LoadData(const std::string& strPath)
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
		SShipCFG* pData = new SShipCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT8)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_TypeID = pDataElem->Attribute("TypeID");
		if(pstr_TypeID != NULL)
			pData->_TypeID = (UINT8)atoi(pstr_TypeID);
		else
			pData->_TypeID = 0;
		const char* pstr_Number = pDataElem->Attribute("Number");
		if(pstr_Number != NULL)
			pData->_Number = (UINT16)atoi(pstr_Number);
		else
			pData->_Number = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_FreeChance = pDataElem->Attribute("FreeChance");
		if(pstr_FreeChance != NULL)
			pData->_FreeChance = (UINT16)atoi(pstr_FreeChance);
		else
			pData->_FreeChance = 0;
		const char* pstr_MoneyChance = pDataElem->Attribute("MoneyChance");
		if(pstr_MoneyChance != NULL)
			pData->_MoneyChance = (UINT16)atoi(pstr_MoneyChance);
		else
			pData->_MoneyChance = 0;
		const char* pstr_Time = pDataElem->Attribute("Time");
		if(pstr_Time != NULL)
			pData->_Time = (UINT16)atoi(pstr_Time);
		else
			pData->_Time = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = (UINT16)atoi(pstr_Award);
		else
			pData->_Award = 0;
		const char* pstr_Award1 = pDataElem->Attribute("Award1");
		if(pstr_Award1 != NULL)
			pData->_Award1 = (UINT16)atoi(pstr_Award1);
		else
			pData->_Award1 = 0;
		const char* pstr_Award2 = pDataElem->Attribute("Award2");
		if(pstr_Award2 != NULL)
			pData->_Award2 = (UINT16)atoi(pstr_Award2);
		else
			pData->_Award2 = 0;
		const char* pstr_Award3 = pDataElem->Attribute("Award3");
		if(pstr_Award3 != NULL)
			pData->_Award3 = (UINT16)atoi(pstr_Award3);
		else
			pData->_Award3 = 0;
		const char* pstr_ProtectAward = pDataElem->Attribute("ProtectAward");
		if(pstr_ProtectAward != NULL)
			pData->_ProtectAward = (UINT16)atoi(pstr_ProtectAward);
		else
			pData->_ProtectAward = 0;
		const char* pstr_RobAward = pDataElem->Attribute("RobAward");
		if(pstr_RobAward != NULL)
			pData->_RobAward = (UINT16)atoi(pstr_RobAward);
		else
			pData->_RobAward = 0;
		const char* pstr_Buff = pDataElem->Attribute("Buff");
		if(pstr_Buff != NULL)
			pData->_Buff = (UINT16)atoi(pstr_Buff);
		else
			pData->_Buff = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


