// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExaminationAwardCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "ExaminationAwardCFG.h"
#include "tinyxml.h"

CExaminationAwardLoader::~CExaminationAwardLoader()
{
	ClearData();
}

void CExaminationAwardLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SExaminationAwardCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CExaminationAwardLoader::LoadData(const std::string& strPath)
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
		SExaminationAwardCFG* pData = new SExaminationAwardCFG;
		const char* pstr_RankTop = pDataElem->Attribute("RankTop");
		if(pstr_RankTop != NULL)
			pData->_RankTop = (UINT16)atoi(pstr_RankTop);
		else
			pData->_RankTop = 0;
		const char* pstr_RankBottom = pDataElem->Attribute("RankBottom");
		if(pstr_RankBottom != NULL)
			pData->_RankBottom = (UINT16)atoi(pstr_RankBottom);
		else
			pData->_RankBottom = 0;
		const char* pstr_PrizeType = pDataElem->Attribute("PrizeType");
		if(pstr_PrizeType != NULL)
			pData->_PrizeType = (UINT16)atoi(pstr_PrizeType);
		else
			pData->_PrizeType = 0;
		const char* pstr_GivenItem = pDataElem->Attribute("GivenItem");
		if(pstr_GivenItem != NULL)
			pData->_GivenItem = pstr_GivenItem;
		else
			pData->_GivenItem = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


