// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFormationBreakCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FormationBreakCFG.h"
#include "tinyxml.h"

CFormationBreakLoader::~CFormationBreakLoader()
{
	ClearData();
}

void CFormationBreakLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFormationBreakCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFormationBreakLoader::LoadData(const std::string& strPath)
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
		SFormationBreakCFG* pData = new SFormationBreakCFG;
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
		const char* pstr_RequiredLevel = pDataElem->Attribute("RequiredLevel");
		if(pstr_RequiredLevel != NULL)
			pData->_RequiredLevel = (UINT8)atoi(pstr_RequiredLevel);
		else
			pData->_RequiredLevel = 0;
		const char* pstr_MonsterTeam = pDataElem->Attribute("MonsterTeam");
		if(pstr_MonsterTeam != NULL)
			pData->_MonsterTeam = pstr_MonsterTeam;
		else
			pData->_MonsterTeam = "";
		const char* pstr_Reward = pDataElem->Attribute("Reward");
		if(pstr_Reward != NULL)
			pData->_Reward = pstr_Reward;
		else
			pData->_Reward = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


