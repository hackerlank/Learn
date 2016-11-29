// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STreasureToolsSuitCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "TreasureToolsSuitCFG.h"
#include "tinyxml.h"

CTreasureToolsSuitLoader::~CTreasureToolsSuitLoader()
{
	ClearData();
}

void CTreasureToolsSuitLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		STreasureToolsSuitCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CTreasureToolsSuitLoader::LoadData(const std::string& strPath)
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
		STreasureToolsSuitCFG* pData = new STreasureToolsSuitCFG;
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
		const char* pstr_Color = pDataElem->Attribute("Color");
		if(pstr_Color != NULL)
			pData->_Color = (UINT16)atoi(pstr_Color);
		else
			pData->_Color = 0;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Num = pDataElem->Attribute("Num");
		if(pstr_Num != NULL)
			pData->_Num = (UINT8)atoi(pstr_Num);
		else
			pData->_Num = 0;
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
		const char* pstr_AdditionalSkills = pDataElem->Attribute("AdditionalSkills");
		if(pstr_AdditionalSkills != NULL)
			pData->_AdditionalSkills = (UINT16)atoi(pstr_AdditionalSkills);
		else
			pData->_AdditionalSkills = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


