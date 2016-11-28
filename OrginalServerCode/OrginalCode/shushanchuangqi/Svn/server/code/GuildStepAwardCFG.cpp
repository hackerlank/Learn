// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildStepAwardCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuildStepAwardCFG.h"
#include "tinyxml.h"

CGuildStepAwardLoader::~CGuildStepAwardLoader()
{
	ClearData();
}

void CGuildStepAwardLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuildStepAwardCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuildStepAwardLoader::LoadData(const std::string& strPath)
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
		SGuildStepAwardCFG* pData = new SGuildStepAwardCFG;
		const char* pstr_AwardLevel = pDataElem->Attribute("AwardLevel");
		if(pstr_AwardLevel != NULL)
			pData->_AwardLevel = (UINT8)atoi(pstr_AwardLevel);
		else
			pData->_AwardLevel = 0;
		const char* pstr_GuildStep = pDataElem->Attribute("GuildStep");
		if(pstr_GuildStep != NULL)
			pData->_GuildStep = pstr_GuildStep;
		else
			pData->_GuildStep = "";
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


