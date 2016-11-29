// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterPropCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FighterPropCFG.h"
#include "tinyxml.h"

CFighterPropLoader::~CFighterPropLoader()
{
	ClearData();
}

void CFighterPropLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFighterPropCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFighterPropLoader::LoadData(const std::string& strPath)
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
		SFighterPropCFG* pData = new SFighterPropCFG;
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
		const char* pstr_AssetType = pDataElem->Attribute("AssetType");
		if(pstr_AssetType != NULL)
			pData->_AssetType = (UINT8)atoi(pstr_AssetType);
		else
			pData->_AssetType = 0;
		const char* pstr_AssetParam1 = pDataElem->Attribute("AssetParam1");
		if(pstr_AssetParam1 != NULL)
			pData->_AssetParam1 = (UINT16)atoi(pstr_AssetParam1);
		else
			pData->_AssetParam1 = 0;
		const char* pstr_AssetParam2 = pDataElem->Attribute("AssetParam2");
		if(pstr_AssetParam2 != NULL)
			pData->_AssetParam2 = (UINT8)atoi(pstr_AssetParam2);
		else
			pData->_AssetParam2 = 0;
		const char* pstr_AssetParam3 = pDataElem->Attribute("AssetParam3");
		if(pstr_AssetParam3 != NULL)
			pData->_AssetParam3 = pstr_AssetParam3;
		else
			pData->_AssetParam3 = "";
		const char* pstr_AssetExist = pDataElem->Attribute("AssetExist");
		if(pstr_AssetExist != NULL)
			pData->_AssetExist = (int)atoi(pstr_AssetExist)>0?true:false;
		else
			pData->_AssetExist = false;
		const char* pstr_FirstExist = pDataElem->Attribute("FirstExist");
		if(pstr_FirstExist != NULL)
			pData->_FirstExist = (int)atoi(pstr_FirstExist)>0?true:false;
		else
			pData->_FirstExist = false;
		const char* pstr_MonsterType = pDataElem->Attribute("MonsterType");
		if(pstr_MonsterType != NULL)
			pData->_MonsterType = pstr_MonsterType;
		else
			pData->_MonsterType = "";
		const char* pstr_HealthNum = pDataElem->Attribute("HealthNum");
		if(pstr_HealthNum != NULL)
			pData->_HealthNum = (UINT8)atoi(pstr_HealthNum);
		else
			pData->_HealthNum = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Job = pDataElem->Attribute("Job");
		if(pstr_Job != NULL)
			pData->_Job = (UINT8)atoi(pstr_Job);
		else
			pData->_Job = 0;
		const char* pstr_Inclination = pDataElem->Attribute("Inclination");
		if(pstr_Inclination != NULL)
			pData->_Inclination = (UINT8)atoi(pstr_Inclination);
		else
			pData->_Inclination = 0;
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT8)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_EnterRage = pDataElem->Attribute("EnterRage");
		if(pstr_EnterRage != NULL)
			pData->_EnterRage = (UINT8)atoi(pstr_EnterRage);
		else
			pData->_EnterRage = 0;
		const char* pstr_MaxRage = pDataElem->Attribute("MaxRage");
		if(pstr_MaxRage != NULL)
			pData->_MaxRage = (UINT8)atoi(pstr_MaxRage);
		else
			pData->_MaxRage = 0;
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
		const char* pstr_EFIGHTATTR_COUNTERRATE = pDataElem->Attribute("EFIGHTATTR_COUNTERRATE");
		if(pstr_EFIGHTATTR_COUNTERRATE != NULL)
			pData->_EFIGHTATTR_COUNTERRATE = (FLOAT)atof(pstr_EFIGHTATTR_COUNTERRATE);
		else
			pData->_EFIGHTATTR_COUNTERRATE = 0.0f;
		const char* pstr_EFIGHTATTR_RESIST = pDataElem->Attribute("EFIGHTATTR_RESIST");
		if(pstr_EFIGHTATTR_RESIST != NULL)
			pData->_EFIGHTATTR_RESIST = (FLOAT)atof(pstr_EFIGHTATTR_RESIST);
		else
			pData->_EFIGHTATTR_RESIST = 0.0f;
		const char* pstr_EFIGHTATTR_RESISTRATE = pDataElem->Attribute("EFIGHTATTR_RESISTRATE");
		if(pstr_EFIGHTATTR_RESISTRATE != NULL)
			pData->_EFIGHTATTR_RESISTRATE = (FLOAT)atof(pstr_EFIGHTATTR_RESISTRATE);
		else
			pData->_EFIGHTATTR_RESISTRATE = 0.0f;
		const char* pstr_EFIGHTATTR_INITAURA = pDataElem->Attribute("EFIGHTATTR_INITAURA");
		if(pstr_EFIGHTATTR_INITAURA != NULL)
			pData->_EFIGHTATTR_INITAURA = (UINT32)atoi(pstr_EFIGHTATTR_INITAURA);
		else
			pData->_EFIGHTATTR_INITAURA = 0;
		const char* pstr_EFIGHTATTR_MAXAURA = pDataElem->Attribute("EFIGHTATTR_MAXAURA");
		if(pstr_EFIGHTATTR_MAXAURA != NULL)
			pData->_EFIGHTATTR_MAXAURA = (UINT32)atoi(pstr_EFIGHTATTR_MAXAURA);
		else
			pData->_EFIGHTATTR_MAXAURA = 0;
		const char* pstr_EFIGHTATTR_CRIEXTRAADD = pDataElem->Attribute("EFIGHTATTR_CRIEXTRAADD");
		if(pstr_EFIGHTATTR_CRIEXTRAADD != NULL)
			pData->_EFIGHTATTR_CRIEXTRAADD = (FLOAT)atof(pstr_EFIGHTATTR_CRIEXTRAADD);
		else
			pData->_EFIGHTATTR_CRIEXTRAADD = 0.0f;
		const char* pstr_EFIGHTATTR_CRIEXTRARDC = pDataElem->Attribute("EFIGHTATTR_CRIEXTRARDC");
		if(pstr_EFIGHTATTR_CRIEXTRARDC != NULL)
			pData->_EFIGHTATTR_CRIEXTRARDC = (FLOAT)atof(pstr_EFIGHTATTR_CRIEXTRARDC);
		else
			pData->_EFIGHTATTR_CRIEXTRARDC = 0.0f;
		const char* pstr_EFIGHTATTR_METALATK = pDataElem->Attribute("EFIGHTATTR_METALATK");
		if(pstr_EFIGHTATTR_METALATK != NULL)
			pData->_EFIGHTATTR_METALATK = (FLOAT)atof(pstr_EFIGHTATTR_METALATK);
		else
			pData->_EFIGHTATTR_METALATK = 0.0f;
		const char* pstr_EFIGHTATTR_WOODATK = pDataElem->Attribute("EFIGHTATTR_WOODATK");
		if(pstr_EFIGHTATTR_WOODATK != NULL)
			pData->_EFIGHTATTR_WOODATK = (FLOAT)atof(pstr_EFIGHTATTR_WOODATK);
		else
			pData->_EFIGHTATTR_WOODATK = 0.0f;
		const char* pstr_EFIGHTATTR_WATERATK = pDataElem->Attribute("EFIGHTATTR_WATERATK");
		if(pstr_EFIGHTATTR_WATERATK != NULL)
			pData->_EFIGHTATTR_WATERATK = (FLOAT)atof(pstr_EFIGHTATTR_WATERATK);
		else
			pData->_EFIGHTATTR_WATERATK = 0.0f;
		const char* pstr_EFIGHTATTR_FIREATK = pDataElem->Attribute("EFIGHTATTR_FIREATK");
		if(pstr_EFIGHTATTR_FIREATK != NULL)
			pData->_EFIGHTATTR_FIREATK = (FLOAT)atof(pstr_EFIGHTATTR_FIREATK);
		else
			pData->_EFIGHTATTR_FIREATK = 0.0f;
		const char* pstr_EFIGHTATTR_EARTHATK = pDataElem->Attribute("EFIGHTATTR_EARTHATK");
		if(pstr_EFIGHTATTR_EARTHATK != NULL)
			pData->_EFIGHTATTR_EARTHATK = (FLOAT)atof(pstr_EFIGHTATTR_EARTHATK);
		else
			pData->_EFIGHTATTR_EARTHATK = 0.0f;
		const char* pstr_EFIGHTATTR_METALDEF = pDataElem->Attribute("EFIGHTATTR_METALDEF");
		if(pstr_EFIGHTATTR_METALDEF != NULL)
			pData->_EFIGHTATTR_METALDEF = (FLOAT)atof(pstr_EFIGHTATTR_METALDEF);
		else
			pData->_EFIGHTATTR_METALDEF = 0.0f;
		const char* pstr_EFIGHTATTR_WOODDEF = pDataElem->Attribute("EFIGHTATTR_WOODDEF");
		if(pstr_EFIGHTATTR_WOODDEF != NULL)
			pData->_EFIGHTATTR_WOODDEF = (FLOAT)atof(pstr_EFIGHTATTR_WOODDEF);
		else
			pData->_EFIGHTATTR_WOODDEF = 0.0f;
		const char* pstr_EFIGHTATTR_WATERDEF = pDataElem->Attribute("EFIGHTATTR_WATERDEF");
		if(pstr_EFIGHTATTR_WATERDEF != NULL)
			pData->_EFIGHTATTR_WATERDEF = (FLOAT)atof(pstr_EFIGHTATTR_WATERDEF);
		else
			pData->_EFIGHTATTR_WATERDEF = 0.0f;
		const char* pstr_EFIGHTATTR_FIREDEF = pDataElem->Attribute("EFIGHTATTR_FIREDEF");
		if(pstr_EFIGHTATTR_FIREDEF != NULL)
			pData->_EFIGHTATTR_FIREDEF = (FLOAT)atof(pstr_EFIGHTATTR_FIREDEF);
		else
			pData->_EFIGHTATTR_FIREDEF = 0.0f;
		const char* pstr_EFIGHTATTR_EARTHDEF = pDataElem->Attribute("EFIGHTATTR_EARTHDEF");
		if(pstr_EFIGHTATTR_EARTHDEF != NULL)
			pData->_EFIGHTATTR_EARTHDEF = (FLOAT)atof(pstr_EFIGHTATTR_EARTHDEF);
		else
			pData->_EFIGHTATTR_EARTHDEF = 0.0f;
		const char* pstr_EFIGHTATTR_PHYATK_PER = pDataElem->Attribute("EFIGHTATTR_PHYATK_PER");
		if(pstr_EFIGHTATTR_PHYATK_PER != NULL)
			pData->_EFIGHTATTR_PHYATK_PER = (FLOAT)atof(pstr_EFIGHTATTR_PHYATK_PER);
		else
			pData->_EFIGHTATTR_PHYATK_PER = 0.0f;
		const char* pstr_EFIGHTATTR_MGCATK_PER = pDataElem->Attribute("EFIGHTATTR_MGCATK_PER");
		if(pstr_EFIGHTATTR_MGCATK_PER != NULL)
			pData->_EFIGHTATTR_MGCATK_PER = (FLOAT)atof(pstr_EFIGHTATTR_MGCATK_PER);
		else
			pData->_EFIGHTATTR_MGCATK_PER = 0.0f;
		const char* pstr_EFIGHTATTR_PHYDEF_PER = pDataElem->Attribute("EFIGHTATTR_PHYDEF_PER");
		if(pstr_EFIGHTATTR_PHYDEF_PER != NULL)
			pData->_EFIGHTATTR_PHYDEF_PER = (FLOAT)atof(pstr_EFIGHTATTR_PHYDEF_PER);
		else
			pData->_EFIGHTATTR_PHYDEF_PER = 0.0f;
		const char* pstr_EFIGHTATTR_MGCDEF_PER = pDataElem->Attribute("EFIGHTATTR_MGCDEF_PER");
		if(pstr_EFIGHTATTR_MGCDEF_PER != NULL)
			pData->_EFIGHTATTR_MGCDEF_PER = (FLOAT)atof(pstr_EFIGHTATTR_MGCDEF_PER);
		else
			pData->_EFIGHTATTR_MGCDEF_PER = 0.0f;
		const char* pstr_EFIGHTATTR_MAXHP_PER = pDataElem->Attribute("EFIGHTATTR_MAXHP_PER");
		if(pstr_EFIGHTATTR_MAXHP_PER != NULL)
			pData->_EFIGHTATTR_MAXHP_PER = (FLOAT)atof(pstr_EFIGHTATTR_MAXHP_PER);
		else
			pData->_EFIGHTATTR_MAXHP_PER = 0.0f;
		const char* pstr_EFIGHTATTR_SPEED_PER = pDataElem->Attribute("EFIGHTATTR_SPEED_PER");
		if(pstr_EFIGHTATTR_SPEED_PER != NULL)
			pData->_EFIGHTATTR_SPEED_PER = (FLOAT)atof(pstr_EFIGHTATTR_SPEED_PER);
		else
			pData->_EFIGHTATTR_SPEED_PER = 0.0f;
		const char* pstr_EFIGHTATTR_HIT_PER = pDataElem->Attribute("EFIGHTATTR_HIT_PER");
		if(pstr_EFIGHTATTR_HIT_PER != NULL)
			pData->_EFIGHTATTR_HIT_PER = (FLOAT)atof(pstr_EFIGHTATTR_HIT_PER);
		else
			pData->_EFIGHTATTR_HIT_PER = 0.0f;
		const char* pstr_EFIGHTATTR_DODGE_PER = pDataElem->Attribute("EFIGHTATTR_DODGE_PER");
		if(pstr_EFIGHTATTR_DODGE_PER != NULL)
			pData->_EFIGHTATTR_DODGE_PER = (FLOAT)atof(pstr_EFIGHTATTR_DODGE_PER);
		else
			pData->_EFIGHTATTR_DODGE_PER = 0.0f;
		const char* pstr_EFIGHTATTR_CRITICAL_PER = pDataElem->Attribute("EFIGHTATTR_CRITICAL_PER");
		if(pstr_EFIGHTATTR_CRITICAL_PER != NULL)
			pData->_EFIGHTATTR_CRITICAL_PER = (FLOAT)atof(pstr_EFIGHTATTR_CRITICAL_PER);
		else
			pData->_EFIGHTATTR_CRITICAL_PER = 0.0f;
		const char* pstr_EFIGHTATTR_ANTICRITCAL_PER = pDataElem->Attribute("EFIGHTATTR_ANTICRITCAL_PER");
		if(pstr_EFIGHTATTR_ANTICRITCAL_PER != NULL)
			pData->_EFIGHTATTR_ANTICRITCAL_PER = (FLOAT)atof(pstr_EFIGHTATTR_ANTICRITCAL_PER);
		else
			pData->_EFIGHTATTR_ANTICRITCAL_PER = 0.0f;
		const char* pstr_EFIGHTATTR_BLOCK_PER = pDataElem->Attribute("EFIGHTATTR_BLOCK_PER");
		if(pstr_EFIGHTATTR_BLOCK_PER != NULL)
			pData->_EFIGHTATTR_BLOCK_PER = (FLOAT)atof(pstr_EFIGHTATTR_BLOCK_PER);
		else
			pData->_EFIGHTATTR_BLOCK_PER = 0.0f;
		const char* pstr_EFIGHTATTR_PIERCE_PER = pDataElem->Attribute("EFIGHTATTR_PIERCE_PER");
		if(pstr_EFIGHTATTR_PIERCE_PER != NULL)
			pData->_EFIGHTATTR_PIERCE_PER = (FLOAT)atof(pstr_EFIGHTATTR_PIERCE_PER);
		else
			pData->_EFIGHTATTR_PIERCE_PER = 0.0f;
		const char* pstr_EFIGHTATTR_COUNTER_PER = pDataElem->Attribute("EFIGHTATTR_COUNTER_PER");
		if(pstr_EFIGHTATTR_COUNTER_PER != NULL)
			pData->_EFIGHTATTR_COUNTER_PER = (FLOAT)atof(pstr_EFIGHTATTR_COUNTER_PER);
		else
			pData->_EFIGHTATTR_COUNTER_PER = 0.0f;
		const char* pstr_EFIGHTATTR_RESIST_PER = pDataElem->Attribute("EFIGHTATTR_RESIST_PER");
		if(pstr_EFIGHTATTR_RESIST_PER != NULL)
			pData->_EFIGHTATTR_RESIST_PER = (FLOAT)atof(pstr_EFIGHTATTR_RESIST_PER);
		else
			pData->_EFIGHTATTR_RESIST_PER = 0.0f;
		const char* pstr_EFIGHTATTR_ANTIEFFECT = pDataElem->Attribute("EFIGHTATTR_ANTIEFFECT");
		if(pstr_EFIGHTATTR_ANTIEFFECT != NULL)
			pData->_EFIGHTATTR_ANTIEFFECT = (FLOAT)atof(pstr_EFIGHTATTR_ANTIEFFECT);
		else
			pData->_EFIGHTATTR_ANTIEFFECT = 0.0f;
		const char* pstr_SOUL = pDataElem->Attribute("SOUL");
		if(pstr_SOUL != NULL)
			pData->_SOUL = (FLOAT)atof(pstr_SOUL);
		else
			pData->_SOUL = 0.0f;
		const char* pstr_NormalDead = pDataElem->Attribute("NormalDead");
		if(pstr_NormalDead != NULL)
			pData->_NormalDead = (UINT32)atoi(pstr_NormalDead);
		else
			pData->_NormalDead = 0;
		const char* pstr_NormalAttack = pDataElem->Attribute("NormalAttack");
		if(pstr_NormalAttack != NULL)
			pData->_NormalAttack = (UINT32)atoi(pstr_NormalAttack);
		else
			pData->_NormalAttack = 0;
		const char* pstr_NormalAttackEx = pDataElem->Attribute("NormalAttackEx");
		if(pstr_NormalAttackEx != NULL)
			pData->_NormalAttackEx = pstr_NormalAttackEx;
		else
			pData->_NormalAttackEx = "";
		const char* pstr_Combination = pDataElem->Attribute("Combination");
		if(pstr_Combination != NULL)
			pData->_Combination = pstr_Combination;
		else
			pData->_Combination = "";
		const char* pstr_Skills = pDataElem->Attribute("Skills");
		if(pstr_Skills != NULL)
			pData->_Skills = pstr_Skills;
		else
			pData->_Skills = "";
		const char* pstr_SkillsEx = pDataElem->Attribute("SkillsEx");
		if(pstr_SkillsEx != NULL)
			pData->_SkillsEx = pstr_SkillsEx;
		else
			pData->_SkillsEx = "";
		const char* pstr_Peerless = pDataElem->Attribute("Peerless");
		if(pstr_Peerless != NULL)
			pData->_Peerless = pstr_Peerless;
		else
			pData->_Peerless = "";
		const char* pstr_Talent = pDataElem->Attribute("Talent");
		if(pstr_Talent != NULL)
			pData->_Talent = pstr_Talent;
		else
			pData->_Talent = "";
		const char* pstr_Xinfa = pDataElem->Attribute("Xinfa");
		if(pstr_Xinfa != NULL)
			pData->_Xinfa = pstr_Xinfa;
		else
			pData->_Xinfa = "";
		const char* pstr_Closes = pDataElem->Attribute("Closes");
		if(pstr_Closes != NULL)
			pData->_Closes = (UINT16)atoi(pstr_Closes);
		else
			pData->_Closes = 0;
		const char* pstr_Weapon = pDataElem->Attribute("Weapon");
		if(pstr_Weapon != NULL)
			pData->_Weapon = (UINT16)atoi(pstr_Weapon);
		else
			pData->_Weapon = 0;
		const char* pstr_Star = pDataElem->Attribute("Star");
		if(pstr_Star != NULL)
			pData->_Star = (UINT8)atoi(pstr_Star);
		else
			pData->_Star = 0;
		const char* pstr_DujieTemplateId = pDataElem->Attribute("DujieTemplateId");
		if(pstr_DujieTemplateId != NULL)
			pData->_DujieTemplateId = (UINT16)atoi(pstr_DujieTemplateId);
		else
			pData->_DujieTemplateId = 0;
		const char* pstr_HeroFeature = pDataElem->Attribute("HeroFeature");
		if(pstr_HeroFeature != NULL)
			pData->_HeroFeature = (UINT8)atoi(pstr_HeroFeature);
		else
			pData->_HeroFeature = 0;
		const char* pstr_HeroFeatureDes = pDataElem->Attribute("HeroFeatureDes");
		if(pstr_HeroFeatureDes != NULL)
			pData->_HeroFeatureDes = pstr_HeroFeatureDes;
		else
			pData->_HeroFeatureDes = "";
		const char* pstr_HeroFeatureDesText = pDataElem->Attribute("HeroFeatureDesText");
		if(pstr_HeroFeatureDesText != NULL)
			pData->_HeroFeatureDesText = pstr_HeroFeatureDesText;
		else
			pData->_HeroFeatureDesText = "";
		const char* pstr_AttackTalent = pDataElem->Attribute("AttackTalent");
		if(pstr_AttackTalent != NULL)
			pData->_AttackTalent = (UINT8)atoi(pstr_AttackTalent);
		else
			pData->_AttackTalent = 0;
		const char* pstr_PhysicalDefenseTalent = pDataElem->Attribute("PhysicalDefenseTalent");
		if(pstr_PhysicalDefenseTalent != NULL)
			pData->_PhysicalDefenseTalent = (UINT8)atoi(pstr_PhysicalDefenseTalent);
		else
			pData->_PhysicalDefenseTalent = 0;
		const char* pstr_MagicDefenseTalent = pDataElem->Attribute("MagicDefenseTalent");
		if(pstr_MagicDefenseTalent != NULL)
			pData->_MagicDefenseTalent = (UINT8)atoi(pstr_MagicDefenseTalent);
		else
			pData->_MagicDefenseTalent = 0;
		const char* pstr_HealthTalent = pDataElem->Attribute("HealthTalent");
		if(pstr_HealthTalent != NULL)
			pData->_HealthTalent = (UINT8)atoi(pstr_HealthTalent);
		else
			pData->_HealthTalent = 0;
		const char* pstr_RecruitItem = pDataElem->Attribute("RecruitItem");
		if(pstr_RecruitItem != NULL)
			pData->_RecruitItem = (UINT16)atoi(pstr_RecruitItem);
		else
			pData->_RecruitItem = 0;
		const char* pstr_Sort = pDataElem->Attribute("Sort");
		if(pstr_Sort != NULL)
			pData->_Sort = (UINT16)atoi(pstr_Sort);
		else
			pData->_Sort = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


