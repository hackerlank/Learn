// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuardEMeiCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "GuardEMeiCFG.h"
#include "tinyxml.h"

CGuardEMeiLoader::~CGuardEMeiLoader()
{
	ClearData();
}

void CGuardEMeiLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SGuardEMeiCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CGuardEMeiLoader::LoadData(const std::string& strPath)
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
		SGuardEMeiCFG* pData = new SGuardEMeiCFG;
		const char* pstr_LevelId = pDataElem->Attribute("LevelId");
		if(pstr_LevelId != NULL)
			pData->_LevelId = (UINT16)atoi(pstr_LevelId);
		else
			pData->_LevelId = 0;
		const char* pstr_Name = pDataElem->Attribute("Name");
		if(pstr_Name != NULL)
			pData->_Name = pstr_Name;
		else
			pData->_Name = "";
		const char* pstr_NamePic = pDataElem->Attribute("NamePic");
		if(pstr_NamePic != NULL)
			pData->_NamePic = (UINT16)atoi(pstr_NamePic);
		else
			pData->_NamePic = 0;
		const char* pstr_RequiredLevel = pDataElem->Attribute("RequiredLevel");
		if(pstr_RequiredLevel != NULL)
			pData->_RequiredLevel = (UINT16)atoi(pstr_RequiredLevel);
		else
			pData->_RequiredLevel = 0;
		const char* pstr_PreLevel = pDataElem->Attribute("PreLevel");
		if(pstr_PreLevel != NULL)
			pData->_PreLevel = (UINT16)atoi(pstr_PreLevel);
		else
			pData->_PreLevel = 0;
		const char* pstr_RewardReview = pDataElem->Attribute("RewardReview");
		if(pstr_RewardReview != NULL)
			pData->_RewardReview = pstr_RewardReview;
		else
			pData->_RewardReview = "";
		const char* pstr_FinishReward = pDataElem->Attribute("FinishReward");
		if(pstr_FinishReward != NULL)
			pData->_FinishReward = pstr_FinishReward;
		else
			pData->_FinishReward = "";
		const char* pstr_MaxNum = pDataElem->Attribute("MaxNum");
		if(pstr_MaxNum != NULL)
			pData->_MaxNum = (UINT8)atoi(pstr_MaxNum);
		else
			pData->_MaxNum = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


