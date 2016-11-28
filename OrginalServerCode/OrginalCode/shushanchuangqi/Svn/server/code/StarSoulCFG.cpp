// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStarSoulCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "StarSoulCFG.h"
#include "tinyxml.h"

CStarSoulLoader::~CStarSoulLoader()
{
	ClearData();
}

void CStarSoulLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SStarSoulCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CStarSoulLoader::LoadData(const std::string& strPath)
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
		SStarSoulCFG* pData = new SStarSoulCFG;
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
		const char* pstr_StarLevel = pDataElem->Attribute("StarLevel");
		if(pstr_StarLevel != NULL)
			pData->_StarLevel = (UINT16)atoi(pstr_StarLevel);
		else
			pData->_StarLevel = 0;
		const char* pstr_SoulType = pDataElem->Attribute("SoulType");
		if(pstr_SoulType != NULL)
			pData->_SoulType = (UINT8)atoi(pstr_SoulType);
		else
			pData->_SoulType = 0;
		const char* pstr_StarPage = pDataElem->Attribute("StarPage");
		if(pstr_StarPage != NULL)
			pData->_StarPage = (UINT8)atoi(pstr_StarPage);
		else
			pData->_StarPage = 0;
		const char* pstr_RoleLevel = pDataElem->Attribute("RoleLevel");
		if(pstr_RoleLevel != NULL)
			pData->_RoleLevel = (UINT16)atoi(pstr_RoleLevel);
		else
			pData->_RoleLevel = 0;
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT32)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		const char* pstr_Chance = pDataElem->Attribute("Chance");
		if(pstr_Chance != NULL)
			pData->_Chance = (UINT16)atoi(pstr_Chance);
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
		const char* pstr_EFIGHTATTR_DODGE = pDataElem->Attribute("EFIGHTATTR_DODGE");
		if(pstr_EFIGHTATTR_DODGE != NULL)
			pData->_EFIGHTATTR_DODGE = (UINT32)atoi(pstr_EFIGHTATTR_DODGE);
		else
			pData->_EFIGHTATTR_DODGE = 0;
		const char* pstr_EFIGHTATTR_CRITICAL = pDataElem->Attribute("EFIGHTATTR_CRITICAL");
		if(pstr_EFIGHTATTR_CRITICAL != NULL)
			pData->_EFIGHTATTR_CRITICAL = (UINT32)atoi(pstr_EFIGHTATTR_CRITICAL);
		else
			pData->_EFIGHTATTR_CRITICAL = 0;
		const char* pstr_EFIGHTATTR_COUNTER = pDataElem->Attribute("EFIGHTATTR_COUNTER");
		if(pstr_EFIGHTATTR_COUNTER != NULL)
			pData->_EFIGHTATTR_COUNTER = (UINT32)atoi(pstr_EFIGHTATTR_COUNTER);
		else
			pData->_EFIGHTATTR_COUNTER = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


