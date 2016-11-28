// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuardEMeiLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuardEMeiLevelCFG.h"
#include "tinyxml.h"

CGuardEMeiLevelLoader::~CGuardEMeiLevelLoader()
{
	ClearData();
}

void CGuardEMeiLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuardEMeiLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuardEMeiLevelLoader::LoadData(const std::string& strPath)
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
		SGuardEMeiLevelCFG* pData = new SGuardEMeiLevelCFG;
		const char* pstr_GroupId = pDataElem->Attribute("GroupId");
		if(pstr_GroupId != NULL)
			pData->_GroupId = (UINT16)atoi(pstr_GroupId);
		else
			pData->_GroupId = 0;
		const char* pstr_LevelId = pDataElem->Attribute("LevelId");
		if(pstr_LevelId != NULL)
			pData->_LevelId = (UINT16)atoi(pstr_LevelId);
		else
			pData->_LevelId = 0;
		const char* pstr_MonsterGroup = pDataElem->Attribute("MonsterGroup");
		if(pstr_MonsterGroup != NULL)
			pData->_MonsterGroup = pstr_MonsterGroup;
		else
			pData->_MonsterGroup = "";
		const char* pstr_LootId = pDataElem->Attribute("LootId");
		if(pstr_LootId != NULL)
			pData->_LootId = (UINT16)atoi(pstr_LootId);
		else
			pData->_LootId = 0;
		const char* pstr_RewardReview = pDataElem->Attribute("RewardReview");
		if(pstr_RewardReview != NULL)
			pData->_RewardReview = pstr_RewardReview;
		else
			pData->_RewardReview = "";
		const char* pstr_LootBuff = pDataElem->Attribute("LootBuff");
		if(pstr_LootBuff != NULL)
			pData->_LootBuff = pstr_LootBuff;
		else
			pData->_LootBuff = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


