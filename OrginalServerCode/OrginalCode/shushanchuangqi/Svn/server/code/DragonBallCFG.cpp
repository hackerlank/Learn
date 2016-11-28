// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDragonBallCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "DragonBallCFG.h"
#include "tinyxml.h"

CDragonBallLoader::~CDragonBallLoader()
{
	ClearData();
}

void CDragonBallLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SDragonBallCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CDragonBallLoader::LoadData(const std::string& strPath)
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
		SDragonBallCFG* pData = new SDragonBallCFG;
		const char* pstr_cid = pDataElem->Attribute("cid");
		if(pstr_cid != NULL)
			pData->_cid = (UINT16)atoi(pstr_cid);
		else
			pData->_cid = 0;
		const char* pstr_Daytime = pDataElem->Attribute("Daytime");
		if(pstr_Daytime != NULL)
			pData->_Daytime = (UINT8)atoi(pstr_Daytime);
		else
			pData->_Daytime = 0;
		const char* pstr_Fanl = pDataElem->Attribute("Fanl");
		if(pstr_Fanl != NULL)
			pData->_Fanl = (UINT8)atoi(pstr_Fanl);
		else
			pData->_Fanl = 0;
		const char* pstr_Cost = pDataElem->Attribute("Cost");
		if(pstr_Cost != NULL)
			pData->_Cost = (UINT32)atoi(pstr_Cost);
		else
			pData->_Cost = 0;
		const char* pstr_Desc = pDataElem->Attribute("Desc");
		if(pstr_Desc != NULL)
			pData->_Desc = pstr_Desc;
		else
			pData->_Desc = "";
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


