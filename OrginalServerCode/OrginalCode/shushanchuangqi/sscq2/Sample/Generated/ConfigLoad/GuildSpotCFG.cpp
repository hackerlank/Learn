// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildSpotCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildSpotCFG.h"
#include "tinyxml.h"

CGuildSpotLoader::~CGuildSpotLoader()
{
	ClearData();
}

void CGuildSpotLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildSpotCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildSpotLoader::LoadData(const std::string& strPath)
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
		SGuildSpotCFG* pData = new SGuildSpotCFG;
		const char* pstr_Id = pDataElem->Attribute("Id");
		if(pstr_Id != NULL)
			pData->_Id = (UINT8)atoi(pstr_Id);
		else
			pData->_Id = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_Score = pDataElem->Attribute("Score");
		if(pstr_Score != NULL)
			pData->_Score = (UINT8)atoi(pstr_Score);
		else
			pData->_Score = 0;
		const char* pstr_MaxNum = pDataElem->Attribute("MaxNum");
		if(pstr_MaxNum != NULL)
			pData->_MaxNum = (UINT8)atoi(pstr_MaxNum);
		else
			pData->_MaxNum = 0;
		const char* pstr_MapId = pDataElem->Attribute("MapId");
		if(pstr_MapId != NULL)
			pData->_MapId = (UINT32)atoi(pstr_MapId);
		else
			pData->_MapId = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


