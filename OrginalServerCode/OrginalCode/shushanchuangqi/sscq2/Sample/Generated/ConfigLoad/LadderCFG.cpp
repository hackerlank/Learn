// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLadderCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LadderCFG.h"
#include "tinyxml.h"

CLadderLoader::~CLadderLoader()
{
	ClearData();
}

void CLadderLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLadderCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLadderLoader::LoadData(const std::string& strPath)
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
		SLadderCFG* pData = new SLadderCFG;
		const char* pstr_RankId = pDataElem->Attribute("RankId");
		if(pstr_RankId != NULL)
			pData->_RankId = (UINT32)atoi(pstr_RankId);
		else
			pData->_RankId = 0;
		const char* pstr_Score = pDataElem->Attribute("Score");
		if(pstr_Score != NULL)
			pData->_Score = (UINT32)atoi(pstr_Score);
		else
			pData->_Score = 0;
		const char* pstr_RankLootId = pDataElem->Attribute("RankLootId");
		if(pstr_RankLootId != NULL)
			pData->_RankLootId = (UINT32)atoi(pstr_RankLootId);
		else
			pData->_RankLootId = 0;
		const char* pstr_RankHighestAward = pDataElem->Attribute("RankHighestAward");
		if(pstr_RankHighestAward != NULL)
			pData->_RankHighestAward = pstr_RankHighestAward;
		else
			pData->_RankHighestAward = "";
		const char* pstr_RobotMonsterId = pDataElem->Attribute("RobotMonsterId");
		if(pstr_RobotMonsterId != NULL)
			pData->_RobotMonsterId = (UINT16)atoi(pstr_RobotMonsterId);
		else
			pData->_RobotMonsterId = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


