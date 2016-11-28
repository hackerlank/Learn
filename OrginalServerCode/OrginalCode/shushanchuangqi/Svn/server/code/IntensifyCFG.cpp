// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SIntensifyCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "IntensifyCFG.h"
#include "tinyxml.h"

CIntensifyLoader::~CIntensifyLoader()
{
	ClearData();
}

void CIntensifyLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SIntensifyCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CIntensifyLoader::LoadData(const std::string& strPath)
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
		SIntensifyCFG* pData = new SIntensifyCFG;
		const char* pstr_Job = pDataElem->Attribute("Job");
		if(pstr_Job != NULL)
			pData->_Job = (UINT8)atoi(pstr_Job);
		else
			pData->_Job = 0;
		const char* pstr_ArmorType = pDataElem->Attribute("ArmorType");
		if(pstr_ArmorType != NULL)
			pData->_ArmorType = (UINT8)atoi(pstr_ArmorType);
		else
			pData->_ArmorType = 0;
		const char* pstr_IntensifyLevel = pDataElem->Attribute("IntensifyLevel");
		if(pstr_IntensifyLevel != NULL)
			pData->_IntensifyLevel = (UINT8)atoi(pstr_IntensifyLevel);
		else
			pData->_IntensifyLevel = 0;
		const char* pstr_SilverNeed = pDataElem->Attribute("SilverNeed");
		if(pstr_SilverNeed != NULL)
			pData->_SilverNeed = (UINT32)atoi(pstr_SilverNeed);
		else
			pData->_SilverNeed = 0;
		const char* pstr_SpecialEffect = pDataElem->Attribute("SpecialEffect");
		if(pstr_SpecialEffect != NULL)
			pData->_SpecialEffect = (UINT32)atoi(pstr_SpecialEffect);
		else
			pData->_SpecialEffect = 0;
		const char* pstr_Chance = pDataElem->Attribute("Chance");
		if(pstr_Chance != NULL)
			pData->_Chance = (UINT32)atoi(pstr_Chance);
		else
			pData->_Chance = 0;
		const char* pstr_EFIGHTATTR_PHYATK = pDataElem->Attribute("EFIGHTATTR_PHYATK");
		if(pstr_EFIGHTATTR_PHYATK != NULL)
			pData->_EFIGHTATTR_PHYATK = (UINT32)atoi(pstr_EFIGHTATTR_PHYATK);
		else
			pData->_EFIGHTATTR_PHYATK = 0;
		const char* pstr_EFIGHTATTR_MGCATK = pDataElem->Attribute("EFIGHTATTR_MGCATK");
		if(pstr_EFIGHTATTR_MGCATK != NULL)
			pData->_EFIGHTATTR_MGCATK = (UINT32)atoi(pstr_EFIGHTATTR_MGCATK);
		else
			pData->_EFIGHTATTR_MGCATK = 0;
		const char* pstr_EFIGHTATTR_PHYDEF = pDataElem->Attribute("EFIGHTATTR_PHYDEF");
		if(pstr_EFIGHTATTR_PHYDEF != NULL)
			pData->_EFIGHTATTR_PHYDEF = (UINT32)atoi(pstr_EFIGHTATTR_PHYDEF);
		else
			pData->_EFIGHTATTR_PHYDEF = 0;
		const char* pstr_EFIGHTATTR_MGCDEF = pDataElem->Attribute("EFIGHTATTR_MGCDEF");
		if(pstr_EFIGHTATTR_MGCDEF != NULL)
			pData->_EFIGHTATTR_MGCDEF = (UINT32)atoi(pstr_EFIGHTATTR_MGCDEF);
		else
			pData->_EFIGHTATTR_MGCDEF = 0;
		const char* pstr_EFIGHTATTR_PHYRDC = pDataElem->Attribute("EFIGHTATTR_PHYRDC");
		if(pstr_EFIGHTATTR_PHYRDC != NULL)
			pData->_EFIGHTATTR_PHYRDC = (UINT32)atoi(pstr_EFIGHTATTR_PHYRDC);
		else
			pData->_EFIGHTATTR_PHYRDC = 0;
		const char* pstr_EFIGHTATTR_MGCRDC = pDataElem->Attribute("EFIGHTATTR_MGCRDC");
		if(pstr_EFIGHTATTR_MGCRDC != NULL)
			pData->_EFIGHTATTR_MGCRDC = (UINT32)atoi(pstr_EFIGHTATTR_MGCRDC);
		else
			pData->_EFIGHTATTR_MGCRDC = 0;
		const char* pstr_EFIGHTATTR_MAXHP = pDataElem->Attribute("EFIGHTATTR_MAXHP");
		if(pstr_EFIGHTATTR_MAXHP != NULL)
			pData->_EFIGHTATTR_MAXHP = (UINT32)atoi(pstr_EFIGHTATTR_MAXHP);
		else
			pData->_EFIGHTATTR_MAXHP = 0;
		const char* pstr_EFIGHTATTR_SPEED = pDataElem->Attribute("EFIGHTATTR_SPEED");
		if(pstr_EFIGHTATTR_SPEED != NULL)
			pData->_EFIGHTATTR_SPEED = (UINT32)atoi(pstr_EFIGHTATTR_SPEED);
		else
			pData->_EFIGHTATTR_SPEED = 0;
		const char* pstr_EFIGHTATTR_HIT = pDataElem->Attribute("EFIGHTATTR_HIT");
		if(pstr_EFIGHTATTR_HIT != NULL)
			pData->_EFIGHTATTR_HIT = (UINT32)atoi(pstr_EFIGHTATTR_HIT);
		else
			pData->_EFIGHTATTR_HIT = 0;
		const char* pstr_EFIGHTATTR_HITRATE = pDataElem->Attribute("EFIGHTATTR_HITRATE");
		if(pstr_EFIGHTATTR_HITRATE != NULL)
			pData->_EFIGHTATTR_HITRATE = (UINT32)atoi(pstr_EFIGHTATTR_HITRATE);
		else
			pData->_EFIGHTATTR_HITRATE = 0;
		const char* pstr_EFIGHTATTR_DODGE = pDataElem->Attribute("EFIGHTATTR_DODGE");
		if(pstr_EFIGHTATTR_DODGE != NULL)
			pData->_EFIGHTATTR_DODGE = (UINT32)atoi(pstr_EFIGHTATTR_DODGE);
		else
			pData->_EFIGHTATTR_DODGE = 0;
		const char* pstr_EFIGHTATTR_DODGERATE = pDataElem->Attribute("EFIGHTATTR_DODGERATE");
		if(pstr_EFIGHTATTR_DODGERATE != NULL)
			pData->_EFIGHTATTR_DODGERATE = (UINT32)atoi(pstr_EFIGHTATTR_DODGERATE);
		else
			pData->_EFIGHTATTR_DODGERATE = 0;
		const char* pstr_EFIGHTATTR_CRITICAL = pDataElem->Attribute("EFIGHTATTR_CRITICAL");
		if(pstr_EFIGHTATTR_CRITICAL != NULL)
			pData->_EFIGHTATTR_CRITICAL = (UINT32)atoi(pstr_EFIGHTATTR_CRITICAL);
		else
			pData->_EFIGHTATTR_CRITICAL = 0;
		const char* pstr_EFIGHTATTR_CRTRATE = pDataElem->Attribute("EFIGHTATTR_CRTRATE");
		if(pstr_EFIGHTATTR_CRTRATE != NULL)
			pData->_EFIGHTATTR_CRTRATE = (UINT32)atoi(pstr_EFIGHTATTR_CRTRATE);
		else
			pData->_EFIGHTATTR_CRTRATE = 0;
		const char* pstr_EFIGHTATTR_ANTICRITCAL = pDataElem->Attribute("EFIGHTATTR_ANTICRITCAL");
		if(pstr_EFIGHTATTR_ANTICRITCAL != NULL)
			pData->_EFIGHTATTR_ANTICRITCAL = (UINT32)atoi(pstr_EFIGHTATTR_ANTICRITCAL);
		else
			pData->_EFIGHTATTR_ANTICRITCAL = 0;
		const char* pstr_EFIGHTATTR_ANTICRTRATE = pDataElem->Attribute("EFIGHTATTR_ANTICRTRATE");
		if(pstr_EFIGHTATTR_ANTICRTRATE != NULL)
			pData->_EFIGHTATTR_ANTICRTRATE = (UINT32)atoi(pstr_EFIGHTATTR_ANTICRTRATE);
		else
			pData->_EFIGHTATTR_ANTICRTRATE = 0;
		const char* pstr_EFIGHTATTR_BLOCK = pDataElem->Attribute("EFIGHTATTR_BLOCK");
		if(pstr_EFIGHTATTR_BLOCK != NULL)
			pData->_EFIGHTATTR_BLOCK = (UINT32)atoi(pstr_EFIGHTATTR_BLOCK);
		else
			pData->_EFIGHTATTR_BLOCK = 0;
		const char* pstr_EFIGHTATTR_BLOCKRATE = pDataElem->Attribute("EFIGHTATTR_BLOCKRATE");
		if(pstr_EFIGHTATTR_BLOCKRATE != NULL)
			pData->_EFIGHTATTR_BLOCKRATE = (UINT32)atoi(pstr_EFIGHTATTR_BLOCKRATE);
		else
			pData->_EFIGHTATTR_BLOCKRATE = 0;
		const char* pstr_EFIGHTATTR_PIERCE = pDataElem->Attribute("EFIGHTATTR_PIERCE");
		if(pstr_EFIGHTATTR_PIERCE != NULL)
			pData->_EFIGHTATTR_PIERCE = (UINT32)atoi(pstr_EFIGHTATTR_PIERCE);
		else
			pData->_EFIGHTATTR_PIERCE = 0;
		const char* pstr_EFIGHTATTR_PIERCERATE = pDataElem->Attribute("EFIGHTATTR_PIERCERATE");
		if(pstr_EFIGHTATTR_PIERCERATE != NULL)
			pData->_EFIGHTATTR_PIERCERATE = (UINT32)atoi(pstr_EFIGHTATTR_PIERCERATE);
		else
			pData->_EFIGHTATTR_PIERCERATE = 0;
		const char* pstr_EFIGHTATTR_COUNTER = pDataElem->Attribute("EFIGHTATTR_COUNTER");
		if(pstr_EFIGHTATTR_COUNTER != NULL)
			pData->_EFIGHTATTR_COUNTER = (UINT32)atoi(pstr_EFIGHTATTR_COUNTER);
		else
			pData->_EFIGHTATTR_COUNTER = 0;
		const char* pstr_EFIGHTATTR_COUNTERRATE = pDataElem->Attribute("EFIGHTATTR_COUNTERRATE");
		if(pstr_EFIGHTATTR_COUNTERRATE != NULL)
			pData->_EFIGHTATTR_COUNTERRATE = (UINT32)atoi(pstr_EFIGHTATTR_COUNTERRATE);
		else
			pData->_EFIGHTATTR_COUNTERRATE = 0;
		const char* pstr_EFIGHTATTR_RESIST = pDataElem->Attribute("EFIGHTATTR_RESIST");
		if(pstr_EFIGHTATTR_RESIST != NULL)
			pData->_EFIGHTATTR_RESIST = (UINT32)atoi(pstr_EFIGHTATTR_RESIST);
		else
			pData->_EFIGHTATTR_RESIST = 0;
		const char* pstr_EFIGHTATTR_RESISTRATE = pDataElem->Attribute("EFIGHTATTR_RESISTRATE");
		if(pstr_EFIGHTATTR_RESISTRATE != NULL)
			pData->_EFIGHTATTR_RESISTRATE = (UINT32)atoi(pstr_EFIGHTATTR_RESISTRATE);
		else
			pData->_EFIGHTATTR_RESISTRATE = 0;
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
			pData->_EFIGHTATTR_CRIEXTRAADD = (UINT32)atoi(pstr_EFIGHTATTR_CRIEXTRAADD);
		else
			pData->_EFIGHTATTR_CRIEXTRAADD = 0;
		const char* pstr_EFIGHTATTR_CRIEXTRARDC = pDataElem->Attribute("EFIGHTATTR_CRIEXTRARDC");
		if(pstr_EFIGHTATTR_CRIEXTRARDC != NULL)
			pData->_EFIGHTATTR_CRIEXTRARDC = (UINT32)atoi(pstr_EFIGHTATTR_CRIEXTRARDC);
		else
			pData->_EFIGHTATTR_CRIEXTRARDC = 0;
		const char* pstr_EFIGHTATTR_METALATK = pDataElem->Attribute("EFIGHTATTR_METALATK");
		if(pstr_EFIGHTATTR_METALATK != NULL)
			pData->_EFIGHTATTR_METALATK = (UINT32)atoi(pstr_EFIGHTATTR_METALATK);
		else
			pData->_EFIGHTATTR_METALATK = 0;
		const char* pstr_EFIGHTATTR_WOODATK = pDataElem->Attribute("EFIGHTATTR_WOODATK");
		if(pstr_EFIGHTATTR_WOODATK != NULL)
			pData->_EFIGHTATTR_WOODATK = (UINT32)atoi(pstr_EFIGHTATTR_WOODATK);
		else
			pData->_EFIGHTATTR_WOODATK = 0;
		const char* pstr_EFIGHTATTR_WATERATK = pDataElem->Attribute("EFIGHTATTR_WATERATK");
		if(pstr_EFIGHTATTR_WATERATK != NULL)
			pData->_EFIGHTATTR_WATERATK = (UINT32)atoi(pstr_EFIGHTATTR_WATERATK);
		else
			pData->_EFIGHTATTR_WATERATK = 0;
		const char* pstr_EFIGHTATTR_FIREATK = pDataElem->Attribute("EFIGHTATTR_FIREATK");
		if(pstr_EFIGHTATTR_FIREATK != NULL)
			pData->_EFIGHTATTR_FIREATK = (UINT32)atoi(pstr_EFIGHTATTR_FIREATK);
		else
			pData->_EFIGHTATTR_FIREATK = 0;
		const char* pstr_EFIGHTATTR_EARTHATK = pDataElem->Attribute("EFIGHTATTR_EARTHATK");
		if(pstr_EFIGHTATTR_EARTHATK != NULL)
			pData->_EFIGHTATTR_EARTHATK = (UINT32)atoi(pstr_EFIGHTATTR_EARTHATK);
		else
			pData->_EFIGHTATTR_EARTHATK = 0;
		const char* pstr_EFIGHTATTR_METALDEF = pDataElem->Attribute("EFIGHTATTR_METALDEF");
		if(pstr_EFIGHTATTR_METALDEF != NULL)
			pData->_EFIGHTATTR_METALDEF = (UINT32)atoi(pstr_EFIGHTATTR_METALDEF);
		else
			pData->_EFIGHTATTR_METALDEF = 0;
		const char* pstr_EFIGHTATTR_WOODDEF = pDataElem->Attribute("EFIGHTATTR_WOODDEF");
		if(pstr_EFIGHTATTR_WOODDEF != NULL)
			pData->_EFIGHTATTR_WOODDEF = (UINT32)atoi(pstr_EFIGHTATTR_WOODDEF);
		else
			pData->_EFIGHTATTR_WOODDEF = 0;
		const char* pstr_EFIGHTATTR_WATERDEF = pDataElem->Attribute("EFIGHTATTR_WATERDEF");
		if(pstr_EFIGHTATTR_WATERDEF != NULL)
			pData->_EFIGHTATTR_WATERDEF = (UINT32)atoi(pstr_EFIGHTATTR_WATERDEF);
		else
			pData->_EFIGHTATTR_WATERDEF = 0;
		const char* pstr_EFIGHTATTR_FIREDEF = pDataElem->Attribute("EFIGHTATTR_FIREDEF");
		if(pstr_EFIGHTATTR_FIREDEF != NULL)
			pData->_EFIGHTATTR_FIREDEF = (UINT32)atoi(pstr_EFIGHTATTR_FIREDEF);
		else
			pData->_EFIGHTATTR_FIREDEF = 0;
		const char* pstr_EFIGHTATTR_EARTHDEF = pDataElem->Attribute("EFIGHTATTR_EARTHDEF");
		if(pstr_EFIGHTATTR_EARTHDEF != NULL)
			pData->_EFIGHTATTR_EARTHDEF = (UINT32)atoi(pstr_EFIGHTATTR_EARTHDEF);
		else
			pData->_EFIGHTATTR_EARTHDEF = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


