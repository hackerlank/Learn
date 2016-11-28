// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ItemCFG.h"
#include "tinyxml.h"

CItemLoader::~CItemLoader()
{
	ClearData();
}

void CItemLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SItemCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CItemLoader::LoadData(const std::string& strPath)
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
		SItemCFG* pData = new SItemCFG;
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
			pData->_Type = (UINT16)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_LevelValue = pDataElem->Attribute("LevelValue");
		if(pstr_LevelValue != NULL)
			pData->_LevelValue = (UINT8)atoi(pstr_LevelValue);
		else
			pData->_LevelValue = 0;
		const char* pstr_Cond = pDataElem->Attribute("Cond");
		if(pstr_Cond != NULL)
			pData->_Cond = (UINT16)atoi(pstr_Cond);
		else
			pData->_Cond = 0;
		const char* pstr_Quality = pDataElem->Attribute("Quality");
		if(pstr_Quality != NULL)
			pData->_Quality = (UINT8)atoi(pstr_Quality);
		else
			pData->_Quality = 0;
		const char* pstr_Stack = pDataElem->Attribute("Stack");
		if(pstr_Stack != NULL)
			pData->_Stack = (UINT16)atoi(pstr_Stack);
		else
			pData->_Stack = 0;
		const char* pstr_Job = pDataElem->Attribute("Job");
		if(pstr_Job != NULL)
			pData->_Job = (UINT8)atoi(pstr_Job);
		else
			pData->_Job = 0;
		const char* pstr_Useable = pDataElem->Attribute("Useable");
		if(pstr_Useable != NULL)
			pData->_Useable = (UINT8)atoi(pstr_Useable);
		else
			pData->_Useable = 0;
		const char* pstr_UseableOpen = pDataElem->Attribute("UseableOpen");
		if(pstr_UseableOpen != NULL)
			pData->_UseableOpen = (UINT16)atoi(pstr_UseableOpen);
		else
			pData->_UseableOpen = 0;
		const char* pstr_UpgradeAble = pDataElem->Attribute("UpgradeAble");
		if(pstr_UpgradeAble != NULL)
			pData->_UpgradeAble = (UINT8)atoi(pstr_UpgradeAble);
		else
			pData->_UpgradeAble = 0;
		const char* pstr_UpgradeAbleOpen = pDataElem->Attribute("UpgradeAbleOpen");
		if(pstr_UpgradeAbleOpen != NULL)
			pData->_UpgradeAbleOpen = (UINT16)atoi(pstr_UpgradeAbleOpen);
		else
			pData->_UpgradeAbleOpen = 0;
		const char* pstr_Push = pDataElem->Attribute("Push");
		if(pstr_Push != NULL)
			pData->_Push = (UINT8)atoi(pstr_Push);
		else
			pData->_Push = 0;
		const char* pstr_SellPrice = pDataElem->Attribute("SellPrice");
		if(pstr_SellPrice != NULL)
			pData->_SellPrice = (UINT32)atoi(pstr_SellPrice);
		else
			pData->_SellPrice = 0;
		const char* pstr_ExchangePrice = pDataElem->Attribute("ExchangePrice");
		if(pstr_ExchangePrice != NULL)
			pData->_ExchangePrice = (UINT32)atoi(pstr_ExchangePrice);
		else
			pData->_ExchangePrice = 0;
		const char* pstr_Saleup = pDataElem->Attribute("Saleup");
		if(pstr_Saleup != NULL)
			pData->_Saleup = (UINT16)atoi(pstr_Saleup);
		else
			pData->_Saleup = 0;
		const char* pstr_Binding = pDataElem->Attribute("Binding");
		if(pstr_Binding != NULL)
			pData->_Binding = (UINT8)atoi(pstr_Binding);
		else
			pData->_Binding = 0;
		const char* pstr_AttrIdx_1 = pDataElem->Attribute("AttrIdx_1");
		if(pstr_AttrIdx_1 != NULL)
			pData->_AttrIdx_1 = (UINT16)atoi(pstr_AttrIdx_1);
		else
			pData->_AttrIdx_1 = 0;
		const char* pstr_AttrIdx_2 = pDataElem->Attribute("AttrIdx_2");
		if(pstr_AttrIdx_2 != NULL)
			pData->_AttrIdx_2 = (UINT16)atoi(pstr_AttrIdx_2);
		else
			pData->_AttrIdx_2 = 0;
		const char* pstr_AttrIdx_3 = pDataElem->Attribute("AttrIdx_3");
		if(pstr_AttrIdx_3 != NULL)
			pData->_AttrIdx_3 = (UINT16)atoi(pstr_AttrIdx_3);
		else
			pData->_AttrIdx_3 = 0;
		const char* pstr_Energy = pDataElem->Attribute("Energy");
		if(pstr_Energy != NULL)
			pData->_Energy = (UINT16)atoi(pstr_Energy);
		else
			pData->_Energy = 0;
		const char* pstr_TrumpExp = pDataElem->Attribute("TrumpExp");
		if(pstr_TrumpExp != NULL)
			pData->_TrumpExp = (UINT16)atoi(pstr_TrumpExp);
		else
			pData->_TrumpExp = 0;
		const char* pstr_Goodwill = pDataElem->Attribute("Goodwill");
		if(pstr_Goodwill != NULL)
			pData->_Goodwill = (UINT16)atoi(pstr_Goodwill);
		else
			pData->_Goodwill = 0;
		const char* pstr_QuestData = pDataElem->Attribute("QuestData");
		if(pstr_QuestData != NULL)
			pData->_QuestData = (UINT16)atoi(pstr_QuestData);
		else
			pData->_QuestData = 0;
		const char* pstr_GuiDgn = pDataElem->Attribute("GuiDgn");
		if(pstr_GuiDgn != NULL)
			pData->_GuiDgn = (UINT16)atoi(pstr_GuiDgn);
		else
			pData->_GuiDgn = 0;
		const char* pstr_Enchant = pDataElem->Attribute("Enchant");
		if(pstr_Enchant != NULL)
			pData->_Enchant = (UINT16)atoi(pstr_Enchant);
		else
			pData->_Enchant = 0;
		const char* pstr_ItemTimeID = pDataElem->Attribute("ItemTimeID");
		if(pstr_ItemTimeID != NULL)
			pData->_ItemTimeID = (UINT16)atoi(pstr_ItemTimeID);
		else
			pData->_ItemTimeID = 0;
		const char* pstr_Model = pDataElem->Attribute("Model");
		if(pstr_Model != NULL)
			pData->_Model = (UINT16)atoi(pstr_Model);
		else
			pData->_Model = 0;
		const char* pstr_UseTimes = pDataElem->Attribute("UseTimes");
		if(pstr_UseTimes != NULL)
			pData->_UseTimes = (UINT8)atoi(pstr_UseTimes);
		else
			pData->_UseTimes = 0;
		const char* pstr_StoneLevel = pDataElem->Attribute("StoneLevel");
		if(pstr_StoneLevel != NULL)
			pData->_StoneLevel = (UINT8)atoi(pstr_StoneLevel);
		else
			pData->_StoneLevel = 0;
		const char* pstr_RequiredPackSpace = pDataElem->Attribute("RequiredPackSpace");
		if(pstr_RequiredPackSpace != NULL)
			pData->_RequiredPackSpace = (UINT8)atoi(pstr_RequiredPackSpace);
		else
			pData->_RequiredPackSpace = 0;
		const char* pstr_RequiredPackTypeNum = pDataElem->Attribute("RequiredPackTypeNum");
		if(pstr_RequiredPackTypeNum != NULL)
			pData->_RequiredPackTypeNum = (UINT8)atoi(pstr_RequiredPackTypeNum);
		else
			pData->_RequiredPackTypeNum = 0;
		const char* pstr_EquipConflict = pDataElem->Attribute("EquipConflict");
		if(pstr_EquipConflict != NULL)
			pData->_EquipConflict = pstr_EquipConflict;
		else
			pData->_EquipConflict = "";
		const char* pstr_EquipConflictTeam = pDataElem->Attribute("EquipConflictTeam");
		if(pstr_EquipConflictTeam != NULL)
			pData->_EquipConflictTeam = pstr_EquipConflictTeam;
		else
			pData->_EquipConflictTeam = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


