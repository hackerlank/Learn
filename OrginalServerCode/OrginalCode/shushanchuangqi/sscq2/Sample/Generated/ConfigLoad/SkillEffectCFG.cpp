// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillEffectCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "SkillEffectCFG.h"
#include "tinyxml.h"

CSkillEffectLoader::~CSkillEffectLoader()
{
	ClearData();
}

void CSkillEffectLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SSkillEffectCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CSkillEffectLoader::LoadData(const std::string& strPath)
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
		SSkillEffectCFG* pData = new SSkillEffectCFG;
		const char* pstr_id = pDataElem->Attribute("id");
		if(pstr_id != NULL)
			pData->_id = (UINT32)atoi(pstr_id);
		else
			pData->_id = 0;
		const char* pstr_name = pDataElem->Attribute("name");
		if(pstr_name != NULL)
			pData->_name = pstr_name;
		else
			pData->_name = "";
		const char* pstr_buffName = pDataElem->Attribute("buffName");
		if(pstr_buffName != NULL)
			pData->_buffName = pstr_buffName;
		else
			pData->_buffName = "";
		const char* pstr_skillCostType = pDataElem->Attribute("skillCostType");
		if(pstr_skillCostType != NULL)
			pData->_skillCostType = (UINT16)atoi(pstr_skillCostType);
		else
			pData->_skillCostType = 0;
		const char* pstr_skillCost = pDataElem->Attribute("skillCost");
		if(pstr_skillCost != NULL)
			pData->_skillCost = (UINT32)atoi(pstr_skillCost);
		else
			pData->_skillCost = 0;
		const char* pstr_needLvl = pDataElem->Attribute("needLvl");
		if(pstr_needLvl != NULL)
			pData->_needLvl = (UINT8)atoi(pstr_needLvl);
		else
			pData->_needLvl = 0;
		const char* pstr_cd = pDataElem->Attribute("cd");
		if(pstr_cd != NULL)
			pData->_cd = (INT32)atoi(pstr_cd);
		else
			pData->_cd = 0;
		const char* pstr_rate = pDataElem->Attribute("rate");
		if(pstr_rate != NULL)
			pData->_rate = (UINT16)atoi(pstr_rate);
		else
			pData->_rate = 0;
		const char* pstr_condRate = pDataElem->Attribute("condRate");
		if(pstr_condRate != NULL)
			pData->_condRate = (UINT16)atoi(pstr_condRate);
		else
			pData->_condRate = 0;
		const char* pstr_cond = pDataElem->Attribute("cond");
		if(pstr_cond != NULL)
			pData->_cond = (UINT16)atoi(pstr_cond);
		else
			pData->_cond = 0;
		const char* pstr_condstr = pDataElem->Attribute("condstr");
		if(pstr_condstr != NULL)
			pData->_condstr = pstr_condstr;
		else
			pData->_condstr = "";
		const char* pstr_condCD = pDataElem->Attribute("condCD");
		if(pstr_condCD != NULL)
			pData->_condCD = (UINT8)atoi(pstr_condCD);
		else
			pData->_condCD = 0;
		const char* pstr_outCond = pDataElem->Attribute("outCond");
		if(pstr_outCond != NULL)
			pData->_outCond = (UINT16)atoi(pstr_outCond);
		else
			pData->_outCond = 0;
		const char* pstr_outCondcondstr = pDataElem->Attribute("outCondcondstr");
		if(pstr_outCondcondstr != NULL)
			pData->_outCondcondstr = pstr_outCondcondstr;
		else
			pData->_outCondcondstr = "";
		const char* pstr_outCD = pDataElem->Attribute("outCD");
		if(pstr_outCD != NULL)
			pData->_outCD = (UINT8)atoi(pstr_outCD);
		else
			pData->_outCD = 0;
		const char* pstr_turnNumber = pDataElem->Attribute("turnNumber");
		if(pstr_turnNumber != NULL)
			pData->_turnNumber = (UINT8)atoi(pstr_turnNumber);
		else
			pData->_turnNumber = 0;
		const char* pstr_last = pDataElem->Attribute("last");
		if(pstr_last != NULL)
			pData->_last = (UINT8)atoi(pstr_last);
		else
			pData->_last = 0;
		const char* pstr_gpId = pDataElem->Attribute("gpId");
		if(pstr_gpId != NULL)
			pData->_gpId = (UINT16)atoi(pstr_gpId);
		else
			pData->_gpId = 0;
		const char* pstr_area = pDataElem->Attribute("area");
		if(pstr_area != NULL)
			pData->_area = (UINT16)atoi(pstr_area);
		else
			pData->_area = 0;
		const char* pstr_type = pDataElem->Attribute("type");
		if(pstr_type != NULL)
			pData->_type = (UINT16)atoi(pstr_type);
		else
			pData->_type = 0;
		const char* pstr_resist = pDataElem->Attribute("resist");
		if(pstr_resist != NULL)
			pData->_resist = (UINT8)atoi(pstr_resist);
		else
			pData->_resist = 0;
		const char* pstr_value1 = pDataElem->Attribute("value1");
		if(pstr_value1 != NULL)
			pData->_value1 = (UINT32)atoi(pstr_value1);
		else
			pData->_value1 = 0;
		const char* pstr_value2 = pDataElem->Attribute("value2");
		if(pstr_value2 != NULL)
			pData->_value2 = (UINT32)atoi(pstr_value2);
		else
			pData->_value2 = 0;
		const char* pstr_value3 = pDataElem->Attribute("value3");
		if(pstr_value3 != NULL)
			pData->_value3 = (UINT32)atoi(pstr_value3);
		else
			pData->_value3 = 0;
		const char* pstr_buffID = pDataElem->Attribute("buffID");
		if(pstr_buffID != NULL)
			pData->_buffID = pstr_buffID;
		else
			pData->_buffID = "";
		const char* pstr_battlePoint = pDataElem->Attribute("battlePoint");
		if(pstr_battlePoint != NULL)
			pData->_battlePoint = (UINT32)atoi(pstr_battlePoint);
		else
			pData->_battlePoint = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


