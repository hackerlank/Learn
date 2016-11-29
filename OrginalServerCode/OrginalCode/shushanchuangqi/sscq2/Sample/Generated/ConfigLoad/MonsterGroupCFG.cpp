// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMonsterGroupCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "MonsterGroupCFG.h"
#include "tinyxml.h"

CMonsterGroupLoader::~CMonsterGroupLoader()
{
	ClearData();
}

void CMonsterGroupLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SMonsterGroupCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CMonsterGroupLoader::LoadData(const std::string& strPath)
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
		SMonsterGroupCFG* pData = new SMonsterGroupCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_MainMonster = pDataElem->Attribute("MainMonster");
		if(pstr_MainMonster != NULL)
			pData->_MainMonster = (UINT16)atoi(pstr_MainMonster);
		else
			pData->_MainMonster = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_uQuality = pDataElem->Attribute("uQuality");
		if(pstr_uQuality != NULL)
			pData->_uQuality = (UINT8)atoi(pstr_uQuality);
		else
			pData->_uQuality = 0;
		const char* pstr_uType = pDataElem->Attribute("uType");
		if(pstr_uType != NULL)
			pData->_uType = (UINT8)atoi(pstr_uType);
		else
			pData->_uType = 0;
		const char* pstr_FightType = pDataElem->Attribute("FightType");
		if(pstr_FightType != NULL)
			pData->_FightType = (UINT8)atoi(pstr_FightType);
		else
			pData->_FightType = 0;
		const char* pstr_wLevel = pDataElem->Attribute("wLevel");
		if(pstr_wLevel != NULL)
			pData->_wLevel = (UINT16)atoi(pstr_wLevel);
		else
			pData->_wLevel = 0;
		const char* pstr_uExp = pDataElem->Attribute("uExp");
		if(pstr_uExp != NULL)
			pData->_uExp = (UINT32)atoi(pstr_uExp);
		else
			pData->_uExp = 0;
		const char* pstr_strDropID = pDataElem->Attribute("strDropID");
		if(pstr_strDropID != NULL)
			pData->_strDropID = pstr_strDropID;
		else
			pData->_strDropID = "";
		const char* pstr_strFighters = pDataElem->Attribute("strFighters");
		if(pstr_strFighters != NULL)
			pData->_strFighters = pstr_strFighters;
		else
			pData->_strFighters = "";
		const char* pstr_MonsterClass = pDataElem->Attribute("MonsterClass");
		if(pstr_MonsterClass != NULL)
			pData->_MonsterClass = pstr_MonsterClass;
		else
			pData->_MonsterClass = "";
		const char* pstr_addPet = pDataElem->Attribute("addPet");
		if(pstr_addPet != NULL)
			pData->_addPet = (UINT32)atoi(pstr_addPet);
		else
			pData->_addPet = 0;
		const char* pstr_addNPC = pDataElem->Attribute("addNPC");
		if(pstr_addNPC != NULL)
			pData->_addNPC = pstr_addNPC;
		else
			pData->_addNPC = "";
		const char* pstr_AddSkill = pDataElem->Attribute("AddSkill");
		if(pstr_AddSkill != NULL)
			pData->_AddSkill = pstr_AddSkill;
		else
			pData->_AddSkill = "";
		const char* pstr_AI = pDataElem->Attribute("AI");
		if(pstr_AI != NULL)
			pData->_AI = (UINT16)atoi(pstr_AI);
		else
			pData->_AI = 0;
		const char* pstr_Visual = pDataElem->Attribute("Visual");
		if(pstr_Visual != NULL)
			pData->_Visual = (UINT8)atoi(pstr_Visual);
		else
			pData->_Visual = 0;
		const char* pstr_dialog = pDataElem->Attribute("dialog");
		if(pstr_dialog != NULL)
			pData->_dialog = pstr_dialog;
		else
			pData->_dialog = "";
		const char* pstr_findDialog = pDataElem->Attribute("findDialog");
		if(pstr_findDialog != NULL)
			pData->_findDialog = pstr_findDialog;
		else
			pData->_findDialog = "";
		const char* pstr_FightMap = pDataElem->Attribute("FightMap");
		if(pstr_FightMap != NULL)
			pData->_FightMap = (UINT16)atoi(pstr_FightMap);
		else
			pData->_FightMap = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


