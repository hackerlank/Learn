// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGetCondCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GetCondCFG.h"
#include "tinyxml.h"

CGetCondLoader::~CGetCondLoader()
{
	ClearData();
}

void CGetCondLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGetCondCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGetCondLoader::LoadData(const std::string& strPath)
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
		SGetCondCFG* pData = new SGetCondCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT16)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Money = pDataElem->Attribute("Money");
		if(pstr_Money != NULL)
			pData->_Money = pstr_Money;
		else
			pData->_Money = "";
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT32)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_ItemID = pDataElem->Attribute("ItemID");
		if(pstr_ItemID != NULL)
			pData->_ItemID = pstr_ItemID;
		else
			pData->_ItemID = "";
		const char* pstr_DungeonID = pDataElem->Attribute("DungeonID");
		if(pstr_DungeonID != NULL)
			pData->_DungeonID = pstr_DungeonID;
		else
			pData->_DungeonID = "";
		const char* pstr_TaskID = pDataElem->Attribute("TaskID");
		if(pstr_TaskID != NULL)
			pData->_TaskID = pstr_TaskID;
		else
			pData->_TaskID = "";
		const char* pstr_FriendCount = pDataElem->Attribute("FriendCount");
		if(pstr_FriendCount != NULL)
			pData->_FriendCount = (UINT32)atoi(pstr_FriendCount);
		else
			pData->_FriendCount = 0;
		const char* pstr_VipLevel = pDataElem->Attribute("VipLevel");
		if(pstr_VipLevel != NULL)
			pData->_VipLevel = (UINT32)atoi(pstr_VipLevel);
		else
			pData->_VipLevel = 0;
		const char* pstr_Recharge = pDataElem->Attribute("Recharge");
		if(pstr_Recharge != NULL)
			pData->_Recharge = (UINT32)atoi(pstr_Recharge);
		else
			pData->_Recharge = 0;
		const char* pstr_Consume = pDataElem->Attribute("Consume");
		if(pstr_Consume != NULL)
			pData->_Consume = (UINT32)atoi(pstr_Consume);
		else
			pData->_Consume = 0;
		const char* pstr_PetLevel = pDataElem->Attribute("PetLevel");
		if(pstr_PetLevel != NULL)
			pData->_PetLevel = (UINT32)atoi(pstr_PetLevel);
		else
			pData->_PetLevel = 0;
		const char* pstr_PreHero = pDataElem->Attribute("PreHero");
		if(pstr_PreHero != NULL)
			pData->_PreHero = pstr_PreHero;
		else
			pData->_PreHero = "";
		const char* pstr_NeedCareer = pDataElem->Attribute("NeedCareer");
		if(pstr_NeedCareer != NULL)
			pData->_NeedCareer = (UINT8)atoi(pstr_NeedCareer);
		else
			pData->_NeedCareer = 0;
		const char* pstr_Dujie = pDataElem->Attribute("Dujie");
		if(pstr_Dujie != NULL)
			pData->_Dujie = (UINT8)atoi(pstr_Dujie);
		else
			pData->_Dujie = 0;
		const char* pstr_GuildLevel = pDataElem->Attribute("GuildLevel");
		if(pstr_GuildLevel != NULL)
			pData->_GuildLevel = (UINT8)atoi(pstr_GuildLevel);
		else
			pData->_GuildLevel = 0;
		const char* pstr_DujieLevel = pDataElem->Attribute("DujieLevel");
		if(pstr_DujieLevel != NULL)
			pData->_DujieLevel = (UINT8)atoi(pstr_DujieLevel);
		else
			pData->_DujieLevel = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


