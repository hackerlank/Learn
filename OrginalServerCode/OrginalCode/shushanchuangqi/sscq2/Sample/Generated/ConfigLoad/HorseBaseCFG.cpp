// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHorseBaseCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "HorseBaseCFG.h"
#include "tinyxml.h"

CHorseBaseLoader::~CHorseBaseLoader()
{
	ClearData();
}

void CHorseBaseLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SHorseBaseCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CHorseBaseLoader::LoadData(const std::string& strPath)
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
		SHorseBaseCFG* pData = new SHorseBaseCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_ModelName = pDataElem->Attribute("ModelName");
		if(pstr_ModelName != NULL)
			pData->_ModelName = pstr_ModelName;
		else
			pData->_ModelName = "";
		const char* pstr_Quality = pDataElem->Attribute("Quality");
		if(pstr_Quality != NULL)
			pData->_Quality = (UINT8)atoi(pstr_Quality);
		else
			pData->_Quality = 0;
		const char* pstr_ItemID = pDataElem->Attribute("ItemID");
		if(pstr_ItemID != NULL)
			pData->_ItemID = (UINT32)atoi(pstr_ItemID);
		else
			pData->_ItemID = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Speed = pDataElem->Attribute("Speed");
		if(pstr_Speed != NULL)
			pData->_Speed = (UINT32)atoi(pstr_Speed);
		else
			pData->_Speed = 0;
		const char* pstr_ModelID = pDataElem->Attribute("ModelID");
		if(pstr_ModelID != NULL)
			pData->_ModelID = (UINT32)atoi(pstr_ModelID);
		else
			pData->_ModelID = 0;
		const char* pstr_SkillAttrID1 = pDataElem->Attribute("SkillAttrID1");
		if(pstr_SkillAttrID1 != NULL)
			pData->_SkillAttrID1 = (UINT32)atoi(pstr_SkillAttrID1);
		else
			pData->_SkillAttrID1 = 0;
		const char* pstr_UnLockCond1 = pDataElem->Attribute("UnLockCond1");
		if(pstr_UnLockCond1 != NULL)
			pData->_UnLockCond1 = (UINT8)atoi(pstr_UnLockCond1);
		else
			pData->_UnLockCond1 = 0;
		const char* pstr_SkillAttrID2 = pDataElem->Attribute("SkillAttrID2");
		if(pstr_SkillAttrID2 != NULL)
			pData->_SkillAttrID2 = (UINT32)atoi(pstr_SkillAttrID2);
		else
			pData->_SkillAttrID2 = 0;
		const char* pstr_UnLockCond2 = pDataElem->Attribute("UnLockCond2");
		if(pstr_UnLockCond2 != NULL)
			pData->_UnLockCond2 = (UINT32)atoi(pstr_UnLockCond2);
		else
			pData->_UnLockCond2 = 0;
		const char* pstr_SkillAttrID3 = pDataElem->Attribute("SkillAttrID3");
		if(pstr_SkillAttrID3 != NULL)
			pData->_SkillAttrID3 = (UINT32)atoi(pstr_SkillAttrID3);
		else
			pData->_SkillAttrID3 = 0;
		const char* pstr_UnLockCond3 = pDataElem->Attribute("UnLockCond3");
		if(pstr_UnLockCond3 != NULL)
			pData->_UnLockCond3 = (UINT32)atoi(pstr_UnLockCond3);
		else
			pData->_UnLockCond3 = 0;
		const char* pstr_SkillAttrID4 = pDataElem->Attribute("SkillAttrID4");
		if(pstr_SkillAttrID4 != NULL)
			pData->_SkillAttrID4 = (UINT32)atoi(pstr_SkillAttrID4);
		else
			pData->_SkillAttrID4 = 0;
		const char* pstr_UnLockCond4 = pDataElem->Attribute("UnLockCond4");
		if(pstr_UnLockCond4 != NULL)
			pData->_UnLockCond4 = (UINT32)atoi(pstr_UnLockCond4);
		else
			pData->_UnLockCond4 = 0;
		const char* pstr_SkillAttrID5 = pDataElem->Attribute("SkillAttrID5");
		if(pstr_SkillAttrID5 != NULL)
			pData->_SkillAttrID5 = (UINT32)atoi(pstr_SkillAttrID5);
		else
			pData->_SkillAttrID5 = 0;
		const char* pstr_UnLockCond5 = pDataElem->Attribute("UnLockCond5");
		if(pstr_UnLockCond5 != NULL)
			pData->_UnLockCond5 = (UINT32)atoi(pstr_UnLockCond5);
		else
			pData->_UnLockCond5 = 0;
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


