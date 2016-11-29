// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildBattlePosCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildBattlePosCFG.h"
#include "tinyxml.h"

CGuildBattlePosLoader::~CGuildBattlePosLoader()
{
	ClearData();
}

void CGuildBattlePosLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildBattlePosCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildBattlePosLoader::LoadData(const std::string& strPath)
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
		SGuildBattlePosCFG* pData = new SGuildBattlePosCFG;
		const char* pstr_Id = pDataElem->Attribute("Id");
		if(pstr_Id != NULL)
			pData->_Id = (UINT8)atoi(pstr_Id);
		else
			pData->_Id = 0;
		const char* pstr_PosX = pDataElem->Attribute("PosX");
		if(pstr_PosX != NULL)
			pData->_PosX = (UINT16)atoi(pstr_PosX);
		else
			pData->_PosX = 0;
		const char* pstr_PosY = pDataElem->Attribute("PosY");
		if(pstr_PosY != NULL)
			pData->_PosY = (UINT16)atoi(pstr_PosY);
		else
			pData->_PosY = 0;
		const char* pstr_direction = pDataElem->Attribute("direction");
		if(pstr_direction != NULL)
			pData->_direction = (UINT16)atoi(pstr_direction);
		else
			pData->_direction = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


