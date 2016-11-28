// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFightWordCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "FightWordCFG.h"
#include "tinyxml.h"

CFightWordLoader::~CFightWordLoader()
{
	ClearData();
}

void CFightWordLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SFightWordCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CFightWordLoader::LoadData(const std::string& strPath)
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
		SFightWordCFG* pData = new SFightWordCFG;
		const char* pstr_ResultID = pDataElem->Attribute("ResultID");
		if(pstr_ResultID != NULL)
			pData->_ResultID = (UINT32)atoi(pstr_ResultID);
		else
			pData->_ResultID = 0;
		const char* pstr_Num = pDataElem->Attribute("Num");
		if(pstr_Num != NULL)
			pData->_Num = (UINT32)atoi(pstr_Num);
		else
			pData->_Num = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


