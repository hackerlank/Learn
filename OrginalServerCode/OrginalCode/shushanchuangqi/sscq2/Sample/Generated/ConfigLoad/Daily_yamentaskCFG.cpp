// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_yamentaskCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "Daily_yamentaskCFG.h"
#include "tinyxml.h"

CDaily_yamentaskLoader::~CDaily_yamentaskLoader()
{
	ClearData();
}

void CDaily_yamentaskLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDaily_yamentaskCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDaily_yamentaskLoader::LoadData(const std::string& strPath)
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
		SDaily_yamentaskCFG* pData = new SDaily_yamentaskCFG;
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
		const char* pstr_Task_1 = pDataElem->Attribute("Task_1");
		if(pstr_Task_1 != NULL)
			pData->_Task_1 = pstr_Task_1;
		else
			pData->_Task_1 = "";
		const char* pstr_Task_2 = pDataElem->Attribute("Task_2");
		if(pstr_Task_2 != NULL)
			pData->_Task_2 = pstr_Task_2;
		else
			pData->_Task_2 = "";
		const char* pstr_Task_3 = pDataElem->Attribute("Task_3");
		if(pstr_Task_3 != NULL)
			pData->_Task_3 = pstr_Task_3;
		else
			pData->_Task_3 = "";
		const char* pstr_Task_4 = pDataElem->Attribute("Task_4");
		if(pstr_Task_4 != NULL)
			pData->_Task_4 = pstr_Task_4;
		else
			pData->_Task_4 = "";
		const char* pstr_Task_5 = pDataElem->Attribute("Task_5");
		if(pstr_Task_5 != NULL)
			pData->_Task_5 = pstr_Task_5;
		else
			pData->_Task_5 = "";
		const char* pstr_Task_ID = pDataElem->Attribute("Task_ID");
		if(pstr_Task_ID != NULL)
			pData->_Task_ID = pstr_Task_ID;
		else
			pData->_Task_ID = "";
		const char* pstr_Descripition = pDataElem->Attribute("Descripition");
		if(pstr_Descripition != NULL)
			pData->_Descripition = pstr_Descripition;
		else
			pData->_Descripition = "";
		const char* pstr_Chance_Award = pDataElem->Attribute("Chance_Award");
		if(pstr_Chance_Award != NULL)
			pData->_Chance_Award = pstr_Chance_Award;
		else
			pData->_Chance_Award = "";
		const char* pstr_Chance_Award_Gold = pDataElem->Attribute("Chance_Award_Gold");
		if(pstr_Chance_Award_Gold != NULL)
			pData->_Chance_Award_Gold = pstr_Chance_Award_Gold;
		else
			pData->_Chance_Award_Gold = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


