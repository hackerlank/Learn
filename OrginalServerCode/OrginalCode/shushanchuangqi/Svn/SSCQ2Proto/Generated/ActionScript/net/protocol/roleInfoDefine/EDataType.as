/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDataType.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
 {
	import net.protocol.Message.ProtocolMessageProt10;
	/**
	 * 数据类型
	 */
	public final class EDataType
	{
		public static const eTypeRoleBaseInfo:uint = 0; //玩家基本数据
		public static const eTypeItemInfo:uint = 1; //玩家物品数据
		public static const eTypePlayerDgn:uint = 2; //玩家副本数据
		public static const eTypeFighterInfo:uint = 3; //玩家将信息
		public static const eTypeTaskInfo:uint = 4; //玩家任务信息
		public static const eTypeSkillInfo:uint = 5; //技能信息
		public static const eTypePassiveSkillInfo:uint = 6; //被动技能信息
		public static const eTypeFriendInfo:uint = 7; //关系信息
		public static const eTypeVarInfo:uint = 8; //关系信息
		public static const eTypeCittaInfo:uint = 9; //玩家心法数据
		public static const eTypeSlotsInfo:uint = 10; //玩家/其他槽心法数据
		public static const eTypeTrumpInfo:uint = 11; //法宝信息
		public static const eTypeEquipTrumpInfo:uint = 12; //装备法宝信息
		public static const eTypeEquipTrumpShuffleInfo:uint = 13; //装备法宝洗炼信息
		public static const eTypeFormationInfo:uint = 14; //阵形信息
		public static const eTypePetDataInfo:uint = 15; //阵灵信息
		public static const eTypeRolePetInfo:uint = 16; //阵灵全局信息
		public static const eTypeBeastSoulInfo:uint = 17; //兽魂信息
		public static const eTypeTripodFireInfo:uint = 18; //九疑鼎的火种信息
		public static const eTypeArena:uint = 19; //斗剑信息
		public static const eTypeBuffInfo:uint = 20; //Buff信息
		public static const eTypeFashionInfo:uint = 21; //时装信息
		public static const eTypeSoulSpaceInfo:uint = 22; //魄空间信息
		public static const eTypeBubbleInfo:uint = 23; //气泡信息
		public static const eTypeHorseDBInfo:uint = 24; //坐骑信息
		public static const eTypeGroupTask:uint = 25; //师门任务
		public static const eTypeYaMenTask:uint = 26; //衙门任务
		public static const eTypeActivityTask:uint = 27; //活跃度任务
		public static const eTypeTitle:uint = 28; //称号
		public static const eTypeAchievementInfo:uint = 29; //成就
		public static const eTypeCollectionInfo:uint = 30; //收藏
		public static const eTypeAttacked:uint = 31; //玩家被攻击信息
		public static const eTypeExchangedItem:uint = 32; //玩家兑换商品信息
		public static const eTypeSweep:uint = 33; //玩家扫荡信息
		public static const eTypePendRes:uint = 34; //玩家暂存信息
		public static const eTypeXinFaInfo:uint = 35; //心法信息
		public static const eTypeLevelPrize:uint = 36; //心法信息
		public static const eTypeYelloDiamond:uint = 37; //黄钻信息
		public static const eTypeEventInfo:uint = 38; //事件信息
		public static const eTypeBuyItemLimit:uint = 39; //商品数量限购信息
		public static const eTypeDayTarget:uint = 40; //七日目标活动
		public static const eTypeFighterComination:uint = 41; //玩家的散仙组合信息
		public static const eTypeBattleArray:uint = 42; //破阵信息
		public static const eTypeAutoStore:uint = 43; //动态存储信息
		public static const eTypeTH:uint = 44; //寻宝信息
		public static const eTypeBeauty:uint = 45; //美女系统
		public static const eTypeFightFormation:uint = 46; //新阵型系统
		public static const eTypeFightHero:uint = 47; //散仙数据
		public static const eTypeShip:uint = 48; //金船
		public static const eTypeGuardEMei:uint = 49; //守卫峨眉
		public static const eTypeGemstone:uint = 50; //宝石
		public static const eTypeShengLing:uint = 51; //圣陵信息
		public static const eTypeShengLingPrize:uint = 52; //圣陵奖励信息
		public static const eTypeMax:uint = 53; //最大值
		public static const end:uint = eTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTypeRoleBaseInfo:
					return ProtocolMessageProt10.eTypeRoleBaseInfo;
				case eTypeItemInfo:
					return ProtocolMessageProt10.eTypeItemInfo;
				case eTypePlayerDgn:
					return ProtocolMessageProt10.eTypePlayerDgn;
				case eTypeFighterInfo:
					return ProtocolMessageProt10.eTypeFighterInfo;
				case eTypeTaskInfo:
					return ProtocolMessageProt10.eTypeTaskInfo;
				case eTypeSkillInfo:
					return ProtocolMessageProt10.eTypeSkillInfo;
				case eTypePassiveSkillInfo:
					return ProtocolMessageProt10.eTypePassiveSkillInfo;
				case eTypeFriendInfo:
					return ProtocolMessageProt10.eTypeFriendInfo;
				case eTypeVarInfo:
					return ProtocolMessageProt10.eTypeVarInfo;
				case eTypeCittaInfo:
					return ProtocolMessageProt10.eTypeCittaInfo;
				case eTypeSlotsInfo:
					return ProtocolMessageProt10.eTypeSlotsInfo;
				case eTypeTrumpInfo:
					return ProtocolMessageProt10.eTypeTrumpInfo;
				case eTypeEquipTrumpInfo:
					return ProtocolMessageProt10.eTypeEquipTrumpInfo;
				case eTypeEquipTrumpShuffleInfo:
					return ProtocolMessageProt10.eTypeEquipTrumpShuffleInfo;
				case eTypeFormationInfo:
					return ProtocolMessageProt10.eTypeFormationInfo;
				case eTypePetDataInfo:
					return ProtocolMessageProt10.eTypePetDataInfo;
				case eTypeRolePetInfo:
					return ProtocolMessageProt10.eTypeRolePetInfo;
				case eTypeBeastSoulInfo:
					return ProtocolMessageProt10.eTypeBeastSoulInfo;
				case eTypeTripodFireInfo:
					return ProtocolMessageProt10.eTypeTripodFireInfo;
				case eTypeArena:
					return ProtocolMessageProt10.eTypeArena;
				case eTypeBuffInfo:
					return ProtocolMessageProt10.eTypeBuffInfo;
				case eTypeFashionInfo:
					return ProtocolMessageProt10.eTypeFashionInfo;
				case eTypeSoulSpaceInfo:
					return ProtocolMessageProt10.eTypeSoulSpaceInfo;
				case eTypeBubbleInfo:
					return ProtocolMessageProt10.eTypeBubbleInfo;
				case eTypeHorseDBInfo:
					return ProtocolMessageProt10.eTypeHorseDBInfo;
				case eTypeGroupTask:
					return ProtocolMessageProt10.eTypeGroupTask;
				case eTypeYaMenTask:
					return ProtocolMessageProt10.eTypeYaMenTask;
				case eTypeActivityTask:
					return ProtocolMessageProt10.eTypeActivityTask;
				case eTypeTitle:
					return ProtocolMessageProt10.eTypeTitle;
				case eTypeAchievementInfo:
					return ProtocolMessageProt10.eTypeAchievementInfo;
				case eTypeCollectionInfo:
					return ProtocolMessageProt10.eTypeCollectionInfo;
				case eTypeAttacked:
					return ProtocolMessageProt10.eTypeAttacked;
				case eTypeExchangedItem:
					return ProtocolMessageProt10.eTypeExchangedItem;
				case eTypeSweep:
					return ProtocolMessageProt10.eTypeSweep;
				case eTypePendRes:
					return ProtocolMessageProt10.eTypePendRes;
				case eTypeXinFaInfo:
					return ProtocolMessageProt10.eTypeXinFaInfo;
				case eTypeLevelPrize:
					return ProtocolMessageProt10.eTypeLevelPrize;
				case eTypeYelloDiamond:
					return ProtocolMessageProt10.eTypeYelloDiamond;
				case eTypeEventInfo:
					return ProtocolMessageProt10.eTypeEventInfo;
				case eTypeBuyItemLimit:
					return ProtocolMessageProt10.eTypeBuyItemLimit;
				case eTypeDayTarget:
					return ProtocolMessageProt10.eTypeDayTarget;
				case eTypeFighterComination:
					return ProtocolMessageProt10.eTypeFighterComination;
				case eTypeBattleArray:
					return ProtocolMessageProt10.eTypeBattleArray;
				case eTypeAutoStore:
					return ProtocolMessageProt10.eTypeAutoStore;
				case eTypeTH:
					return ProtocolMessageProt10.eTypeTH;
				case eTypeBeauty:
					return ProtocolMessageProt10.eTypeBeauty;
				case eTypeFightFormation:
					return ProtocolMessageProt10.eTypeFightFormation;
				case eTypeFightHero:
					return ProtocolMessageProt10.eTypeFightHero;
				case eTypeShip:
					return ProtocolMessageProt10.eTypeShip;
				case eTypeGuardEMei:
					return ProtocolMessageProt10.eTypeGuardEMei;
				case eTypeGemstone:
					return ProtocolMessageProt10.eTypeGemstone;
				case eTypeShengLing:
					return ProtocolMessageProt10.eTypeShengLing;
				case eTypeShengLingPrize:
					return ProtocolMessageProt10.eTypeShengLingPrize;
				case eTypeMax:
					return ProtocolMessageProt10.eTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
