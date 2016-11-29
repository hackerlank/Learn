// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdljiuyidinglevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ComdljiuyidinglevelCFG.h"
#include "tinyxml.h"

CComdljiuyidinglevelLoader::~CComdljiuyidinglevelLoader()
{
	ClearData();
}

void CComdljiuyidinglevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SComdljiuyidinglevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CComdljiuyidinglevelLoader::LoadData(const std::string& strPath)
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
		SComdljiuyidinglevelCFG* pData = new SComdljiuyidinglevelCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Experience = pDataElem->Attribute("Experience");
		if(pstr_Experience != NULL)
			pData->_Experience = (UINT32)atoi(pstr_Experience);
		else
			pData->_Experience = 0;
		const char* pstr_Activaterecipe = pDataElem->Attribute("Activaterecipe");
		if(pstr_Activaterecipe != NULL)
			pData->_Activaterecipe = pstr_Activaterecipe;
		else
			pData->_Activaterecipe = "";
		const char* pstr_Outputincrease = pDataElem->Attribute("Outputincrease");
		if(pstr_Outputincrease != NULL)
			pData->_Outputincrease = (UINT8)atoi(pstr_Outputincrease);
		else
			pData->_Outputincrease = 0;
		const char* pstr_Yuanqireduce = pDataElem->Attribute("Yuanqireduce");
		if(pstr_Yuanqireduce != NULL)
			pData->_Yuanqireduce = (UINT8)atoi(pstr_Yuanqireduce);
		else
			pData->_Yuanqireduce = 0;
		const char* pstr_Lifeincrease = pDataElem->Attribute("Lifeincrease");
		if(pstr_Lifeincrease != NULL)
			pData->_Lifeincrease = (UINT16)atoi(pstr_Lifeincrease);
		else
			pData->_Lifeincrease = 0;
		const char* pstr_Expincrease = pDataElem->Attribute("Expincrease");
		if(pstr_Expincrease != NULL)
			pData->_Expincrease = (UINT8)atoi(pstr_Expincrease);
		else
			pData->_Expincrease = 0;
		const char* pstr_Attackincrease = pDataElem->Attribute("Attackincrease");
		if(pstr_Attackincrease != NULL)
			pData->_Attackincrease = (UINT16)atoi(pstr_Attackincrease);
		else
			pData->_Attackincrease = 0;
		const char* pstr_Armorincrease = pDataElem->Attribute("Armorincrease");
		if(pstr_Armorincrease != NULL)
			pData->_Armorincrease = (UINT16)atoi(pstr_Armorincrease);
		else
			pData->_Armorincrease = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


