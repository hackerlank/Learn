// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STreasureToolsCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TreasureToolsCFG.h"
#include "tinyxml.h"

CTreasureToolsLoader::~CTreasureToolsLoader()
{
	ClearData();
}

void CTreasureToolsLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STreasureToolsCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTreasureToolsLoader::LoadData(const std::string& strPath)
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
		STreasureToolsCFG* pData = new STreasureToolsCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT16)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Location = pDataElem->Attribute("Location");
		if(pstr_Location != NULL)
			pData->_Location = (UINT16)atoi(pstr_Location);
		else
			pData->_Location = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Icon = pDataElem->Attribute("Icon");
		if(pstr_Icon != NULL)
			pData->_Icon = pstr_Icon;
		else
			pData->_Icon = "";
		const char* pstr_EntryNum = pDataElem->Attribute("EntryNum");
		if(pstr_EntryNum != NULL)
			pData->_EntryNum = (UINT8)atoi(pstr_EntryNum);
		else
			pData->_EntryNum = 0;
		const char* pstr_EFIGHTATTR_PHYATK = pDataElem->Attribute("EFIGHTATTR_PHYATK");
		if(pstr_EFIGHTATTR_PHYATK != NULL)
			pData->_EFIGHTATTR_PHYATK = (FLOAT)atof(pstr_EFIGHTATTR_PHYATK);
		else
			pData->_EFIGHTATTR_PHYATK = 0.0f;
		const char* pstr_EFIGHTATTR_MGCATK = pDataElem->Attribute("EFIGHTATTR_MGCATK");
		if(pstr_EFIGHTATTR_MGCATK != NULL)
			pData->_EFIGHTATTR_MGCATK = (FLOAT)atof(pstr_EFIGHTATTR_MGCATK);
		else
			pData->_EFIGHTATTR_MGCATK = 0.0f;
		const char* pstr_EFIGHTATTR_PHYDEF = pDataElem->Attribute("EFIGHTATTR_PHYDEF");
		if(pstr_EFIGHTATTR_PHYDEF != NULL)
			pData->_EFIGHTATTR_PHYDEF = (FLOAT)atof(pstr_EFIGHTATTR_PHYDEF);
		else
			pData->_EFIGHTATTR_PHYDEF = 0.0f;
		const char* pstr_EFIGHTATTR_MGCDEF = pDataElem->Attribute("EFIGHTATTR_MGCDEF");
		if(pstr_EFIGHTATTR_MGCDEF != NULL)
			pData->_EFIGHTATTR_MGCDEF = (FLOAT)atof(pstr_EFIGHTATTR_MGCDEF);
		else
			pData->_EFIGHTATTR_MGCDEF = 0.0f;
		const char* pstr_EFIGHTATTR_PHYRDC = pDataElem->Attribute("EFIGHTATTR_PHYRDC");
		if(pstr_EFIGHTATTR_PHYRDC != NULL)
			pData->_EFIGHTATTR_PHYRDC = (FLOAT)atof(pstr_EFIGHTATTR_PHYRDC);
		else
			pData->_EFIGHTATTR_PHYRDC = 0.0f;
		const char* pstr_EFIGHTATTR_MGCRDC = pDataElem->Attribute("EFIGHTATTR_MGCRDC");
		if(pstr_EFIGHTATTR_MGCRDC != NULL)
			pData->_EFIGHTATTR_MGCRDC = (FLOAT)atof(pstr_EFIGHTATTR_MGCRDC);
		else
			pData->_EFIGHTATTR_MGCRDC = 0.0f;
		const char* pstr_EFIGHTATTR_MAXHP = pDataElem->Attribute("EFIGHTATTR_MAXHP");
		if(pstr_EFIGHTATTR_MAXHP != NULL)
			pData->_EFIGHTATTR_MAXHP = (UINT32)atoi(pstr_EFIGHTATTR_MAXHP);
		else
			pData->_EFIGHTATTR_MAXHP = 0;
		const char* pstr_EFIGHTATTR_SPEED = pDataElem->Attribute("EFIGHTATTR_SPEED");
		if(pstr_EFIGHTATTR_SPEED != NULL)
			pData->_EFIGHTATTR_SPEED = (FLOAT)atof(pstr_EFIGHTATTR_SPEED);
		else
			pData->_EFIGHTATTR_SPEED = 0.0f;
		const char* pstr_EFIGHTATTR_HIT = pDataElem->Attribute("EFIGHTATTR_HIT");
		if(pstr_EFIGHTATTR_HIT != NULL)
			pData->_EFIGHTATTR_HIT = (FLOAT)atof(pstr_EFIGHTATTR_HIT);
		else
			pData->_EFIGHTATTR_HIT = 0.0f;
		const char* pstr_EFIGHTATTR_HITRATE = pDataElem->Attribute("EFIGHTATTR_HITRATE");
		if(pstr_EFIGHTATTR_HITRATE != NULL)
			pData->_EFIGHTATTR_HITRATE = (FLOAT)atof(pstr_EFIGHTATTR_HITRATE);
		else
			pData->_EFIGHTATTR_HITRATE = 0.0f;
		const char* pstr_EFIGHTATTR_DODGE = pDataElem->Attribute("EFIGHTATTR_DODGE");
		if(pstr_EFIGHTATTR_DODGE != NULL)
			pData->_EFIGHTATTR_DODGE = (FLOAT)atof(pstr_EFIGHTATTR_DODGE);
		else
			pData->_EFIGHTATTR_DODGE = 0.0f;
		const char* pstr_EFIGHTATTR_DODGERATE = pDataElem->Attribute("EFIGHTATTR_DODGERATE");
		if(pstr_EFIGHTATTR_DODGERATE != NULL)
			pData->_EFIGHTATTR_DODGERATE = (FLOAT)atof(pstr_EFIGHTATTR_DODGERATE);
		else
			pData->_EFIGHTATTR_DODGERATE = 0.0f;
		const char* pstr_EFIGHTATTR_CRITICAL = pDataElem->Attribute("EFIGHTATTR_CRITICAL");
		if(pstr_EFIGHTATTR_CRITICAL != NULL)
			pData->_EFIGHTATTR_CRITICAL = (FLOAT)atof(pstr_EFIGHTATTR_CRITICAL);
		else
			pData->_EFIGHTATTR_CRITICAL = 0.0f;
		const char* pstr_EFIGHTATTR_CRTRATE = pDataElem->Attribute("EFIGHTATTR_CRTRATE");
		if(pstr_EFIGHTATTR_CRTRATE != NULL)
			pData->_EFIGHTATTR_CRTRATE = (FLOAT)atof(pstr_EFIGHTATTR_CRTRATE);
		else
			pData->_EFIGHTATTR_CRTRATE = 0.0f;
		const char* pstr_EFIGHTATTR_ANTICRITCAL = pDataElem->Attribute("EFIGHTATTR_ANTICRITCAL");
		if(pstr_EFIGHTATTR_ANTICRITCAL != NULL)
			pData->_EFIGHTATTR_ANTICRITCAL = (FLOAT)atof(pstr_EFIGHTATTR_ANTICRITCAL);
		else
			pData->_EFIGHTATTR_ANTICRITCAL = 0.0f;
		const char* pstr_EFIGHTATTR_ANTICRTRATE = pDataElem->Attribute("EFIGHTATTR_ANTICRTRATE");
		if(pstr_EFIGHTATTR_ANTICRTRATE != NULL)
			pData->_EFIGHTATTR_ANTICRTRATE = (FLOAT)atof(pstr_EFIGHTATTR_ANTICRTRATE);
		else
			pData->_EFIGHTATTR_ANTICRTRATE = 0.0f;
		const char* pstr_EFIGHTATTR_BLOCK = pDataElem->Attribute("EFIGHTATTR_BLOCK");
		if(pstr_EFIGHTATTR_BLOCK != NULL)
			pData->_EFIGHTATTR_BLOCK = (FLOAT)atof(pstr_EFIGHTATTR_BLOCK);
		else
			pData->_EFIGHTATTR_BLOCK = 0.0f;
		const char* pstr_EFIGHTATTR_BLOCKRATE = pDataElem->Attribute("EFIGHTATTR_BLOCKRATE");
		if(pstr_EFIGHTATTR_BLOCKRATE != NULL)
			pData->_EFIGHTATTR_BLOCKRATE = (FLOAT)atof(pstr_EFIGHTATTR_BLOCKRATE);
		else
			pData->_EFIGHTATTR_BLOCKRATE = 0.0f;
		const char* pstr_EFIGHTATTR_PIERCE = pDataElem->Attribute("EFIGHTATTR_PIERCE");
		if(pstr_EFIGHTATTR_PIERCE != NULL)
			pData->_EFIGHTATTR_PIERCE = (FLOAT)atof(pstr_EFIGHTATTR_PIERCE);
		else
			pData->_EFIGHTATTR_PIERCE = 0.0f;
		const char* pstr_EFIGHTATTR_PIERCERATE = pDataElem->Attribute("EFIGHTATTR_PIERCERATE");
		if(pstr_EFIGHTATTR_PIERCERATE != NULL)
			pData->_EFIGHTATTR_PIERCERATE = (FLOAT)atof(pstr_EFIGHTATTR_PIERCERATE);
		else
			pData->_EFIGHTATTR_PIERCERATE = 0.0f;
		const char* pstr_EFIGHTATTR_COUNTER = pDataElem->Attribute("EFIGHTATTR_COUNTER");
		if(pstr_EFIGHTATTR_COUNTER != NULL)
			pData->_EFIGHTATTR_COUNTER = (FLOAT)atof(pstr_EFIGHTATTR_COUNTER);
		else
			pData->_EFIGHTATTR_COUNTER = 0.0f;
		const char* pstr_EFIGHTATTR_PHYATKChance = pDataElem->Attribute("EFIGHTATTR_PHYATKChance");
		if(pstr_EFIGHTATTR_PHYATKChance != NULL)
			pData->_EFIGHTATTR_PHYATKChance = (FLOAT)atof(pstr_EFIGHTATTR_PHYATKChance);
		else
			pData->_EFIGHTATTR_PHYATKChance = 0.0f;
		const char* pstr_EFIGHTATTR_MGCATKChance = pDataElem->Attribute("EFIGHTATTR_MGCATKChance");
		if(pstr_EFIGHTATTR_MGCATKChance != NULL)
			pData->_EFIGHTATTR_MGCATKChance = (FLOAT)atof(pstr_EFIGHTATTR_MGCATKChance);
		else
			pData->_EFIGHTATTR_MGCATKChance = 0.0f;
		const char* pstr_EFIGHTATTR_PHYDEFChance = pDataElem->Attribute("EFIGHTATTR_PHYDEFChance");
		if(pstr_EFIGHTATTR_PHYDEFChance != NULL)
			pData->_EFIGHTATTR_PHYDEFChance = (FLOAT)atof(pstr_EFIGHTATTR_PHYDEFChance);
		else
			pData->_EFIGHTATTR_PHYDEFChance = 0.0f;
		const char* pstr_EFIGHTATTR_MGCDEFChance = pDataElem->Attribute("EFIGHTATTR_MGCDEFChance");
		if(pstr_EFIGHTATTR_MGCDEFChance != NULL)
			pData->_EFIGHTATTR_MGCDEFChance = (FLOAT)atof(pstr_EFIGHTATTR_MGCDEFChance);
		else
			pData->_EFIGHTATTR_MGCDEFChance = 0.0f;
		const char* pstr_EFIGHTATTR_MAXHPChance = pDataElem->Attribute("EFIGHTATTR_MAXHPChance");
		if(pstr_EFIGHTATTR_MAXHPChance != NULL)
			pData->_EFIGHTATTR_MAXHPChance = (UINT32)atoi(pstr_EFIGHTATTR_MAXHPChance);
		else
			pData->_EFIGHTATTR_MAXHPChance = 0;
		const char* pstr_EFIGHTATTR_SPEEDChance = pDataElem->Attribute("EFIGHTATTR_SPEEDChance");
		if(pstr_EFIGHTATTR_SPEEDChance != NULL)
			pData->_EFIGHTATTR_SPEEDChance = (FLOAT)atof(pstr_EFIGHTATTR_SPEEDChance);
		else
			pData->_EFIGHTATTR_SPEEDChance = 0.0f;
		const char* pstr_EFIGHTATTR_HITChance = pDataElem->Attribute("EFIGHTATTR_HITChance");
		if(pstr_EFIGHTATTR_HITChance != NULL)
			pData->_EFIGHTATTR_HITChance = (FLOAT)atof(pstr_EFIGHTATTR_HITChance);
		else
			pData->_EFIGHTATTR_HITChance = 0.0f;
		const char* pstr_EFIGHTATTR_DODGEChance = pDataElem->Attribute("EFIGHTATTR_DODGEChance");
		if(pstr_EFIGHTATTR_DODGEChance != NULL)
			pData->_EFIGHTATTR_DODGEChance = (FLOAT)atof(pstr_EFIGHTATTR_DODGEChance);
		else
			pData->_EFIGHTATTR_DODGEChance = 0.0f;
		const char* pstr_EFIGHTATTR_CRITICALChance = pDataElem->Attribute("EFIGHTATTR_CRITICALChance");
		if(pstr_EFIGHTATTR_CRITICALChance != NULL)
			pData->_EFIGHTATTR_CRITICALChance = (FLOAT)atof(pstr_EFIGHTATTR_CRITICALChance);
		else
			pData->_EFIGHTATTR_CRITICALChance = 0.0f;
		const char* pstr_EFIGHTATTR_COUNTERChance = pDataElem->Attribute("EFIGHTATTR_COUNTERChance");
		if(pstr_EFIGHTATTR_COUNTERChance != NULL)
			pData->_EFIGHTATTR_COUNTERChance = (FLOAT)atof(pstr_EFIGHTATTR_COUNTERChance);
		else
			pData->_EFIGHTATTR_COUNTERChance = 0.0f;
		const char* pstr_AttackName = pDataElem->Attribute("AttackName");
		if(pstr_AttackName != NULL)
			pData->_AttackName = pstr_AttackName;
		else
			pData->_AttackName = "";
		const char* pstr_PhyDefName = pDataElem->Attribute("PhyDefName");
		if(pstr_PhyDefName != NULL)
			pData->_PhyDefName = pstr_PhyDefName;
		else
			pData->_PhyDefName = "";
		const char* pstr_MagicDefName = pDataElem->Attribute("MagicDefName");
		if(pstr_MagicDefName != NULL)
			pData->_MagicDefName = pstr_MagicDefName;
		else
			pData->_MagicDefName = "";
		const char* pstr_SpeedName = pDataElem->Attribute("SpeedName");
		if(pstr_SpeedName != NULL)
			pData->_SpeedName = pstr_SpeedName;
		else
			pData->_SpeedName = "";
		const char* pstr_HealthName = pDataElem->Attribute("HealthName");
		if(pstr_HealthName != NULL)
			pData->_HealthName = pstr_HealthName;
		else
			pData->_HealthName = "";
		const char* pstr_HitName = pDataElem->Attribute("HitName");
		if(pstr_HitName != NULL)
			pData->_HitName = pstr_HitName;
		else
			pData->_HitName = "";
		const char* pstr_DodgeName = pDataElem->Attribute("DodgeName");
		if(pstr_DodgeName != NULL)
			pData->_DodgeName = pstr_DodgeName;
		else
			pData->_DodgeName = "";
		const char* pstr_CriticalName = pDataElem->Attribute("CriticalName");
		if(pstr_CriticalName != NULL)
			pData->_CriticalName = pstr_CriticalName;
		else
			pData->_CriticalName = "";
		const char* pstr_CounterName = pDataElem->Attribute("CounterName");
		if(pstr_CounterName != NULL)
			pData->_CounterName = pstr_CounterName;
		else
			pData->_CounterName = "";
		const char* pstr_GreenRange = pDataElem->Attribute("GreenRange");
		if(pstr_GreenRange != NULL)
			pData->_GreenRange = pstr_GreenRange;
		else
			pData->_GreenRange = "";
		const char* pstr_GreenChance = pDataElem->Attribute("GreenChance");
		if(pstr_GreenChance != NULL)
			pData->_GreenChance = (UINT16)atoi(pstr_GreenChance);
		else
			pData->_GreenChance = 0;
		const char* pstr_BlueRange = pDataElem->Attribute("BlueRange");
		if(pstr_BlueRange != NULL)
			pData->_BlueRange = pstr_BlueRange;
		else
			pData->_BlueRange = "";
		const char* pstr_BlueChance = pDataElem->Attribute("BlueChance");
		if(pstr_BlueChance != NULL)
			pData->_BlueChance = (UINT16)atoi(pstr_BlueChance);
		else
			pData->_BlueChance = 0;
		const char* pstr_PurpleRange = pDataElem->Attribute("PurpleRange");
		if(pstr_PurpleRange != NULL)
			pData->_PurpleRange = pstr_PurpleRange;
		else
			pData->_PurpleRange = "";
		const char* pstr_PurpleChance = pDataElem->Attribute("PurpleChance");
		if(pstr_PurpleChance != NULL)
			pData->_PurpleChance = (UINT16)atoi(pstr_PurpleChance);
		else
			pData->_PurpleChance = 0;
		const char* pstr_SkillChancePurple = pDataElem->Attribute("SkillChancePurple");
		if(pstr_SkillChancePurple != NULL)
			pData->_SkillChancePurple = (UINT16)atoi(pstr_SkillChancePurple);
		else
			pData->_SkillChancePurple = 0;
		const char* pstr_SkillIdPurple = pDataElem->Attribute("SkillIdPurple");
		if(pstr_SkillIdPurple != NULL)
			pData->_SkillIdPurple = (UINT16)atoi(pstr_SkillIdPurple);
		else
			pData->_SkillIdPurple = 0;
		const char* pstr_SkillPreName = pDataElem->Attribute("SkillPreName");
		if(pstr_SkillPreName != NULL)
			pData->_SkillPreName = pstr_SkillPreName;
		else
			pData->_SkillPreName = "";
		const char* pstr_OrangeRange = pDataElem->Attribute("OrangeRange");
		if(pstr_OrangeRange != NULL)
			pData->_OrangeRange = pstr_OrangeRange;
		else
			pData->_OrangeRange = "";
		const char* pstr_OrangeChance = pDataElem->Attribute("OrangeChance");
		if(pstr_OrangeChance != NULL)
			pData->_OrangeChance = (UINT16)atoi(pstr_OrangeChance);
		else
			pData->_OrangeChance = 0;
		const char* pstr_SkillChanceOrange = pDataElem->Attribute("SkillChanceOrange");
		if(pstr_SkillChanceOrange != NULL)
			pData->_SkillChanceOrange = (UINT16)atoi(pstr_SkillChanceOrange);
		else
			pData->_SkillChanceOrange = 0;
		const char* pstr_SkillIdOrange = pDataElem->Attribute("SkillIdOrange");
		if(pstr_SkillIdOrange != NULL)
			pData->_SkillIdOrange = (UINT16)atoi(pstr_SkillIdOrange);
		else
			pData->_SkillIdOrange = 0;
		const char* pstr_SkillName = pDataElem->Attribute("SkillName");
		if(pstr_SkillName != NULL)
			pData->_SkillName = pstr_SkillName;
		else
			pData->_SkillName = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


