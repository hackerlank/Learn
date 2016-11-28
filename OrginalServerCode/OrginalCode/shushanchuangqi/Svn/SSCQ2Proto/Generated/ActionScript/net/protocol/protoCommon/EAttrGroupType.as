/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAttrGroupType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 属性加成类型
	 */
	public final class EAttrGroupType
	{
		public static const eAttrGpMin:uint = 0; //属性加成
		public static const eAttrGpPlayerBegin:uint = 1; //主将属性加成开始---
		public static const eAttrGpFashion:uint = 2; //时装属性加成
		public static const eAttrGpTitle:uint = 3; //称号属性加成
		public static const eAttrGpCitta:uint = 4; //心法属性加成
		public static const eAttrGpPlayerEnd:uint = 5; //主将加成属性结束-----
		public static const eAttrGpHeroBegin:uint = 6; //散仙加成属性开始
		public static const eAttrGpEquipTrump:uint = 7; //装备法宝属性加成
		public static const eAttrGpGemstone:uint = 8; //宝石属性加成
		public static const eAttrGpHeroEnd:uint = 9; //散仙加成属性结束
		public static const eAttrGpHeroAndPlayerBegin:uint = 10; //全员加成属性开始--
		public static const eAttrGpTrumpActive:uint = 11; //法宝激活属性加成
		public static const eAttrGpTrumpExtra:uint = 12; //法宝附加属性加成
		public static const eAttrGpTrumpHalo:uint = 13; //法宝光环属性加成
		public static const eAttrGpHorse:uint = 14; //坐骑属性加成
		public static const eAttrGpShushanBattle:uint = 15; //蜀山论剑属性加成
		public static const eAttrGpBag:uint = 16; //背包解锁的属性加成
		public static const eAttrGpAchievement:uint = 17; //成就属性加成
		public static const eAttrGpCollection:uint = 18; //收集属性加成
		public static const eAttrGpFormation:uint = 19; //阵形属性加成
		public static const eAttrGpPet:uint = 20; //阵灵属性加成
		public static const eAttrGpBeastSoul:uint = 21; //兽魂
		public static const eAttrGpGuildTech:uint = 22; //帮派技能加成
		public static const eAttrGpBuffer:uint = 23; //外部buffer属性加成
		public static const eAttrGpTripod:uint = 24; //九疑鼎属性加成
		public static const eAttrGpFighterCombination:uint = 25; //散仙组合属性加成
		public static const eAttrBeauty:uint = 26; //美女系统
		public static const eAttrGpHeroAndPlayerEnd:uint = 27; //全员加成属性结束--
		public static const eAttrGpMax:uint = 28; //属性加成
		public static const end:uint = eAttrGpMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAttrGpMin:
					return ProtocolMessageProt258.eAttrGpMin;
				case eAttrGpPlayerBegin:
					return ProtocolMessageProt258.eAttrGpPlayerBegin;
				case eAttrGpFashion:
					return ProtocolMessageProt258.eAttrGpFashion;
				case eAttrGpTitle:
					return ProtocolMessageProt258.eAttrGpTitle;
				case eAttrGpCitta:
					return ProtocolMessageProt258.eAttrGpCitta;
				case eAttrGpPlayerEnd:
					return ProtocolMessageProt258.eAttrGpPlayerEnd;
				case eAttrGpHeroBegin:
					return ProtocolMessageProt258.eAttrGpHeroBegin;
				case eAttrGpEquipTrump:
					return ProtocolMessageProt258.eAttrGpEquipTrump;
				case eAttrGpGemstone:
					return ProtocolMessageProt258.eAttrGpGemstone;
				case eAttrGpHeroEnd:
					return ProtocolMessageProt258.eAttrGpHeroEnd;
				case eAttrGpHeroAndPlayerBegin:
					return ProtocolMessageProt258.eAttrGpHeroAndPlayerBegin;
				case eAttrGpTrumpActive:
					return ProtocolMessageProt258.eAttrGpTrumpActive;
				case eAttrGpTrumpExtra:
					return ProtocolMessageProt258.eAttrGpTrumpExtra;
				case eAttrGpTrumpHalo:
					return ProtocolMessageProt258.eAttrGpTrumpHalo;
				case eAttrGpHorse:
					return ProtocolMessageProt258.eAttrGpHorse;
				case eAttrGpShushanBattle:
					return ProtocolMessageProt258.eAttrGpShushanBattle;
				case eAttrGpBag:
					return ProtocolMessageProt258.eAttrGpBag;
				case eAttrGpAchievement:
					return ProtocolMessageProt258.eAttrGpAchievement;
				case eAttrGpCollection:
					return ProtocolMessageProt258.eAttrGpCollection;
				case eAttrGpFormation:
					return ProtocolMessageProt258.eAttrGpFormation;
				case eAttrGpPet:
					return ProtocolMessageProt258.eAttrGpPet;
				case eAttrGpBeastSoul:
					return ProtocolMessageProt258.eAttrGpBeastSoul;
				case eAttrGpGuildTech:
					return ProtocolMessageProt258.eAttrGpGuildTech;
				case eAttrGpBuffer:
					return ProtocolMessageProt258.eAttrGpBuffer;
				case eAttrGpTripod:
					return ProtocolMessageProt258.eAttrGpTripod;
				case eAttrGpFighterCombination:
					return ProtocolMessageProt258.eAttrGpFighterCombination;
				case eAttrBeauty:
					return ProtocolMessageProt258.eAttrBeauty;
				case eAttrGpHeroAndPlayerEnd:
					return ProtocolMessageProt258.eAttrGpHeroAndPlayerEnd;
				case eAttrGpMax:
					return ProtocolMessageProt258.eAttrGpMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
