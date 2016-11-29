// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanKillPrizeCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LingShanKillPrizeCFG.h"
#include "tinyxml.h"

CLingShanKillPrizeLoader::~CLingShanKillPrizeLoader()
{
	ClearData();
}

void CLingShanKillPrizeLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLingShanKillPrizeCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLingShanKillPrizeLoader::LoadData(const std::string& strPath)
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
		SLingShanKillPrizeCFG* pData = new SLingShanKillPrizeCFG;
		const char* pstr_Kills = pDataElem->Attribute("Kills");
		if(pstr_Kills != NULL)
			pData->_Kills = (UINT16)atoi(pstr_Kills);
		else
			pData->_Kills = 0;
		const char* pstr_SuiYuan = pDataElem->Attribute("SuiYuan");
		if(pstr_SuiYuan != NULL)
			pData->_SuiYuan = (UINT16)atoi(pstr_SuiYuan);
		else
			pData->_SuiYuan = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


