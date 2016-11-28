/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    RoleDataInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import net.protocol.fighterProt.SFighterDBInfo;
	import net.protocol.fighterProt.SSkillDBInfo;
	import net.protocol.fighterProt.SPassiveSkillDBInfo;
	import net.protocol.fighterProt.SFighterCombination;
	import net.protocol.itemProt.SItem;
	import net.protocol.friendProt.SFriendDBInfo;
	import net.protocol.tripodProt.SFireInfo;
	import net.protocol.protoCommon.SDBBuffInfo;
	import net.protocol.horse.SHorseDB;
	import net.protocol.achievementProt.SAchievementInfo;
	import net.protocol.collectionProt.SCollectionInfo;
	import net.protocol.demonTower.SRoleAttaked;
	import net.protocol.exchangeShopProt.ExchangeInfo;
	import net.protocol.dungeonProt.SSweepInfo;
	import net.protocol.fighterProt.SXinFaDBInfo;
	import net.protocol.levelPrize.SPrize2DB;
	import net.protocol.protoCommon.SPlatformParam;
	import net.protocol.treasureHuntProt.STHDBInfo;
	import net.protocol.beauty.SBeauty;
	import net.protocol.shipProt.PlayerSelfShipData;
	import net.protocol.shipProt.ShipReport;
	import net.protocol.guardEMeiProt.SGEMDBInfo;
	import net.protocol.shengLingProt.SShengLingInfo2DB;
	import net.protocol.shengLingProt.SShengLingPrize2DB;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家整体数据
	 */
	public final class RoleDataInfo
	{
		public var qwRoleId:BigInteger; //(无符号64位整数)玩家RoleId
		public var stBaseInfo:RoleBaseInfo; //玩家基本数据成员
		public var vecFighterInfo:Vector.<SFighterDBInfo>; //将信息
		public var vecSkillInfo:Vector.<SSkillDBInfo>; //将技能信息
		public var vecPassiveSkillInfo:Vector.<SPassiveSkillDBInfo>; //将技能信息
		public var vecFighterCombination:Vector.<SFighterCombination>; //玩家的散仙组合信息
		public var vecRoleItemInfo:Vector.<SItem>; //玩家物品成员
		public var vecFriendsInfo:Vector.<SFriendDBInfo>; //好友信息
		public var vecRoleDgnInfo:Vector.<RoleDgnInfo>; //玩家副本信息
		public var vecRoleTaskInfo:Vector.<RoleTaskInfo>; //玩家任务信息
		public var vecGameVars:Vector.<SVarsDBInfo>; //玩家身上Game上的变量任务信息
		public var vecRoleSlotsInfo:Vector.<SRoleSlotsInfo>; //玩家身上的槽的信息
		public var vecFormationInfo:Vector.<SFormationInfo>; //玩家的阵形信息
		public var vecPetDataInfo:Vector.<SPetDataInfo>; //玩家的阵灵信息
		public var oRolePetInfo:SRolePetInfo; //玩家的阵形全局信息
		public var vecBeastSoulInfo:Vector.<SBeastSoulInfo>; //玩家的兽魂信息
		public var vecFireInfo:Vector.<SFireInfo>; //玩家九疑鼎的火种信息
		public var vecArenaInfo:Vector.<SRoleArenaInfo>; //玩家斗剑信息
		public var vecDBBuffInfo:Vector.<SDBBuffInfo>; //玩家Buff信息
		public var vecSoulSpaceInfo:Vector.<SSoulSpaceInfo>; //玩家魄空间信息
		public var vecBubbleInfo:Vector.<SDBBubbleInfo>; //玩家气泡信息
		public var vecHorseDB:Vector.<SHorseDB>; //玩家魄坐骑信息
		public var sGroupInfo:SGroupTaskInfo; //师门任务信息
		public var sYaMenInfo:SYaMenTaskInfo; //衙门任务信息
		public var vecActivityTask:Vector.<SActivityTaskInfo>; //活跃度任务信息
		public var vecTitle:Vector.<STitle>; //称号信息
		public var vecAchievementInfo:Vector.<SAchievementInfo>; //成就信息
		public var vecCollectionInfo:Vector.<SCollectionInfo>; //收藏信息
		public var vecRoleAttaked:Vector.<SRoleAttaked>; //玩家被攻击信息列表
		public var vecExchangeInfo:Vector.<ExchangeInfo>; //玩家兑换信息列表
		public var vecSweepInfo:Vector.<SSweepInfo>; //玩家兑换信息列表
		public var vecPendRes:Vector.<SPendRes>; //玩家暂存资源列表
		public var vecXinFaDBInfo:Vector.<SXinFaDBInfo>; //玩家心法信息
		public var vecLevelPrize:Vector.<SPrize2DB>; //玩家条件奖励信息
		public var vecPlatformParam:Vector.<SPlatformParam>; //玩家平台信息
		public var vecEventInfo:Vector.<SEventInfo>; //事件信息
		public var vecEventOffLine:Vector.<SEventOffLine>; //离线事件
		public var vecBuyItemDBInfo:Vector.<SBuyItemDBInfo>; //商品购买数量
		public var vecDayTargetDBInfo:Vector.<SDayTargetDBInfo>; //7日目标活动信息
		public var vecBattleArrayDBInfo:Vector.<SBattleArrayDBInfo>; //破阵信息
		public var vecAutoStoreDBInfo:Vector.<SAutoStoreDBInfo>; //动态存储信息
		public var vecTHDBInfo:Vector.<STHDBInfo>; //玩家寻宝信息
		public var vecBeauty:Vector.<SBeauty>; //美女信息
		public var vecFightFormationDBInfo:Vector.<SFightFormationDBInfo>; //新阵型信息
		public var vecFightHeroDBInfo:Vector.<SFightHeroDBInfo>; //战斗散仙数据
		public var sShipData:PlayerSelfShipData; //自己运船信息
		public var vecShipReport:Vector.<ShipReport>; //战报信息
		public var vecGEMDBInfo:Vector.<SGEMDBInfo>; //玩家守卫峨眉信息
		public var vecShengLing:Vector.<SShengLingInfo2DB>; //玩家圣陵信息
		public var vecShengLingPrize:Vector.<SShengLingPrize2DB>; //玩家圣陵奖励

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleId:BigInteger, stBaseInfo:RoleBaseInfo, vecFighterInfo:Vector.<SFighterDBInfo>, vecSkillInfo:Vector.<SSkillDBInfo>, vecPassiveSkillInfo:Vector.<SPassiveSkillDBInfo>, 
			vecFighterCombination:Vector.<SFighterCombination>, vecRoleItemInfo:Vector.<SItem>, vecFriendsInfo:Vector.<SFriendDBInfo>, vecRoleDgnInfo:Vector.<RoleDgnInfo>, vecRoleTaskInfo:Vector.<RoleTaskInfo>, 
			vecGameVars:Vector.<SVarsDBInfo>, vecRoleSlotsInfo:Vector.<SRoleSlotsInfo>, vecFormationInfo:Vector.<SFormationInfo>, vecPetDataInfo:Vector.<SPetDataInfo>, oRolePetInfo:SRolePetInfo, 
			vecBeastSoulInfo:Vector.<SBeastSoulInfo>, vecFireInfo:Vector.<SFireInfo>, vecArenaInfo:Vector.<SRoleArenaInfo>, vecDBBuffInfo:Vector.<SDBBuffInfo>, vecSoulSpaceInfo:Vector.<SSoulSpaceInfo>, 
			vecBubbleInfo:Vector.<SDBBubbleInfo>, vecHorseDB:Vector.<SHorseDB>, sGroupInfo:SGroupTaskInfo, sYaMenInfo:SYaMenTaskInfo, vecActivityTask:Vector.<SActivityTaskInfo>, 
			vecTitle:Vector.<STitle>, vecAchievementInfo:Vector.<SAchievementInfo>, vecCollectionInfo:Vector.<SCollectionInfo>, vecRoleAttaked:Vector.<SRoleAttaked>, vecExchangeInfo:Vector.<ExchangeInfo>, 
			vecSweepInfo:Vector.<SSweepInfo>, vecPendRes:Vector.<SPendRes>, vecXinFaDBInfo:Vector.<SXinFaDBInfo>, vecLevelPrize:Vector.<SPrize2DB>, vecPlatformParam:Vector.<SPlatformParam>, 
			vecEventInfo:Vector.<SEventInfo>, vecEventOffLine:Vector.<SEventOffLine>, vecBuyItemDBInfo:Vector.<SBuyItemDBInfo>, vecDayTargetDBInfo:Vector.<SDayTargetDBInfo>, vecBattleArrayDBInfo:Vector.<SBattleArrayDBInfo>, 
			vecAutoStoreDBInfo:Vector.<SAutoStoreDBInfo>, vecTHDBInfo:Vector.<STHDBInfo>, vecBeauty:Vector.<SBeauty>, vecFightFormationDBInfo:Vector.<SFightFormationDBInfo>, vecFightHeroDBInfo:Vector.<SFightHeroDBInfo>, 
			sShipData:PlayerSelfShipData, vecShipReport:Vector.<ShipReport>, vecGEMDBInfo:Vector.<SGEMDBInfo>, vecShengLing:Vector.<SShengLingInfo2DB>, vecShengLingPrize:Vector.<SShengLingPrize2DB>):RoleDataInfo
		{
			var s_:RoleDataInfo = new RoleDataInfo();
			s_.qwRoleId = qwRoleId;
			s_.stBaseInfo = stBaseInfo;
			s_.vecFighterInfo = vecFighterInfo;
			s_.vecSkillInfo = vecSkillInfo;
			s_.vecPassiveSkillInfo = vecPassiveSkillInfo;
			s_.vecFighterCombination = vecFighterCombination;
			s_.vecRoleItemInfo = vecRoleItemInfo;
			s_.vecFriendsInfo = vecFriendsInfo;
			s_.vecRoleDgnInfo = vecRoleDgnInfo;
			s_.vecRoleTaskInfo = vecRoleTaskInfo;
			s_.vecGameVars = vecGameVars;
			s_.vecRoleSlotsInfo = vecRoleSlotsInfo;
			s_.vecFormationInfo = vecFormationInfo;
			s_.vecPetDataInfo = vecPetDataInfo;
			s_.oRolePetInfo = oRolePetInfo;
			s_.vecBeastSoulInfo = vecBeastSoulInfo;
			s_.vecFireInfo = vecFireInfo;
			s_.vecArenaInfo = vecArenaInfo;
			s_.vecDBBuffInfo = vecDBBuffInfo;
			s_.vecSoulSpaceInfo = vecSoulSpaceInfo;
			s_.vecBubbleInfo = vecBubbleInfo;
			s_.vecHorseDB = vecHorseDB;
			s_.sGroupInfo = sGroupInfo;
			s_.sYaMenInfo = sYaMenInfo;
			s_.vecActivityTask = vecActivityTask;
			s_.vecTitle = vecTitle;
			s_.vecAchievementInfo = vecAchievementInfo;
			s_.vecCollectionInfo = vecCollectionInfo;
			s_.vecRoleAttaked = vecRoleAttaked;
			s_.vecExchangeInfo = vecExchangeInfo;
			s_.vecSweepInfo = vecSweepInfo;
			s_.vecPendRes = vecPendRes;
			s_.vecXinFaDBInfo = vecXinFaDBInfo;
			s_.vecLevelPrize = vecLevelPrize;
			s_.vecPlatformParam = vecPlatformParam;
			s_.vecEventInfo = vecEventInfo;
			s_.vecEventOffLine = vecEventOffLine;
			s_.vecBuyItemDBInfo = vecBuyItemDBInfo;
			s_.vecDayTargetDBInfo = vecDayTargetDBInfo;
			s_.vecBattleArrayDBInfo = vecBattleArrayDBInfo;
			s_.vecAutoStoreDBInfo = vecAutoStoreDBInfo;
			s_.vecTHDBInfo = vecTHDBInfo;
			s_.vecBeauty = vecBeauty;
			s_.vecFightFormationDBInfo = vecFightFormationDBInfo;
			s_.vecFightHeroDBInfo = vecFightHeroDBInfo;
			s_.sShipData = sShipData;
			s_.vecShipReport = vecShipReport;
			s_.vecGEMDBInfo = vecGEMDBInfo;
			s_.vecShengLing = vecShengLing;
			s_.vecShengLingPrize = vecShengLingPrize;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <RoleDataInfo _name_={name_} qwRoleId={qwRoleId}/>;
			else
				topXml = <RoleDataInfo qwRoleId={qwRoleId}/>;
			if(stBaseInfo != null)
				topXml.appendChild(stBaseInfo.toXML("stBaseInfo"));
			if(vecFighterInfo != null)
			{
				var vecFighterInfoXml:XML = <Vec_SFighterDBInfo _name_="vecFighterInfo"/>;
				for each(var s2:SFighterDBInfo in vecFighterInfo)
					vecFighterInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecFighterInfoXml);
			}
			if(vecSkillInfo != null)
			{
				var vecSkillInfoXml:XML = <Vec_SSkillDBInfo _name_="vecSkillInfo"/>;
				for each(var s3:SSkillDBInfo in vecSkillInfo)
					vecSkillInfoXml.appendChild(s3.toXML());
				topXml.appendChild(vecSkillInfoXml);
			}
			if(vecPassiveSkillInfo != null)
			{
				var vecPassiveSkillInfoXml:XML = <Vec_SPassiveSkillDBInfo _name_="vecPassiveSkillInfo"/>;
				for each(var s4:SPassiveSkillDBInfo in vecPassiveSkillInfo)
					vecPassiveSkillInfoXml.appendChild(s4.toXML());
				topXml.appendChild(vecPassiveSkillInfoXml);
			}
			if(vecFighterCombination != null)
			{
				var vecFighterCombinationXml:XML = <Vec_SFighterCombination _name_="vecFighterCombination"/>;
				for each(var s5:SFighterCombination in vecFighterCombination)
					vecFighterCombinationXml.appendChild(s5.toXML());
				topXml.appendChild(vecFighterCombinationXml);
			}
			if(vecRoleItemInfo != null)
			{
				var vecRoleItemInfoXml:XML = <Vec_SItem _name_="vecRoleItemInfo"/>;
				for each(var s6:SItem in vecRoleItemInfo)
					vecRoleItemInfoXml.appendChild(s6.toXML());
				topXml.appendChild(vecRoleItemInfoXml);
			}
			if(vecFriendsInfo != null)
			{
				var vecFriendsInfoXml:XML = <Vec_SFriendDBInfo _name_="vecFriendsInfo"/>;
				for each(var s7:SFriendDBInfo in vecFriendsInfo)
					vecFriendsInfoXml.appendChild(s7.toXML());
				topXml.appendChild(vecFriendsInfoXml);
			}
			if(vecRoleDgnInfo != null)
			{
				var vecRoleDgnInfoXml:XML = <Vec_RoleDgnInfo _name_="vecRoleDgnInfo"/>;
				for each(var s8:RoleDgnInfo in vecRoleDgnInfo)
					vecRoleDgnInfoXml.appendChild(s8.toXML());
				topXml.appendChild(vecRoleDgnInfoXml);
			}
			if(vecRoleTaskInfo != null)
			{
				var vecRoleTaskInfoXml:XML = <Vec_RoleTaskInfo _name_="vecRoleTaskInfo"/>;
				for each(var s9:RoleTaskInfo in vecRoleTaskInfo)
					vecRoleTaskInfoXml.appendChild(s9.toXML());
				topXml.appendChild(vecRoleTaskInfoXml);
			}
			if(vecGameVars != null)
			{
				var vecGameVarsXml:XML = <Vec_SVarsDBInfo _name_="vecGameVars"/>;
				for each(var s10:SVarsDBInfo in vecGameVars)
					vecGameVarsXml.appendChild(s10.toXML());
				topXml.appendChild(vecGameVarsXml);
			}
			if(vecRoleSlotsInfo != null)
			{
				var vecRoleSlotsInfoXml:XML = <Vec_SRoleSlotsInfo _name_="vecRoleSlotsInfo"/>;
				for each(var s11:SRoleSlotsInfo in vecRoleSlotsInfo)
					vecRoleSlotsInfoXml.appendChild(s11.toXML());
				topXml.appendChild(vecRoleSlotsInfoXml);
			}
			if(vecFormationInfo != null)
			{
				var vecFormationInfoXml:XML = <Vec_SFormationInfo _name_="vecFormationInfo"/>;
				for each(var s12:SFormationInfo in vecFormationInfo)
					vecFormationInfoXml.appendChild(s12.toXML());
				topXml.appendChild(vecFormationInfoXml);
			}
			if(vecPetDataInfo != null)
			{
				var vecPetDataInfoXml:XML = <Vec_SPetDataInfo _name_="vecPetDataInfo"/>;
				for each(var s13:SPetDataInfo in vecPetDataInfo)
					vecPetDataInfoXml.appendChild(s13.toXML());
				topXml.appendChild(vecPetDataInfoXml);
			}
			if(oRolePetInfo != null)
				topXml.appendChild(oRolePetInfo.toXML("oRolePetInfo"));
			if(vecBeastSoulInfo != null)
			{
				var vecBeastSoulInfoXml:XML = <Vec_SBeastSoulInfo _name_="vecBeastSoulInfo"/>;
				for each(var s15:SBeastSoulInfo in vecBeastSoulInfo)
					vecBeastSoulInfoXml.appendChild(s15.toXML());
				topXml.appendChild(vecBeastSoulInfoXml);
			}
			if(vecFireInfo != null)
			{
				var vecFireInfoXml:XML = <Vec_SFireInfo _name_="vecFireInfo"/>;
				for each(var s16:SFireInfo in vecFireInfo)
					vecFireInfoXml.appendChild(s16.toXML());
				topXml.appendChild(vecFireInfoXml);
			}
			if(vecArenaInfo != null)
			{
				var vecArenaInfoXml:XML = <Vec_SRoleArenaInfo _name_="vecArenaInfo"/>;
				for each(var s17:SRoleArenaInfo in vecArenaInfo)
					vecArenaInfoXml.appendChild(s17.toXML());
				topXml.appendChild(vecArenaInfoXml);
			}
			if(vecDBBuffInfo != null)
			{
				var vecDBBuffInfoXml:XML = <Vec_SDBBuffInfo _name_="vecDBBuffInfo"/>;
				for each(var s18:SDBBuffInfo in vecDBBuffInfo)
					vecDBBuffInfoXml.appendChild(s18.toXML());
				topXml.appendChild(vecDBBuffInfoXml);
			}
			if(vecSoulSpaceInfo != null)
			{
				var vecSoulSpaceInfoXml:XML = <Vec_SSoulSpaceInfo _name_="vecSoulSpaceInfo"/>;
				for each(var s19:SSoulSpaceInfo in vecSoulSpaceInfo)
					vecSoulSpaceInfoXml.appendChild(s19.toXML());
				topXml.appendChild(vecSoulSpaceInfoXml);
			}
			if(vecBubbleInfo != null)
			{
				var vecBubbleInfoXml:XML = <Vec_SDBBubbleInfo _name_="vecBubbleInfo"/>;
				for each(var s20:SDBBubbleInfo in vecBubbleInfo)
					vecBubbleInfoXml.appendChild(s20.toXML());
				topXml.appendChild(vecBubbleInfoXml);
			}
			if(vecHorseDB != null)
			{
				var vecHorseDBXml:XML = <Vec_SHorseDB _name_="vecHorseDB"/>;
				for each(var s21:SHorseDB in vecHorseDB)
					vecHorseDBXml.appendChild(s21.toXML());
				topXml.appendChild(vecHorseDBXml);
			}
			if(sGroupInfo != null)
				topXml.appendChild(sGroupInfo.toXML("sGroupInfo"));
			if(sYaMenInfo != null)
				topXml.appendChild(sYaMenInfo.toXML("sYaMenInfo"));
			if(vecActivityTask != null)
			{
				var vecActivityTaskXml:XML = <Vec_SActivityTaskInfo _name_="vecActivityTask"/>;
				for each(var s24:SActivityTaskInfo in vecActivityTask)
					vecActivityTaskXml.appendChild(s24.toXML());
				topXml.appendChild(vecActivityTaskXml);
			}
			if(vecTitle != null)
			{
				var vecTitleXml:XML = <Vec_STitle _name_="vecTitle"/>;
				for each(var s25:STitle in vecTitle)
					vecTitleXml.appendChild(s25.toXML());
				topXml.appendChild(vecTitleXml);
			}
			if(vecAchievementInfo != null)
			{
				var vecAchievementInfoXml:XML = <Vec_SAchievementInfo _name_="vecAchievementInfo"/>;
				for each(var s26:SAchievementInfo in vecAchievementInfo)
					vecAchievementInfoXml.appendChild(s26.toXML());
				topXml.appendChild(vecAchievementInfoXml);
			}
			if(vecCollectionInfo != null)
			{
				var vecCollectionInfoXml:XML = <Vec_SCollectionInfo _name_="vecCollectionInfo"/>;
				for each(var s27:SCollectionInfo in vecCollectionInfo)
					vecCollectionInfoXml.appendChild(s27.toXML());
				topXml.appendChild(vecCollectionInfoXml);
			}
			if(vecRoleAttaked != null)
			{
				var vecRoleAttakedXml:XML = <Vec_SRoleAttaked _name_="vecRoleAttaked"/>;
				for each(var s28:SRoleAttaked in vecRoleAttaked)
					vecRoleAttakedXml.appendChild(s28.toXML());
				topXml.appendChild(vecRoleAttakedXml);
			}
			if(vecExchangeInfo != null)
			{
				var vecExchangeInfoXml:XML = <Vec_ExchangeInfo _name_="vecExchangeInfo"/>;
				for each(var s29:ExchangeInfo in vecExchangeInfo)
					vecExchangeInfoXml.appendChild(s29.toXML());
				topXml.appendChild(vecExchangeInfoXml);
			}
			if(vecSweepInfo != null)
			{
				var vecSweepInfoXml:XML = <Vec_SSweepInfo _name_="vecSweepInfo"/>;
				for each(var s30:SSweepInfo in vecSweepInfo)
					vecSweepInfoXml.appendChild(s30.toXML());
				topXml.appendChild(vecSweepInfoXml);
			}
			if(vecPendRes != null)
			{
				var vecPendResXml:XML = <Vec_SPendRes _name_="vecPendRes"/>;
				for each(var s31:SPendRes in vecPendRes)
					vecPendResXml.appendChild(s31.toXML());
				topXml.appendChild(vecPendResXml);
			}
			if(vecXinFaDBInfo != null)
			{
				var vecXinFaDBInfoXml:XML = <Vec_SXinFaDBInfo _name_="vecXinFaDBInfo"/>;
				for each(var s32:SXinFaDBInfo in vecXinFaDBInfo)
					vecXinFaDBInfoXml.appendChild(s32.toXML());
				topXml.appendChild(vecXinFaDBInfoXml);
			}
			if(vecLevelPrize != null)
			{
				var vecLevelPrizeXml:XML = <Vec_SPrize2DB _name_="vecLevelPrize"/>;
				for each(var s33:SPrize2DB in vecLevelPrize)
					vecLevelPrizeXml.appendChild(s33.toXML());
				topXml.appendChild(vecLevelPrizeXml);
			}
			if(vecPlatformParam != null)
			{
				var vecPlatformParamXml:XML = <Vec_SPlatformParam _name_="vecPlatformParam"/>;
				for each(var s34:SPlatformParam in vecPlatformParam)
					vecPlatformParamXml.appendChild(s34.toXML());
				topXml.appendChild(vecPlatformParamXml);
			}
			if(vecEventInfo != null)
			{
				var vecEventInfoXml:XML = <Vec_SEventInfo _name_="vecEventInfo"/>;
				for each(var s35:SEventInfo in vecEventInfo)
					vecEventInfoXml.appendChild(s35.toXML());
				topXml.appendChild(vecEventInfoXml);
			}
			if(vecEventOffLine != null)
			{
				var vecEventOffLineXml:XML = <Vec_SEventOffLine _name_="vecEventOffLine"/>;
				for each(var s36:SEventOffLine in vecEventOffLine)
					vecEventOffLineXml.appendChild(s36.toXML());
				topXml.appendChild(vecEventOffLineXml);
			}
			if(vecBuyItemDBInfo != null)
			{
				var vecBuyItemDBInfoXml:XML = <Vec_SBuyItemDBInfo _name_="vecBuyItemDBInfo"/>;
				for each(var s37:SBuyItemDBInfo in vecBuyItemDBInfo)
					vecBuyItemDBInfoXml.appendChild(s37.toXML());
				topXml.appendChild(vecBuyItemDBInfoXml);
			}
			if(vecDayTargetDBInfo != null)
			{
				var vecDayTargetDBInfoXml:XML = <Vec_SDayTargetDBInfo _name_="vecDayTargetDBInfo"/>;
				for each(var s38:SDayTargetDBInfo in vecDayTargetDBInfo)
					vecDayTargetDBInfoXml.appendChild(s38.toXML());
				topXml.appendChild(vecDayTargetDBInfoXml);
			}
			if(vecBattleArrayDBInfo != null)
			{
				var vecBattleArrayDBInfoXml:XML = <Vec_SBattleArrayDBInfo _name_="vecBattleArrayDBInfo"/>;
				for each(var s39:SBattleArrayDBInfo in vecBattleArrayDBInfo)
					vecBattleArrayDBInfoXml.appendChild(s39.toXML());
				topXml.appendChild(vecBattleArrayDBInfoXml);
			}
			if(vecAutoStoreDBInfo != null)
			{
				var vecAutoStoreDBInfoXml:XML = <Vec_SAutoStoreDBInfo _name_="vecAutoStoreDBInfo"/>;
				for each(var s40:SAutoStoreDBInfo in vecAutoStoreDBInfo)
					vecAutoStoreDBInfoXml.appendChild(s40.toXML());
				topXml.appendChild(vecAutoStoreDBInfoXml);
			}
			if(vecTHDBInfo != null)
			{
				var vecTHDBInfoXml:XML = <Vec_STHDBInfo _name_="vecTHDBInfo"/>;
				for each(var s41:STHDBInfo in vecTHDBInfo)
					vecTHDBInfoXml.appendChild(s41.toXML());
				topXml.appendChild(vecTHDBInfoXml);
			}
			if(vecBeauty != null)
			{
				var vecBeautyXml:XML = <Vec_SBeauty _name_="vecBeauty"/>;
				for each(var s42:SBeauty in vecBeauty)
					vecBeautyXml.appendChild(s42.toXML());
				topXml.appendChild(vecBeautyXml);
			}
			if(vecFightFormationDBInfo != null)
			{
				var vecFightFormationDBInfoXml:XML = <Vec_SFightFormationDBInfo _name_="vecFightFormationDBInfo"/>;
				for each(var s43:SFightFormationDBInfo in vecFightFormationDBInfo)
					vecFightFormationDBInfoXml.appendChild(s43.toXML());
				topXml.appendChild(vecFightFormationDBInfoXml);
			}
			if(vecFightHeroDBInfo != null)
			{
				var vecFightHeroDBInfoXml:XML = <Vec_SFightHeroDBInfo _name_="vecFightHeroDBInfo"/>;
				for each(var s44:SFightHeroDBInfo in vecFightHeroDBInfo)
					vecFightHeroDBInfoXml.appendChild(s44.toXML());
				topXml.appendChild(vecFightHeroDBInfoXml);
			}
			if(sShipData != null)
				topXml.appendChild(sShipData.toXML("sShipData"));
			if(vecShipReport != null)
			{
				var vecShipReportXml:XML = <Vec_ShipReport _name_="vecShipReport"/>;
				for each(var s46:ShipReport in vecShipReport)
					vecShipReportXml.appendChild(s46.toXML());
				topXml.appendChild(vecShipReportXml);
			}
			if(vecGEMDBInfo != null)
			{
				var vecGEMDBInfoXml:XML = <Vec_SGEMDBInfo _name_="vecGEMDBInfo"/>;
				for each(var s47:SGEMDBInfo in vecGEMDBInfo)
					vecGEMDBInfoXml.appendChild(s47.toXML());
				topXml.appendChild(vecGEMDBInfoXml);
			}
			if(vecShengLing != null)
			{
				var vecShengLingXml:XML = <Vec_SShengLingInfo2DB _name_="vecShengLing"/>;
				for each(var s48:SShengLingInfo2DB in vecShengLing)
					vecShengLingXml.appendChild(s48.toXML());
				topXml.appendChild(vecShengLingXml);
			}
			if(vecShengLingPrize != null)
			{
				var vecShengLingPrizeXml:XML = <Vec_SShengLingPrize2DB _name_="vecShengLingPrize"/>;
				for each(var s49:SShengLingPrize2DB in vecShengLingPrize)
					vecShengLingPrizeXml.appendChild(s49.toXML());
				topXml.appendChild(vecShengLingPrizeXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleId = qwRoleId;
			obj_.stBaseInfo = stBaseInfo;
			obj_.vecFighterInfo = vecFighterInfo;
			obj_.vecSkillInfo = vecSkillInfo;
			obj_.vecPassiveSkillInfo = vecPassiveSkillInfo;
			obj_.vecFighterCombination = vecFighterCombination;
			obj_.vecRoleItemInfo = vecRoleItemInfo;
			obj_.vecFriendsInfo = vecFriendsInfo;
			obj_.vecRoleDgnInfo = vecRoleDgnInfo;
			obj_.vecRoleTaskInfo = vecRoleTaskInfo;
			obj_.vecGameVars = vecGameVars;
			obj_.vecRoleSlotsInfo = vecRoleSlotsInfo;
			obj_.vecFormationInfo = vecFormationInfo;
			obj_.vecPetDataInfo = vecPetDataInfo;
			obj_.oRolePetInfo = oRolePetInfo;
			obj_.vecBeastSoulInfo = vecBeastSoulInfo;
			obj_.vecFireInfo = vecFireInfo;
			obj_.vecArenaInfo = vecArenaInfo;
			obj_.vecDBBuffInfo = vecDBBuffInfo;
			obj_.vecSoulSpaceInfo = vecSoulSpaceInfo;
			obj_.vecBubbleInfo = vecBubbleInfo;
			obj_.vecHorseDB = vecHorseDB;
			obj_.sGroupInfo = sGroupInfo;
			obj_.sYaMenInfo = sYaMenInfo;
			obj_.vecActivityTask = vecActivityTask;
			obj_.vecTitle = vecTitle;
			obj_.vecAchievementInfo = vecAchievementInfo;
			obj_.vecCollectionInfo = vecCollectionInfo;
			obj_.vecRoleAttaked = vecRoleAttaked;
			obj_.vecExchangeInfo = vecExchangeInfo;
			obj_.vecSweepInfo = vecSweepInfo;
			obj_.vecPendRes = vecPendRes;
			obj_.vecXinFaDBInfo = vecXinFaDBInfo;
			obj_.vecLevelPrize = vecLevelPrize;
			obj_.vecPlatformParam = vecPlatformParam;
			obj_.vecEventInfo = vecEventInfo;
			obj_.vecEventOffLine = vecEventOffLine;
			obj_.vecBuyItemDBInfo = vecBuyItemDBInfo;
			obj_.vecDayTargetDBInfo = vecDayTargetDBInfo;
			obj_.vecBattleArrayDBInfo = vecBattleArrayDBInfo;
			obj_.vecAutoStoreDBInfo = vecAutoStoreDBInfo;
			obj_.vecTHDBInfo = vecTHDBInfo;
			obj_.vecBeauty = vecBeauty;
			obj_.vecFightFormationDBInfo = vecFightFormationDBInfo;
			obj_.vecFightHeroDBInfo = vecFightHeroDBInfo;
			obj_.sShipData = sShipData;
			obj_.vecShipReport = vecShipReport;
			obj_.vecGEMDBInfo = vecGEMDBInfo;
			obj_.vecShengLing = vecShengLing;
			obj_.vecShengLingPrize = vecShengLingPrize;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):RoleDataInfo
		{
			var s_:RoleDataInfo = new RoleDataInfo();
			var qwRoleId:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleId = qwRoleId;
			var stBaseInfo:RoleBaseInfo = RoleBaseInfo.fromByteArray(bytes);
			s_.stBaseInfo = stBaseInfo;
			var vecFighterInfo:Vector.<SFighterDBInfo> = SFighterDBInfo.vectorFromByteArray(bytes);
			s_.vecFighterInfo = vecFighterInfo;
			var vecSkillInfo:Vector.<SSkillDBInfo> = SSkillDBInfo.vectorFromByteArray(bytes);
			s_.vecSkillInfo = vecSkillInfo;
			var vecPassiveSkillInfo:Vector.<SPassiveSkillDBInfo> = SPassiveSkillDBInfo.vectorFromByteArray(bytes);
			s_.vecPassiveSkillInfo = vecPassiveSkillInfo;
			var vecFighterCombination:Vector.<SFighterCombination> = SFighterCombination.vectorFromByteArray(bytes);
			s_.vecFighterCombination = vecFighterCombination;
			var vecRoleItemInfo:Vector.<SItem> = SItem.superVectorFromByteArray(bytes);
			s_.vecRoleItemInfo = vecRoleItemInfo;
			var vecFriendsInfo:Vector.<SFriendDBInfo> = SFriendDBInfo.vectorFromByteArray(bytes);
			s_.vecFriendsInfo = vecFriendsInfo;
			var vecRoleDgnInfo:Vector.<RoleDgnInfo> = RoleDgnInfo.vectorFromByteArray(bytes);
			s_.vecRoleDgnInfo = vecRoleDgnInfo;
			var vecRoleTaskInfo:Vector.<RoleTaskInfo> = RoleTaskInfo.vectorFromByteArray(bytes);
			s_.vecRoleTaskInfo = vecRoleTaskInfo;
			var vecGameVars:Vector.<SVarsDBInfo> = SVarsDBInfo.vectorFromByteArray(bytes);
			s_.vecGameVars = vecGameVars;
			var vecRoleSlotsInfo:Vector.<SRoleSlotsInfo> = SRoleSlotsInfo.vectorFromByteArray(bytes);
			s_.vecRoleSlotsInfo = vecRoleSlotsInfo;
			var vecFormationInfo:Vector.<SFormationInfo> = SFormationInfo.vectorFromByteArray(bytes);
			s_.vecFormationInfo = vecFormationInfo;
			var vecPetDataInfo:Vector.<SPetDataInfo> = SPetDataInfo.vectorFromByteArray(bytes);
			s_.vecPetDataInfo = vecPetDataInfo;
			var oRolePetInfo:SRolePetInfo = SRolePetInfo.fromByteArray(bytes);
			s_.oRolePetInfo = oRolePetInfo;
			var vecBeastSoulInfo:Vector.<SBeastSoulInfo> = SBeastSoulInfo.vectorFromByteArray(bytes);
			s_.vecBeastSoulInfo = vecBeastSoulInfo;
			var vecFireInfo:Vector.<SFireInfo> = SFireInfo.vectorFromByteArray(bytes);
			s_.vecFireInfo = vecFireInfo;
			var vecArenaInfo:Vector.<SRoleArenaInfo> = SRoleArenaInfo.vectorFromByteArray(bytes);
			s_.vecArenaInfo = vecArenaInfo;
			var vecDBBuffInfo:Vector.<SDBBuffInfo> = SDBBuffInfo.vectorFromByteArray(bytes);
			s_.vecDBBuffInfo = vecDBBuffInfo;
			var vecSoulSpaceInfo:Vector.<SSoulSpaceInfo> = SSoulSpaceInfo.vectorFromByteArray(bytes);
			s_.vecSoulSpaceInfo = vecSoulSpaceInfo;
			var vecBubbleInfo:Vector.<SDBBubbleInfo> = SDBBubbleInfo.vectorFromByteArray(bytes);
			s_.vecBubbleInfo = vecBubbleInfo;
			var vecHorseDB:Vector.<SHorseDB> = SHorseDB.vectorFromByteArray(bytes);
			s_.vecHorseDB = vecHorseDB;
			var sGroupInfo:SGroupTaskInfo = SGroupTaskInfo.fromByteArray(bytes);
			s_.sGroupInfo = sGroupInfo;
			var sYaMenInfo:SYaMenTaskInfo = SYaMenTaskInfo.fromByteArray(bytes);
			s_.sYaMenInfo = sYaMenInfo;
			var vecActivityTask:Vector.<SActivityTaskInfo> = SActivityTaskInfo.vectorFromByteArray(bytes);
			s_.vecActivityTask = vecActivityTask;
			var vecTitle:Vector.<STitle> = STitle.vectorFromByteArray(bytes);
			s_.vecTitle = vecTitle;
			var vecAchievementInfo:Vector.<SAchievementInfo> = SAchievementInfo.vectorFromByteArray(bytes);
			s_.vecAchievementInfo = vecAchievementInfo;
			var vecCollectionInfo:Vector.<SCollectionInfo> = SCollectionInfo.vectorFromByteArray(bytes);
			s_.vecCollectionInfo = vecCollectionInfo;
			var vecRoleAttaked:Vector.<SRoleAttaked> = SRoleAttaked.vectorFromByteArray(bytes);
			s_.vecRoleAttaked = vecRoleAttaked;
			var vecExchangeInfo:Vector.<ExchangeInfo> = ExchangeInfo.vectorFromByteArray(bytes);
			s_.vecExchangeInfo = vecExchangeInfo;
			var vecSweepInfo:Vector.<SSweepInfo> = SSweepInfo.vectorFromByteArray(bytes);
			s_.vecSweepInfo = vecSweepInfo;
			var vecPendRes:Vector.<SPendRes> = SPendRes.vectorFromByteArray(bytes);
			s_.vecPendRes = vecPendRes;
			var vecXinFaDBInfo:Vector.<SXinFaDBInfo> = SXinFaDBInfo.vectorFromByteArray(bytes);
			s_.vecXinFaDBInfo = vecXinFaDBInfo;
			var vecLevelPrize:Vector.<SPrize2DB> = SPrize2DB.vectorFromByteArray(bytes);
			s_.vecLevelPrize = vecLevelPrize;
			var vecPlatformParam:Vector.<SPlatformParam> = SPlatformParam.vectorFromByteArray(bytes);
			s_.vecPlatformParam = vecPlatformParam;
			var vecEventInfo:Vector.<SEventInfo> = SEventInfo.vectorFromByteArray(bytes);
			s_.vecEventInfo = vecEventInfo;
			var vecEventOffLine:Vector.<SEventOffLine> = SEventOffLine.vectorFromByteArray(bytes);
			s_.vecEventOffLine = vecEventOffLine;
			var vecBuyItemDBInfo:Vector.<SBuyItemDBInfo> = SBuyItemDBInfo.vectorFromByteArray(bytes);
			s_.vecBuyItemDBInfo = vecBuyItemDBInfo;
			var vecDayTargetDBInfo:Vector.<SDayTargetDBInfo> = SDayTargetDBInfo.vectorFromByteArray(bytes);
			s_.vecDayTargetDBInfo = vecDayTargetDBInfo;
			var vecBattleArrayDBInfo:Vector.<SBattleArrayDBInfo> = SBattleArrayDBInfo.vectorFromByteArray(bytes);
			s_.vecBattleArrayDBInfo = vecBattleArrayDBInfo;
			var vecAutoStoreDBInfo:Vector.<SAutoStoreDBInfo> = SAutoStoreDBInfo.vectorFromByteArray(bytes);
			s_.vecAutoStoreDBInfo = vecAutoStoreDBInfo;
			var vecTHDBInfo:Vector.<STHDBInfo> = STHDBInfo.vectorFromByteArray(bytes);
			s_.vecTHDBInfo = vecTHDBInfo;
			var vecBeauty:Vector.<SBeauty> = SBeauty.vectorFromByteArray(bytes);
			s_.vecBeauty = vecBeauty;
			var vecFightFormationDBInfo:Vector.<SFightFormationDBInfo> = SFightFormationDBInfo.vectorFromByteArray(bytes);
			s_.vecFightFormationDBInfo = vecFightFormationDBInfo;
			var vecFightHeroDBInfo:Vector.<SFightHeroDBInfo> = SFightHeroDBInfo.vectorFromByteArray(bytes);
			s_.vecFightHeroDBInfo = vecFightHeroDBInfo;
			var sShipData:PlayerSelfShipData = PlayerSelfShipData.fromByteArray(bytes);
			s_.sShipData = sShipData;
			var vecShipReport:Vector.<ShipReport> = ShipReport.vectorFromByteArray(bytes);
			s_.vecShipReport = vecShipReport;
			var vecGEMDBInfo:Vector.<SGEMDBInfo> = SGEMDBInfo.vectorFromByteArray(bytes);
			s_.vecGEMDBInfo = vecGEMDBInfo;
			var vecShengLing:Vector.<SShengLingInfo2DB> = SShengLingInfo2DB.vectorFromByteArray(bytes);
			s_.vecShengLing = vecShengLing;
			var vecShengLingPrize:Vector.<SShengLingPrize2DB> = SShengLingPrize2DB.vectorFromByteArray(bytes);
			s_.vecShengLingPrize = vecShengLingPrize;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<RoleDataInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<RoleDataInfo> = new Vector.<RoleDataInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:RoleDataInfo = RoleDataInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleId);
			stBaseInfo.toByteArray(bytes);
			SFighterDBInfo.vectorToByteArray(vecFighterInfo, bytes);
			SSkillDBInfo.vectorToByteArray(vecSkillInfo, bytes);
			SPassiveSkillDBInfo.vectorToByteArray(vecPassiveSkillInfo, bytes);
			SFighterCombination.vectorToByteArray(vecFighterCombination, bytes);
			SItem.superVectorToByteArray(vecRoleItemInfo, bytes);
			SFriendDBInfo.vectorToByteArray(vecFriendsInfo, bytes);
			RoleDgnInfo.vectorToByteArray(vecRoleDgnInfo, bytes);
			RoleTaskInfo.vectorToByteArray(vecRoleTaskInfo, bytes);
			SVarsDBInfo.vectorToByteArray(vecGameVars, bytes);
			SRoleSlotsInfo.vectorToByteArray(vecRoleSlotsInfo, bytes);
			SFormationInfo.vectorToByteArray(vecFormationInfo, bytes);
			SPetDataInfo.vectorToByteArray(vecPetDataInfo, bytes);
			oRolePetInfo.toByteArray(bytes);
			SBeastSoulInfo.vectorToByteArray(vecBeastSoulInfo, bytes);
			SFireInfo.vectorToByteArray(vecFireInfo, bytes);
			SRoleArenaInfo.vectorToByteArray(vecArenaInfo, bytes);
			SDBBuffInfo.vectorToByteArray(vecDBBuffInfo, bytes);
			SSoulSpaceInfo.vectorToByteArray(vecSoulSpaceInfo, bytes);
			SDBBubbleInfo.vectorToByteArray(vecBubbleInfo, bytes);
			SHorseDB.vectorToByteArray(vecHorseDB, bytes);
			sGroupInfo.toByteArray(bytes);
			sYaMenInfo.toByteArray(bytes);
			SActivityTaskInfo.vectorToByteArray(vecActivityTask, bytes);
			STitle.vectorToByteArray(vecTitle, bytes);
			SAchievementInfo.vectorToByteArray(vecAchievementInfo, bytes);
			SCollectionInfo.vectorToByteArray(vecCollectionInfo, bytes);
			SRoleAttaked.vectorToByteArray(vecRoleAttaked, bytes);
			ExchangeInfo.vectorToByteArray(vecExchangeInfo, bytes);
			SSweepInfo.vectorToByteArray(vecSweepInfo, bytes);
			SPendRes.vectorToByteArray(vecPendRes, bytes);
			SXinFaDBInfo.vectorToByteArray(vecXinFaDBInfo, bytes);
			SPrize2DB.vectorToByteArray(vecLevelPrize, bytes);
			SPlatformParam.vectorToByteArray(vecPlatformParam, bytes);
			SEventInfo.vectorToByteArray(vecEventInfo, bytes);
			SEventOffLine.vectorToByteArray(vecEventOffLine, bytes);
			SBuyItemDBInfo.vectorToByteArray(vecBuyItemDBInfo, bytes);
			SDayTargetDBInfo.vectorToByteArray(vecDayTargetDBInfo, bytes);
			SBattleArrayDBInfo.vectorToByteArray(vecBattleArrayDBInfo, bytes);
			SAutoStoreDBInfo.vectorToByteArray(vecAutoStoreDBInfo, bytes);
			STHDBInfo.vectorToByteArray(vecTHDBInfo, bytes);
			SBeauty.vectorToByteArray(vecBeauty, bytes);
			SFightFormationDBInfo.vectorToByteArray(vecFightFormationDBInfo, bytes);
			SFightHeroDBInfo.vectorToByteArray(vecFightHeroDBInfo, bytes);
			sShipData.toByteArray(bytes);
			ShipReport.vectorToByteArray(vecShipReport, bytes);
			SGEMDBInfo.vectorToByteArray(vecGEMDBInfo, bytes);
			SShengLingInfo2DB.vectorToByteArray(vecShengLing, bytes);
			SShengLingPrize2DB.vectorToByteArray(vecShengLingPrize, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<RoleDataInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:RoleDataInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
