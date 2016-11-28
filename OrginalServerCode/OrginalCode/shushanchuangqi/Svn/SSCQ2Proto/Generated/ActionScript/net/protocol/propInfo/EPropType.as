/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPropType.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
 {
	import net.protocol.Message.ProtocolMessageProt17;
	/**
	 * 属性的类型
	 */
	public final class EPropType
	{
		public static const ePropNone:uint = 0; //无
		public static const ePropGold:uint = 1; //仙石
		public static const ePropSilver:uint = 2; //银币
		public static const ePropCoupon:uint = 3; //礼券
		public static const eProppGiftCoin:uint = 4; //金券
		public static const ePropExpTemp:uint = 5; //经验(占位)
		public static const ePropPrestige:uint = 6; //声望
		public static const ePropSoul:uint = 7; //魂魄
		public static const ePropHonor:uint = 8; //荣誉
		public static const ePropPExp:uint = 9; //修为
		public static const ePropSigil:uint = 10; //符印
		public static const ePropCentsY:uint = 11; //仙元
		public static const ePropAction:uint = 12; //体力
		public static const ePropSop:uint = 13; //阅历
		public static const ePropTaoism:uint = 14; //道术
		public static const ePropPoten:uint = 15; //渡劫点数
		public static const ePropReiki:uint = 16; //副本星级
		public static const ePropHFP:uint = 17; //寻仙积分
		public static const ePropDemonSoul:uint = 18; //锁妖塔魂值
		public static const ePropSoulAttack:uint = 19; //攻击之魂
		public static const ePropSoulHp:uint = 20; //生命之魂
		public static const ePropSoulCritical:uint = 21; //暴击之魂
		public static const ePropSoulCounter:uint = 22; //反击之魂
		public static const ePropSoulSpeed:uint = 23; //身法之魂
		public static const ePropSoulDefence:uint = 24; //防御之魂
		public static const ePropSoulHit:uint = 25; //命中之魂
		public static const ePropSoulDodge:uint = 26; //闪避之魂
		public static const ePropAchievementAP:uint = 27; //成就点
		public static const ePropCollectAP:uint = 28; //收藏点
		public static const ePropGuildContrib:uint = 29; //帮派贡献
		public static const ePropStampHuang:uint = 30; //黄阶除魔印
		public static const ePropStampXuan:uint = 31; //玄阶除魔印
		public static const ePropStampDi:uint = 32; //地阶除魔印
		public static const ePropStampTian:uint = 33; //天阶除魔印
		public static const ePropStampXing:uint = 34; //星阶除魔印
		public static const ePropStampYue:uint = 35; //月阶除魔印
		public static const ePropStampDi2:uint = 36; //帝阶除魔印
		public static const ePropStampXian:uint = 37; //仙阶除魔印
		public static const ePropStampSheng:uint = 38; //圣阶除魔印
		public static const ePropStampFo:uint = 39; //佛阶除魔印
		public static const ePropLoveHeart:uint = 40; //爱心
		public static const ePropBlueFairyFate:uint = 51; //蓝色仙缘
		public static const ePropPurpleFairyFate:uint = 52; //紫色仙缘
		public static const ePropOrangeFairyFate:uint = 53; //橙色仙缘
		public static const ePropDuJieFu:uint = 56; //渡劫符
		public static const ePropLuckyCoupon:uint = 57; //抽奖券
		public static const ePropMoneyEnd:uint = 100; //钱币属性结束标志
		public static const ePropCommon:uint = 200; //普通定义
		public static const ePropTotalRecharge:uint = 201; //总充值数
		public static const ePropBTPoint:uint = 202; //战斗力
		public static const ePropHero:uint = 300; //将定义
		public static const ePropPos:uint = 301; //将在阵型中的位置
		public static const ePropTroopPos:uint = 302; //将在队伍中的位置
		public static const ePropPotential:uint = 303; //潜力
		public static const ePropCapacity:uint = 304; //资质
		public static const ePropLevel:uint = 305; //等级
		public static const ePropLucky:uint = 306; //机缘值
		public static const ePropExp:uint = 307; //经验 -- UINT64
		public static const ePropLianPi:uint = 308; //炼皮
		public static const ePropTongJin:uint = 309; //通筋
		public static const ePropQiangJi:uint = 310; //强肌
		public static const ePropDuanGu:uint = 311; //锻骨
		public static const ePropMax:uint = 312; //属性枚举最大值
		public static const end:uint = ePropMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePropNone:
					return ProtocolMessageProt17.ePropNone;
				case ePropGold:
					return ProtocolMessageProt17.ePropGold;
				case ePropSilver:
					return ProtocolMessageProt17.ePropSilver;
				case ePropCoupon:
					return ProtocolMessageProt17.ePropCoupon;
				case eProppGiftCoin:
					return ProtocolMessageProt17.eProppGiftCoin;
				case ePropExpTemp:
					return ProtocolMessageProt17.ePropExpTemp;
				case ePropPrestige:
					return ProtocolMessageProt17.ePropPrestige;
				case ePropSoul:
					return ProtocolMessageProt17.ePropSoul;
				case ePropHonor:
					return ProtocolMessageProt17.ePropHonor;
				case ePropPExp:
					return ProtocolMessageProt17.ePropPExp;
				case ePropSigil:
					return ProtocolMessageProt17.ePropSigil;
				case ePropCentsY:
					return ProtocolMessageProt17.ePropCentsY;
				case ePropAction:
					return ProtocolMessageProt17.ePropAction;
				case ePropSop:
					return ProtocolMessageProt17.ePropSop;
				case ePropTaoism:
					return ProtocolMessageProt17.ePropTaoism;
				case ePropPoten:
					return ProtocolMessageProt17.ePropPoten;
				case ePropReiki:
					return ProtocolMessageProt17.ePropReiki;
				case ePropHFP:
					return ProtocolMessageProt17.ePropHFP;
				case ePropDemonSoul:
					return ProtocolMessageProt17.ePropDemonSoul;
				case ePropSoulAttack:
					return ProtocolMessageProt17.ePropSoulAttack;
				case ePropSoulHp:
					return ProtocolMessageProt17.ePropSoulHp;
				case ePropSoulCritical:
					return ProtocolMessageProt17.ePropSoulCritical;
				case ePropSoulCounter:
					return ProtocolMessageProt17.ePropSoulCounter;
				case ePropSoulSpeed:
					return ProtocolMessageProt17.ePropSoulSpeed;
				case ePropSoulDefence:
					return ProtocolMessageProt17.ePropSoulDefence;
				case ePropSoulHit:
					return ProtocolMessageProt17.ePropSoulHit;
				case ePropSoulDodge:
					return ProtocolMessageProt17.ePropSoulDodge;
				case ePropAchievementAP:
					return ProtocolMessageProt17.ePropAchievementAP;
				case ePropCollectAP:
					return ProtocolMessageProt17.ePropCollectAP;
				case ePropGuildContrib:
					return ProtocolMessageProt17.ePropGuildContrib;
				case ePropStampHuang:
					return ProtocolMessageProt17.ePropStampHuang;
				case ePropStampXuan:
					return ProtocolMessageProt17.ePropStampXuan;
				case ePropStampDi:
					return ProtocolMessageProt17.ePropStampDi;
				case ePropStampTian:
					return ProtocolMessageProt17.ePropStampTian;
				case ePropStampXing:
					return ProtocolMessageProt17.ePropStampXing;
				case ePropStampYue:
					return ProtocolMessageProt17.ePropStampYue;
				case ePropStampDi2:
					return ProtocolMessageProt17.ePropStampDi2;
				case ePropStampXian:
					return ProtocolMessageProt17.ePropStampXian;
				case ePropStampSheng:
					return ProtocolMessageProt17.ePropStampSheng;
				case ePropStampFo:
					return ProtocolMessageProt17.ePropStampFo;
				case ePropLoveHeart:
					return ProtocolMessageProt17.ePropLoveHeart;
				case ePropBlueFairyFate:
					return ProtocolMessageProt17.ePropBlueFairyFate;
				case ePropPurpleFairyFate:
					return ProtocolMessageProt17.ePropPurpleFairyFate;
				case ePropOrangeFairyFate:
					return ProtocolMessageProt17.ePropOrangeFairyFate;
				case ePropDuJieFu:
					return ProtocolMessageProt17.ePropDuJieFu;
				case ePropLuckyCoupon:
					return ProtocolMessageProt17.ePropLuckyCoupon;
				case ePropMoneyEnd:
					return ProtocolMessageProt17.ePropMoneyEnd;
				case ePropCommon:
					return ProtocolMessageProt17.ePropCommon;
				case ePropTotalRecharge:
					return ProtocolMessageProt17.ePropTotalRecharge;
				case ePropBTPoint:
					return ProtocolMessageProt17.ePropBTPoint;
				case ePropHero:
					return ProtocolMessageProt17.ePropHero;
				case ePropPos:
					return ProtocolMessageProt17.ePropPos;
				case ePropTroopPos:
					return ProtocolMessageProt17.ePropTroopPos;
				case ePropPotential:
					return ProtocolMessageProt17.ePropPotential;
				case ePropCapacity:
					return ProtocolMessageProt17.ePropCapacity;
				case ePropLevel:
					return ProtocolMessageProt17.ePropLevel;
				case ePropLucky:
					return ProtocolMessageProt17.ePropLucky;
				case ePropExp:
					return ProtocolMessageProt17.ePropExp;
				case ePropLianPi:
					return ProtocolMessageProt17.ePropLianPi;
				case ePropTongJin:
					return ProtocolMessageProt17.ePropTongJin;
				case ePropQiangJi:
					return ProtocolMessageProt17.ePropQiangJi;
				case ePropDuanGu:
					return ProtocolMessageProt17.ePropDuanGu;
				case ePropMax:
					return ProtocolMessageProt17.ePropMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
