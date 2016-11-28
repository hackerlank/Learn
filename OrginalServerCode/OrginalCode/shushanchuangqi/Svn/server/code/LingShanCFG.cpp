// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LingShanCFG.h"
#include "tinyxml.h"

CLingShanLoader::~CLingShanLoader()
{
	ClearData();
}

void CLingShanLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLingShanCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLingShanLoader::LoadData(const std::string& strPath)
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
		SLingShanCFG* pData = new SLingShanCFG;
		const char* pstr_ActID = pDataElem->Attribute("ActID");
		if(pstr_ActID != NULL)
			pData->_ActID = (UINT16)atoi(pstr_ActID);
		else
			pData->_ActID = 0;
		const char* pstr_MapID = pDataElem->Attribute("MapID");
		if(pstr_MapID != NULL)
			pData->_MapID = (UINT16)atoi(pstr_MapID);
		else
			pData->_MapID = 0;
		const char* pstr_BornID = pDataElem->Attribute("BornID");
		if(pstr_BornID != NULL)
			pData->_BornID = pstr_BornID;
		else
			pData->_BornID = "";
		const char* pstr_InitPlayerCnt = pDataElem->Attribute("InitPlayerCnt");
		if(pstr_InitPlayerCnt != NULL)
			pData->_InitPlayerCnt = (UINT16)atoi(pstr_InitPlayerCnt);
		else
			pData->_InitPlayerCnt = 0;
		const char* pstr_TotalPlayerCnt = pDataElem->Attribute("TotalPlayerCnt");
		if(pstr_TotalPlayerCnt != NULL)
			pData->_TotalPlayerCnt = (UINT16)atoi(pstr_TotalPlayerCnt);
		else
			pData->_TotalPlayerCnt = 0;
		const char* pstr_SpawPlayerTurns = pDataElem->Attribute("SpawPlayerTurns");
		if(pstr_SpawPlayerTurns != NULL)
			pData->_SpawPlayerTurns = (UINT16)atoi(pstr_SpawPlayerTurns);
		else
			pData->_SpawPlayerTurns = 0;
		const char* pstr_SpawPlayerCnt = pDataElem->Attribute("SpawPlayerCnt");
		if(pstr_SpawPlayerCnt != NULL)
			pData->_SpawPlayerCnt = (UINT16)atoi(pstr_SpawPlayerCnt);
		else
			pData->_SpawPlayerCnt = 0;
		const char* pstr_SpawBoxTurns = pDataElem->Attribute("SpawBoxTurns");
		if(pstr_SpawBoxTurns != NULL)
			pData->_SpawBoxTurns = (UINT16)atoi(pstr_SpawBoxTurns);
		else
			pData->_SpawBoxTurns = 0;
		const char* pstr_BornBigID = pDataElem->Attribute("BornBigID");
		if(pstr_BornBigID != NULL)
			pData->_BornBigID = (UINT16)atoi(pstr_BornBigID);
		else
			pData->_BornBigID = 0;
		const char* pstr_GodBoxID = pDataElem->Attribute("GodBoxID");
		if(pstr_GodBoxID != NULL)
			pData->_GodBoxID = (UINT32)atoi(pstr_GodBoxID);
		else
			pData->_GodBoxID = 0;
		const char* pstr_GodBoxModelID = pDataElem->Attribute("GodBoxModelID");
		if(pstr_GodBoxModelID != NULL)
			pData->_GodBoxModelID = (UINT16)atoi(pstr_GodBoxModelID);
		else
			pData->_GodBoxModelID = 0;
		const char* pstr_NormalBoxID = pDataElem->Attribute("NormalBoxID");
		if(pstr_NormalBoxID != NULL)
			pData->_NormalBoxID = (UINT32)atoi(pstr_NormalBoxID);
		else
			pData->_NormalBoxID = 0;
		const char* pstr_NormalBoxModelID = pDataElem->Attribute("NormalBoxModelID");
		if(pstr_NormalBoxModelID != NULL)
			pData->_NormalBoxModelID = (UINT16)atoi(pstr_NormalBoxModelID);
		else
			pData->_NormalBoxModelID = 0;
		const char* pstr_PlayAward = pDataElem->Attribute("PlayAward");
		if(pstr_PlayAward != NULL)
			pData->_PlayAward = pstr_PlayAward;
		else
			pData->_PlayAward = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


