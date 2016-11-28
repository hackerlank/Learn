// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShushanBattleTaskCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ShushanBattleTaskCFG.h"
#include "tinyxml.h"

CShushanBattleTaskLoader::~CShushanBattleTaskLoader()
{
	ClearData();
}

void CShushanBattleTaskLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SShushanBattleTaskCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CShushanBattleTaskLoader::LoadData(const std::string& strPath)
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
		SShushanBattleTaskCFG* pData = new SShushanBattleTaskCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Degree = pDataElem->Attribute("Degree");
		if(pstr_Degree != NULL)
			pData->_Degree = (UINT8)atoi(pstr_Degree);
		else
			pData->_Degree = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = (UINT16)atoi(pstr_Award);
		else
			pData->_Award = 0;
		const char* pstr_Gradation = pDataElem->Attribute("Gradation");
		if(pstr_Gradation != NULL)
			pData->_Gradation = (UINT8)atoi(pstr_Gradation);
		else
			pData->_Gradation = 0;
		const char* pstr_Tip = pDataElem->Attribute("Tip");
		if(pstr_Tip != NULL)
			pData->_Tip = pstr_Tip;
		else
			pData->_Tip = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


