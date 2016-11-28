// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SV3TaskCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "V3TaskCFG.h"
#include "tinyxml.h"

CV3TaskLoader::~CV3TaskLoader()
{
	ClearData();
}

void CV3TaskLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SV3TaskCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CV3TaskLoader::LoadData(const std::string& strPath)
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
		SV3TaskCFG* pData = new SV3TaskCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_TaskID = pDataElem->Attribute("TaskID");
		if(pstr_TaskID != NULL)
			pData->_TaskID = (UINT32)atoi(pstr_TaskID);
		else
			pData->_TaskID = 0;
		const char* pstr_TaskName = pDataElem->Attribute("TaskName");
		if(pstr_TaskName != NULL)
			pData->_TaskName = pstr_TaskName;
		else
			pData->_TaskName = "";
		const char* pstr_StepID = pDataElem->Attribute("StepID");
		if(pstr_StepID != NULL)
			pData->_StepID = (UINT8)atoi(pstr_StepID);
		else
			pData->_StepID = 0;
		const char* pstr_PrizeID = pDataElem->Attribute("PrizeID");
		if(pstr_PrizeID != NULL)
			pData->_PrizeID = (UINT32)atoi(pstr_PrizeID);
		else
			pData->_PrizeID = 0;
		const char* pstr_PrizeName = pDataElem->Attribute("PrizeName");
		if(pstr_PrizeName != NULL)
			pData->_PrizeName = pstr_PrizeName;
		else
			pData->_PrizeName = "";
		const char* pstr_CondID = pDataElem->Attribute("CondID");
		if(pstr_CondID != NULL)
			pData->_CondID = (UINT32)atoi(pstr_CondID);
		else
			pData->_CondID = 0;
		const char* pstr_CondName = pDataElem->Attribute("CondName");
		if(pstr_CondName != NULL)
			pData->_CondName = pstr_CondName;
		else
			pData->_CondName = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


