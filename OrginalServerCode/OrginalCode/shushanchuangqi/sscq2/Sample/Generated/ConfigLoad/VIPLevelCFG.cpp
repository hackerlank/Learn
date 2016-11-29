// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SVIPLevelCFG.cpp
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#include "VIPLevelCFG.h"
#include "tinyxml.h"

CVIPLevelLoader::~CVIPLevelLoader()
{
	ClearData();
}

void CVIPLevelLoader::ClearData()
{
	for(size_t i=0; i<_vecData.size();++i)
	{
		SVIPLevelCFG *p = _vecData[i];
		delete p;
	}
	_vecData.clear();
}

bool CVIPLevelLoader::LoadData(const std::string& strPath)
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
		SVIPLevelCFG* pData = new SVIPLevelCFG;
		const char* pstr_Level = pDataElem->Attribute("Level");
		if(pstr_Level != NULL)
			pData->_Level = (UINT8)atoi(pstr_Level);
		else
			pData->_Level = 0;
		const char* pstr_Exp = pDataElem->Attribute("Exp");
		if(pstr_Exp != NULL)
			pData->_Exp = (UINT32)atoi(pstr_Exp);
		else
			pData->_Exp = 0;
		const char* pstr_DayPack = pDataElem->Attribute("DayPack");
		if(pstr_DayPack != NULL)
			pData->_DayPack = pstr_DayPack;
		else
			pData->_DayPack = "";
		const char* pstr_Award = pDataElem->Attribute("Award");
		if(pstr_Award != NULL)
			pData->_Award = pstr_Award;
		else
			pData->_Award = "";
		const char* pstr_AssetDesc = pDataElem->Attribute("AssetDesc");
		if(pstr_AssetDesc != NULL)
			pData->_AssetDesc = pstr_AssetDesc;
		else
			pData->_AssetDesc = "";
		const char* pstr_Trailertxt = pDataElem->Attribute("Trailertxt");
		if(pstr_Trailertxt != NULL)
			pData->_Trailertxt = pstr_Trailertxt;
		else
			pData->_Trailertxt = "";
		const char* pstr_TrailerItem = pDataElem->Attribute("TrailerItem");
		if(pstr_TrailerItem != NULL)
			pData->_TrailerItem = pstr_TrailerItem;
		else
			pData->_TrailerItem = "";
		const char* pstr_ImageId = pDataElem->Attribute("ImageId");
		if(pstr_ImageId != NULL)
			pData->_ImageId = pstr_ImageId;
		else
			pData->_ImageId = "";
		const char* pstr_StoreNum = pDataElem->Attribute("StoreNum");
		if(pstr_StoreNum != NULL)
			pData->_StoreNum = (UINT16)atoi(pstr_StoreNum);
		else
			pData->_StoreNum = 0;
		const char* pstr_FriendNum = pDataElem->Attribute("FriendNum");
		if(pstr_FriendNum != NULL)
			pData->_FriendNum = (UINT16)atoi(pstr_FriendNum);
		else
			pData->_FriendNum = 0;
		const char* pstr_BossAuto = pDataElem->Attribute("BossAuto");
		if(pstr_BossAuto != NULL)
			pData->_BossAuto = (UINT16)atoi(pstr_BossAuto);
		else
			pData->_BossAuto = 0;
		const char* pstr_ShimenGet = pDataElem->Attribute("ShimenGet");
		if(pstr_ShimenGet != NULL)
			pData->_ShimenGet = (UINT16)atoi(pstr_ShimenGet);
		else
			pData->_ShimenGet = 0;
		const char* pstr_YamenGet = pDataElem->Attribute("YamenGet");
		if(pstr_YamenGet != NULL)
			pData->_YamenGet = (UINT16)atoi(pstr_YamenGet);
		else
			pData->_YamenGet = 0;
		const char* pstr_ShimenTimes = pDataElem->Attribute("ShimenTimes");
		if(pstr_ShimenTimes != NULL)
			pData->_ShimenTimes = (UINT16)atoi(pstr_ShimenTimes);
		else
			pData->_ShimenTimes = 0;
		const char* pstr_YamenTimes = pDataElem->Attribute("YamenTimes");
		if(pstr_YamenTimes != NULL)
			pData->_YamenTimes = (UINT16)atoi(pstr_YamenTimes);
		else
			pData->_YamenTimes = 0;
		const char* pstr_ShiyaLiKe = pDataElem->Attribute("ShiyaLiKe");
		if(pstr_ShiyaLiKe != NULL)
			pData->_ShiyaLiKe = (UINT16)atoi(pstr_ShiyaLiKe);
		else
			pData->_ShiyaLiKe = 0;
		const char* pstr_GuildFireGet = pDataElem->Attribute("GuildFireGet");
		if(pstr_GuildFireGet != NULL)
			pData->_GuildFireGet = (UINT16)atoi(pstr_GuildFireGet);
		else
			pData->_GuildFireGet = 0;
		const char* pstr_Title = pDataElem->Attribute("Title");
		if(pstr_Title != NULL)
			pData->_Title = pstr_Title;
		else
			pData->_Title = "";
		const char* pstr_DailyEnergyBoughtTimes = pDataElem->Attribute("DailyEnergyBoughtTimes");
		if(pstr_DailyEnergyBoughtTimes != NULL)
			pData->_DailyEnergyBoughtTimes = (UINT16)atoi(pstr_DailyEnergyBoughtTimes);
		else
			pData->_DailyEnergyBoughtTimes = 0;
		const char* pstr_SaoDangFree = pDataElem->Attribute("SaoDangFree");
		if(pstr_SaoDangFree != NULL)
			pData->_SaoDangFree = (UINT16)atoi(pstr_SaoDangFree);
		else
			pData->_SaoDangFree = 0;
		const char* pstr_VipDundgnEXP = pDataElem->Attribute("VipDundgnEXP");
		if(pstr_VipDundgnEXP != NULL)
			pData->_VipDundgnEXP = pstr_VipDundgnEXP;
		else
			pData->_VipDundgnEXP = "";
		const char* pstr_VipDundgnXiuwei = pDataElem->Attribute("VipDundgnXiuwei");
		if(pstr_VipDundgnXiuwei != NULL)
			pData->_VipDundgnXiuwei = pstr_VipDundgnXiuwei;
		else
			pData->_VipDundgnXiuwei = "";
		const char* pstr_VipDundgnCailiao = pDataElem->Attribute("VipDundgnCailiao");
		if(pstr_VipDundgnCailiao != NULL)
			pData->_VipDundgnCailiao = pstr_VipDundgnCailiao;
		else
			pData->_VipDundgnCailiao = "";
		const char* pstr_CopyFinishRewardC = pDataElem->Attribute("CopyFinishRewardC");
		if(pstr_CopyFinishRewardC != NULL)
			pData->_CopyFinishRewardC = (UINT16)atoi(pstr_CopyFinishRewardC);
		else
			pData->_CopyFinishRewardC = 0;
		const char* pstr_LilianBuy = pDataElem->Attribute("LilianBuy");
		if(pstr_LilianBuy != NULL)
			pData->_LilianBuy = (UINT16)atoi(pstr_LilianBuy);
		else
			pData->_LilianBuy = 0;
		const char* pstr_LilianCD = pDataElem->Attribute("LilianCD");
		if(pstr_LilianCD != NULL)
			pData->_LilianCD = (UINT16)atoi(pstr_LilianCD);
		else
			pData->_LilianCD = 0;
		const char* pstr_LilianFrush = pDataElem->Attribute("LilianFrush");
		if(pstr_LilianFrush != NULL)
			pData->_LilianFrush = (UINT16)atoi(pstr_LilianFrush);
		else
			pData->_LilianFrush = 0;
		const char* pstr_DoujianCD = pDataElem->Attribute("DoujianCD");
		if(pstr_DoujianCD != NULL)
			pData->_DoujianCD = (UINT16)atoi(pstr_DoujianCD);
		else
			pData->_DoujianCD = 0;
		const char* pstr_SitTimeMax = pDataElem->Attribute("SitTimeMax");
		if(pstr_SitTimeMax != NULL)
			pData->_SitTimeMax = (UINT16)atoi(pstr_SitTimeMax);
		else
			pData->_SitTimeMax = 0;
		const char* pstr_SitAddition = pDataElem->Attribute("SitAddition");
		if(pstr_SitAddition != NULL)
			pData->_SitAddition = (UINT16)atoi(pstr_SitAddition);
		else
			pData->_SitAddition = 0;
		const char* pstr_VIPFormation = pDataElem->Attribute("VIPFormation");
		if(pstr_VIPFormation != NULL)
			pData->_VIPFormation = pstr_VIPFormation;
		else
			pData->_VIPFormation = "";
		const char* pstr_VIPHero = pDataElem->Attribute("VIPHero");
		if(pstr_VIPHero != NULL)
			pData->_VIPHero = pstr_VIPHero;
		else
			pData->_VIPHero = "";
		const char* pstr_VIPPet = pDataElem->Attribute("VIPPet");
		if(pstr_VIPPet != NULL)
			pData->_VIPPet = pstr_VIPPet;
		else
			pData->_VIPPet = "";
		const char* pstr_VIPFation = pDataElem->Attribute("VIPFation");
		if(pstr_VIPFation != NULL)
			pData->_VIPFation = pstr_VIPFation;
		else
			pData->_VIPFation = "";
		const char* pstr_VIPHorse = pDataElem->Attribute("VIPHorse");
		if(pstr_VIPHorse != NULL)
			pData->_VIPHorse = pstr_VIPHorse;
		else
			pData->_VIPHorse = "";
		const char* pstr_VIPTrump = pDataElem->Attribute("VIPTrump");
		if(pstr_VIPTrump != NULL)
			pData->_VIPTrump = pstr_VIPTrump;
		else
			pData->_VIPTrump = "";
		const char* pstr_VIPBeauty = pDataElem->Attribute("VIPBeauty");
		if(pstr_VIPBeauty != NULL)
			pData->_VIPBeauty = pstr_VIPBeauty;
		else
			pData->_VIPBeauty = "";
		const char* pstr_HuoyueAward = pDataElem->Attribute("HuoyueAward");
		if(pstr_HuoyueAward != NULL)
			pData->_HuoyueAward = pstr_HuoyueAward;
		else
			pData->_HuoyueAward = "";
		const char* pstr_Tiaoguozhandou = pDataElem->Attribute("Tiaoguozhandou");
		if(pstr_Tiaoguozhandou != NULL)
			pData->_Tiaoguozhandou = (UINT16)atoi(pstr_Tiaoguozhandou);
		else
			pData->_Tiaoguozhandou = 0;
		const char* pstr_StoveSpeeding = pDataElem->Attribute("StoveSpeeding");
		if(pstr_StoveSpeeding != NULL)
			pData->_StoveSpeeding = (UINT32)atoi(pstr_StoveSpeeding);
		else
			pData->_StoveSpeeding = 0;
		const char* pstr_SignIn = pDataElem->Attribute("SignIn");
		if(pstr_SignIn != NULL)
			pData->_SignIn = (UINT16)atoi(pstr_SignIn);
		else
			pData->_SignIn = 0;
		const char* pstr_BattleArrayTimes = pDataElem->Attribute("BattleArrayTimes");
		if(pstr_BattleArrayTimes != NULL)
			pData->_BattleArrayTimes = (UINT16)atoi(pstr_BattleArrayTimes);
		else
			pData->_BattleArrayTimes = 0;
		const char* pstr_BattleArrayBoughtTimes = pDataElem->Attribute("BattleArrayBoughtTimes");
		if(pstr_BattleArrayBoughtTimes != NULL)
			pData->_BattleArrayBoughtTimes = (UINT16)atoi(pstr_BattleArrayBoughtTimes);
		else
			pData->_BattleArrayBoughtTimes = 0;
		const char* pstr_HeroDungeonFreeTimes = pDataElem->Attribute("HeroDungeonFreeTimes");
		if(pstr_HeroDungeonFreeTimes != NULL)
			pData->_HeroDungeonFreeTimes = (UINT16)atoi(pstr_HeroDungeonFreeTimes);
		else
			pData->_HeroDungeonFreeTimes = 0;
		const char* pstr_HeroDungeonBuyTimes = pDataElem->Attribute("HeroDungeonBuyTimes");
		if(pstr_HeroDungeonBuyTimes != NULL)
			pData->_HeroDungeonBuyTimes = (UINT16)atoi(pstr_HeroDungeonBuyTimes);
		else
			pData->_HeroDungeonBuyTimes = 0;
		const char* pstr_ShipGet = pDataElem->Attribute("ShipGet");
		if(pstr_ShipGet != NULL)
			pData->_ShipGet = (UINT8)atoi(pstr_ShipGet);
		else
			pData->_ShipGet = 0;
		const char* pstr_GuardEMeiTimes = pDataElem->Attribute("GuardEMeiTimes");
		if(pstr_GuardEMeiTimes != NULL)
			pData->_GuardEMeiTimes = (UINT8)atoi(pstr_GuardEMeiTimes);
		else
			pData->_GuardEMeiTimes = 0;
		const char* pstr_GuardEMeiBuyingTimes = pDataElem->Attribute("GuardEMeiBuyingTimes");
		if(pstr_GuardEMeiBuyingTimes != NULL)
			pData->_GuardEMeiBuyingTimes = (UINT8)atoi(pstr_GuardEMeiBuyingTimes);
		else
			pData->_GuardEMeiBuyingTimes = 0;
		const char* pstr_CircleTaskMaxStar = pDataElem->Attribute("CircleTaskMaxStar");
		if(pstr_CircleTaskMaxStar != NULL)
			pData->_CircleTaskMaxStar = (UINT8)atoi(pstr_CircleTaskMaxStar);
		else
			pData->_CircleTaskMaxStar = 0;
		const char* pstr_AdventureDungeonFreeTimes = pDataElem->Attribute("AdventureDungeonFreeTimes");
		if(pstr_AdventureDungeonFreeTimes != NULL)
			pData->_AdventureDungeonFreeTimes = (UINT16)atoi(pstr_AdventureDungeonFreeTimes);
		else
			pData->_AdventureDungeonFreeTimes = 0;
		const char* pstr_AdventureDungeonBuyTimes = pDataElem->Attribute("AdventureDungeonBuyTimes");
		if(pstr_AdventureDungeonBuyTimes != NULL)
			pData->_AdventureDungeonBuyTimes = (UINT16)atoi(pstr_AdventureDungeonBuyTimes);
		else
			pData->_AdventureDungeonBuyTimes = 0;
		const char* pstr_GuardEMeiAutoNoCd = pDataElem->Attribute("GuardEMeiAutoNoCd");
		if(pstr_GuardEMeiAutoNoCd != NULL)
			pData->_GuardEMeiAutoNoCd = (UINT8)atoi(pstr_GuardEMeiAutoNoCd);
		else
			pData->_GuardEMeiAutoNoCd = 0;
		const char* pstr_ArenaNoCd = pDataElem->Attribute("ArenaNoCd");
		if(pstr_ArenaNoCd != NULL)
			pData->_ArenaNoCd = (UINT8)atoi(pstr_ArenaNoCd);
		else
			pData->_ArenaNoCd = 0;
		const char* pstr_ArenaTimes = pDataElem->Attribute("ArenaTimes");
		if(pstr_ArenaTimes != NULL)
			pData->_ArenaTimes = (UINT16)atoi(pstr_ArenaTimes);
		else
			pData->_ArenaTimes = 0;
		const char* pstr_ArenaBoughtTimes = pDataElem->Attribute("ArenaBoughtTimes");
		if(pstr_ArenaBoughtTimes != NULL)
			pData->_ArenaBoughtTimes = (UINT16)atoi(pstr_ArenaBoughtTimes);
		else
			pData->_ArenaBoughtTimes = 0;
		const char* pstr_FreeDrawTimes = pDataElem->Attribute("FreeDrawTimes");
		if(pstr_FreeDrawTimes != NULL)
			pData->_FreeDrawTimes = (UINT16)atoi(pstr_FreeDrawTimes);
		else
			pData->_FreeDrawTimes = 0;
		const char* pstr_MoneyTree = pDataElem->Attribute("MoneyTree");
		if(pstr_MoneyTree != NULL)
			pData->_MoneyTree = (UINT16)atoi(pstr_MoneyTree);
		else
			pData->_MoneyTree = 0;
		const char* pstr_ShipRefresh = pDataElem->Attribute("ShipRefresh");
		if(pstr_ShipRefresh != NULL)
			pData->_ShipRefresh = (UINT8)atoi(pstr_ShipRefresh);
		else
			pData->_ShipRefresh = 0;
		const char* pstr_ShipTime = pDataElem->Attribute("ShipTime");
		if(pstr_ShipTime != NULL)
			pData->_ShipTime = (UINT8)atoi(pstr_ShipTime);
		else
			pData->_ShipTime = 0;
		const char* pstr_RichTime = pDataElem->Attribute("RichTime");
		if(pstr_RichTime != NULL)
			pData->_RichTime = (UINT8)atoi(pstr_RichTime);
		else
			pData->_RichTime = 0;
		const char* pstr_RichCtrlDiceTime = pDataElem->Attribute("RichCtrlDiceTime");
		if(pstr_RichCtrlDiceTime != NULL)
			pData->_RichCtrlDiceTime = (UINT8)atoi(pstr_RichCtrlDiceTime);
		else
			pData->_RichCtrlDiceTime = 0;
		const char* pstr_RichComBackTime = pDataElem->Attribute("RichComBackTime");
		if(pstr_RichComBackTime != NULL)
			pData->_RichComBackTime = (UINT8)atoi(pstr_RichComBackTime);
		else
			pData->_RichComBackTime = 0;
		const char* pstr_RichLife = pDataElem->Attribute("RichLife");
		if(pstr_RichLife != NULL)
			pData->_RichLife = (UINT8)atoi(pstr_RichLife);
		else
			pData->_RichLife = 0;
		_vecData.push_back(pData);
		pDataElem = pDataElem->NextSiblingElement();
	}
	doc.Clear();
	return true;
}


