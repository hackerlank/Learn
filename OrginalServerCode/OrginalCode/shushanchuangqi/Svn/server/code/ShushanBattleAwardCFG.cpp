// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShushanBattleAwardCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ShushanBattleAwardCFG.h"
#include "tinyxml.h"

CShushanBattleAwardLoader::~CShushanBattleAwardLoader()
{
	ClearData();
}

void CShushanBattleAwardLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SShushanBattleAwardCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CShushanBattleAwardLoader::LoadData(const std::string& strPath)
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
		SShushanBattleAwardCFG* pData = new SShushanBattleAwardCFG;
		const char* pstr_HonorLevel = pDataElem->Attribute("HonorLevel");
		if(pstr_HonorLevel != NULL)
			pData->_HonorLevel = (UINT8)atoi(pstr_HonorLevel);
		else
			pData->_HonorLevel = 0;
		const char* pstr_Honor = pDataElem->Attribute("Honor");
		if(pstr_Honor != NULL)
			pData->_Honor = (UINT32)atoi(pstr_Honor);
		else
			pData->_Honor = 0;
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


