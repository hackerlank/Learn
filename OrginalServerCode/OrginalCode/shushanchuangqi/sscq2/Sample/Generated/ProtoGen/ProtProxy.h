/************************************************************************
//  工具自动生成的协议转发类型代码文件
//  File Name:    ProtocolProxy.h
//  Purpose:      定义协议转发类型，网关服务器用
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once

const UINT8 arProtGameServer[] = { //转发到GameServer的协议
	5, //MapProt
	11, //RoleEvent
	13, //GameSvrBasic
	14, //NpcProt
	15, //TaskProt
	17, //PropInfo
	18, //ItemProt
	20, //FighterProt
	21, //BattleGS
	22, //FormationProt
	23, //ChatProt
	25, //BossProt
	27, //MallProt
	30, //EquipTrumpProt
	51, //GroupTaskProt
	52, //YaMenTaskProt
	53, //ActivityProt
	54, //TitleProt
	55, //SittingProt
	58, //CompareBattlePoint
	59, //DungeonProt
	60, //GatherProt
	65, //VIPProt
	66, //ShushanBattleProt
	68, //NewGuildBattleProt
	69, //DayActProt
	70, //DemonTower
	72, //MiscProt
	74, //Horse
	75, //AchievementProt
	76, //GuildBattleProt
	78, //CollectionProt
	79, //LangHuanBlessProt
	82, //ViewInfoProt
	83, //SignProt
	85, //TreasureHuntProt
	86, //GuardEMeiProt
	88, //MoneyTreeProt
	89, //RegisterSevenDaysProt
	91, //CoinProt
	92, //LoginPkgProt
	93, //ShushanweiweiProt
	98, //ShengLingProt
	101, //ExchangeShopProt
	121, //LevelPrize
	125, //DayTarget
	130, //BattleArray
	131, //Beauty
	132, //FightFormation
	135, //LingShanProt
	144, //FeedBackProt
	200, //YelloDiamondProt
};

const UINT8 arProtCenterServer[] = { //转发到CenterServer的协议
	16, //GuildProt
	19, //MailProt
	24, //FriendProt
	26, //ArenaGS
	28, //GlobalChatProt
	56, //TeamGS
	63, //TripodProt
	71, //DemonTowerGS
	80, //RankProt
	84, //ShipProt
	90, //PHPProt
	94, //CenterMiscProt
	95, //AnswerProt
	96, //GodMonsterProt
	97, //ActivityIDProt
	133, //BeautyLogGS
	134, //InviteGS
	199, //WonderActivityProt
};

const UINT8 arProtDBServer[] = { //转发到DBServer的协议
	3, //RoleEnterGameProt
};
