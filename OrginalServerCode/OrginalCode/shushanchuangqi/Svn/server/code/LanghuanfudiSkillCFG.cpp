// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLanghuanfudiSkillCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "LanghuanfudiSkillCFG.h"
#include "tinyxml.h"

CLanghuanfudiSkillLoader::~CLanghuanfudiSkillLoader()
{
	ClearData();
}

void CLanghuanfudiSkillLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SLanghuanfudiSkillCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CLanghuanfudiSkillLoader::LoadData(const std::string& strPath)
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
		SLanghuanfudiSkillCFG* pData = new SLanghuanfudiSkillCFG;
		const char* pstr_ID = pDataElem->Attribute("ID");
		if(pstr_ID != NULL)
			pData->_ID = (UINT32)atoi(pstr_ID);
		else
			pData->_ID = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_UseTimes = pDataElem->Attribute("UseTimes");
		if(pstr_UseTimes != NULL)
			pData->_UseTimes = (UINT32)atoi(pstr_UseTimes);
		else
			pData->_UseTimes = 0;
		const char* pstr_Distance = pDataElem->Attribute("Distance");
		if(pstr_Distance != NULL)
			pData->_Distance = (UINT16)atoi(pstr_Distance);
		else
			pData->_Distance = 0;
		const char* pstr_CoolDown = pDataElem->Attribute("CoolDown");
		if(pstr_CoolDown != NULL)
			pData->_CoolDown = (UINT16)atoi(pstr_CoolDown);
		else
			pData->_CoolDown = 0;
		const char* pstr_MapId = pDataElem->Attribute("MapId");
		if(pstr_MapId != NULL)
			pData->_MapId = (UINT32)atoi(pstr_MapId);
		else
			pData->_MapId = 0;
		const char* pstr_MeTalk = pDataElem->Attribute("MeTalk");
		if(pstr_MeTalk != NULL)
			pData->_MeTalk = pstr_MeTalk;
		else
			pData->_MeTalk = "";
		const char* pstr_OtherTalk = pDataElem->Attribute("OtherTalk");
		if(pstr_OtherTalk != NULL)
			pData->_OtherTalk = pstr_OtherTalk;
		else
			pData->_OtherTalk = "";
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


