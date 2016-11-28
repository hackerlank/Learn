// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDujieCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DujieCFG.h"
#include "tinyxml.h"

CDujieLoader::~CDujieLoader()
{
	ClearData();
}

void CDujieLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDujieCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDujieLoader::LoadData(const std::string& strPath)
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
		SDujieCFG* pData = new SDujieCFG;
		const char* pstr_FighterId = pDataElem->Attribute("FighterId");
		if(pstr_FighterId != NULL)
			pData->_FighterId = (UINT16)atoi(pstr_FighterId);
		else
			pData->_FighterId = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_PeriodName = pDataElem->Attribute("PeriodName");
		if(pstr_PeriodName != NULL)
			pData->_PeriodName = pstr_PeriodName;
		else
			pData->_PeriodName = "";
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Condition = pDataElem->Attribute("Condition");
		if(pstr_Condition != NULL)
			pData->_Condition = pstr_Condition;
		else
			pData->_Condition = "";
		const char* pstr_LootId = pDataElem->Attribute("LootId");
		if(pstr_LootId != NULL)
			pData->_LootId = (UINT32)atoi(pstr_LootId);
		else
			pData->_LootId = 0;
		const char* pstr_Dgn = pDataElem->Attribute("Dgn");
		if(pstr_Dgn != NULL)
			pData->_Dgn = (UINT16)atoi(pstr_Dgn);
		else
			pData->_Dgn = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_SkillColor = pDataElem->Attribute("SkillColor");
		if(pstr_SkillColor != NULL)
			pData->_SkillColor = pstr_SkillColor;
		else
			pData->_SkillColor = "";
		const char* pstr_MasterSkillColor = pDataElem->Attribute("MasterSkillColor");
		if(pstr_MasterSkillColor != NULL)
			pData->_MasterSkillColor = (UINT8)atoi(pstr_MasterSkillColor);
		else
			pData->_MasterSkillColor = 0;
		const char* pstr_UnlockSkill = pDataElem->Attribute("UnlockSkill");
		if(pstr_UnlockSkill != NULL)
			pData->_UnlockSkill = pstr_UnlockSkill;
		else
			pData->_UnlockSkill = "";
		const char* pstr_UnlockTalent = pDataElem->Attribute("UnlockTalent");
		if(pstr_UnlockTalent != NULL)
			pData->_UnlockTalent = pstr_UnlockTalent;
		else
			pData->_UnlockTalent = "";
		const char* pstr_GrowthRate = pDataElem->Attribute("GrowthRate");
		if(pstr_GrowthRate != NULL)
			pData->_GrowthRate = (FLOAT)atof(pstr_GrowthRate);
		else
			pData->_GrowthRate = 0.0f;
		const char* pstr_AwardYuanshen = pDataElem->Attribute("AwardYuanshen");
		if(pstr_AwardYuanshen != NULL)
			pData->_AwardYuanshen = (UINT8)atoi(pstr_AwardYuanshen);
		else
			pData->_AwardYuanshen = 0;
		const char* pstr_XinfaPos = pDataElem->Attribute("XinfaPos");
		if(pstr_XinfaPos != NULL)
			pData->_XinfaPos = pstr_XinfaPos;
		else
			pData->_XinfaPos = "";
		const char* pstr_EffectName = pDataElem->Attribute("EffectName");
		if(pstr_EffectName != NULL)
			pData->_EffectName = pstr_EffectName;
		else
			pData->_EffectName = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


