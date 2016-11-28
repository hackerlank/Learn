// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMapCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "MapCFG.h"
#include "tinyxml.h"

CMapLoader::~CMapLoader()
{
	ClearData();
}

void CMapLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SMapCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CMapLoader::LoadData(const std::string& strPath)
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
		SMapCFG* pData = new SMapCFG;
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
			pData->_Type = (UINT8)atoi(pstr_Type);
		else
			pData->_Type = 0;
		const char* pstr_Type2 = pDataElem->Attribute("Type2");
		if(pstr_Type2 != NULL)
			pData->_Type2 = (UINT8)atoi(pstr_Type2);
		else
			pData->_Type2 = 0;
		const char* pstr_ConfigFile = pDataElem->Attribute("ConfigFile");
		if(pstr_ConfigFile != NULL)
			pData->_ConfigFile = pstr_ConfigFile;
		else
			pData->_ConfigFile = "";
		const char* pstr_ClientFile = pDataElem->Attribute("ClientFile");
		if(pstr_ClientFile != NULL)
			pData->_ClientFile = pstr_ClientFile;
		else
			pData->_ClientFile = "";
		const char* pstr_IsFar = pDataElem->Attribute("IsFar");
		if(pstr_IsFar != NULL)
			pData->_IsFar = (int)atoi(pstr_IsFar)>0?true:false;
		else
			pData->_IsFar = false;
		const char* pstr_Force = pDataElem->Attribute("Force");
		if(pstr_Force != NULL)
			pData->_Force = (UINT8)atoi(pstr_Force);
		else
			pData->_Force = 0;
		const char* pstr_Leastlevel = pDataElem->Attribute("Leastlevel");
		if(pstr_Leastlevel != NULL)
			pData->_Leastlevel = (UINT16)atoi(pstr_Leastlevel);
		else
			pData->_Leastlevel = 0;
		const char* pstr_IsSafe = pDataElem->Attribute("IsSafe");
		if(pstr_IsSafe != NULL)
			pData->_IsSafe = (int)atoi(pstr_IsSafe)>0?true:false;
		else
			pData->_IsSafe = false;
		const char* pstr_FightMap = pDataElem->Attribute("FightMap");
		if(pstr_FightMap != NULL)
			pData->_FightMap = (UINT16)atoi(pstr_FightMap);
		else
			pData->_FightMap = 0;
		const char* pstr_DropID = pDataElem->Attribute("DropID");
		if(pstr_DropID != NULL)
			pData->_DropID = (UINT16)atoi(pstr_DropID);
		else
			pData->_DropID = 0;
		const char* pstr_SkillID = pDataElem->Attribute("SkillID");
		if(pstr_SkillID != NULL)
			pData->_SkillID = pstr_SkillID;
		else
			pData->_SkillID = "";
		const char* pstr_MaxPlayer = pDataElem->Attribute("MaxPlayer");
		if(pstr_MaxPlayer != NULL)
			pData->_MaxPlayer = (UINT16)atoi(pstr_MaxPlayer);
		else
			pData->_MaxPlayer = 0;
		const char* pstr_SMaxPlayer = pDataElem->Attribute("SMaxPlayer");
		if(pstr_SMaxPlayer != NULL)
			pData->_SMaxPlayer = (UINT16)atoi(pstr_SMaxPlayer);
		else
			pData->_SMaxPlayer = 0;
		const char* pstr_MapNameAppear = pDataElem->Attribute("MapNameAppear");
		if(pstr_MapNameAppear != NULL)
			pData->_MapNameAppear = (UINT16)atoi(pstr_MapNameAppear);
		else
			pData->_MapNameAppear = 0;
		const char* pstr_LoadingBGMap = pDataElem->Attribute("LoadingBGMap");
		if(pstr_LoadingBGMap != NULL)
			pData->_LoadingBGMap = pstr_LoadingBGMap;
		else
			pData->_LoadingBGMap = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


