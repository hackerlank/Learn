// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCircleTaskCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "CircleTaskCFG.h"
#include "tinyxml.h"

CCircleTaskLoader::~CCircleTaskLoader()
{
	ClearData();
}

void CCircleTaskLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SCircleTaskCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CCircleTaskLoader::LoadData(const std::string& strPath)
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
		SCircleTaskCFG* pData = new SCircleTaskCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT16)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Level_min = pDataElem->Attribute("Level_min");
		if(pstr_Level_min != NULL)
			pData->_Level_min = (UINT16)atoi(pstr_Level_min);
		else
			pData->_Level_min = 0;
		const char* pstr_Level_max = pDataElem->Attribute("Level_max");
		if(pstr_Level_max != NULL)
			pData->_Level_max = (UINT16)atoi(pstr_Level_max);
		else
			pData->_Level_max = 0;
		const char* pstr_Task_ID = pDataElem->Attribute("Task_ID");
		if(pstr_Task_ID != NULL)
			pData->_Task_ID = pstr_Task_ID;
		else
			pData->_Task_ID = "";
		const char* pstr_Chance_Award = pDataElem->Attribute("Chance_Award");
		if(pstr_Chance_Award != NULL)
			pData->_Chance_Award = pstr_Chance_Award;
		else
			pData->_Chance_Award = "";
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		const char* pstr_FinishAward = pDataElem->Attribute("FinishAward");
		if(pstr_FinishAward != NULL)
			pData->_FinishAward = pstr_FinishAward;
		else
			pData->_FinishAward = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


