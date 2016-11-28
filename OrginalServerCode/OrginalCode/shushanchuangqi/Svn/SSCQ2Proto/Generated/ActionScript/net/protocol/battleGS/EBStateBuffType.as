/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBStateBuffType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * State效果枚举
	 */
	public final class EBStateBuffType
	{
		public static const EBFBuffTypeNone:uint = 0; //无状态
		public static const EBFBuffTypeMin:uint = 0; //出手时状态枚举最小值
		public static const EBFBuffTypeStun:uint = 1; //眩晕
		public static const EBFBuffTypeConfuse:uint = 2; //混乱
		public static const EBFBuffTypeCover:uint = 3; //掩护
		public static const EBFBuffTypeEShock:uint = 4; //电击
		public static const EBFBuffTypeBlock:uint = 5; //格挡
		public static const EBFBuffTypeInvincible:uint = 6; //无敌
		public static const EBFBuffTypeShield:uint = 7; //护盾
		public static const EBFBuffTypePierce:uint = 8; //破甲
		public static const EBFBuffTypeBleed:uint = 9; //流血
		public static const EBFBuffTypeForget:uint = 10; //沉默
		public static const EBFBuffTypeFreeze:uint = 11; //冻结
		public static const EBFBuffTypeBurned:uint = 12; //点燃
		public static const EBFBuffTypeAtkAdd:uint = 13; //攻击提升
		public static const EBFBuffTypeAtkSub:uint = 14; //攻击下降
		public static const EBFBuffTypeRedAdd:uint = 15; //免伤提升
		public static const EBFBuffTypeRedSub:uint = 16; //免伤下降
		public static const EBFBuffTypeStoned:uint = 17; //石化
		public static const EBFBuffTypePoison:uint = 18; //中毒
		public static const EBFBuffTypeHide:uint = 19; //影遁
		public static const EBFBuffTypeBronze:uint = 20; //铜人
		public static const EBFBuffTypeKingkong:uint = 21; //金刚
		public static const EBFBuffTypeDmgReduce:uint = 22; //伤害减少
		public static const EBFBuffTypeDmgAdd:uint = 23; //伤害提升
		public static const EBFBuffTypeCongest:uint = 24; //蓄力
		public static const EBFBuffTypeReflect:uint = 25; //反弹状态
		public static const EBFBuffTypeHitDown:uint = 26; //命中降低
		public static const EBFBuffTypeClone:uint = 27; //分身
		public static const EBFBuffTypeSealed:uint = 28; //封印
		public static const EBFBuffTypeBeDmgReudce:uint = 29; //伤害减免
		public static const EBFBuffTypeBlind:uint = 30; //致盲
		public static const EBFBuffTypeSmoke:uint = 31; //烟幕
		public static const EBFBuffTypeGuard:uint = 32; //护卫
		public static const EBFBuffTypeKindKing:uint = 33; //仁王
		public static const EBFBuffTypeBlunt:uint = 34; //麻痹
		public static const EBFBuffTypeIceBlade:uint = 35; //冰刃
		public static const EBFBuffTypeThunderBlade:uint = 36; //雷刃
		public static const EBFBuffTypeFireBlade:uint = 37; //炎刃
		public static const EBFBuffTypeSnowSoul:uint = 38; //雪魂
		public static const EBFBuffTypeHaloRed:uint = 39; //光环红
		public static const EBFBuffTypeHaloBlue:uint = 40; //光环蓝
		public static const EBFBuffTypeDrogenSting:uint = 41; //龙刺
		public static const EBFBuffTypeDmgShare:uint = 42; //伤害分担
		public static const EBFBuffTypeAttrAdd:uint = 43; //属性增益
		public static const EBFBuffTypeAttrSub:uint = 44; //属性减益
		public static const EBFBuffTypeActAtkAdd:uint = 45; //行动后攻击增加
		public static const EBFBuffTypeActDefAdd:uint = 46; //行动后防御增加
		public static const EBFBuffTypeMax:uint = 47; //状态最大值
		public static const end:uint = EBFBuffTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBFBuffTypeNone:
					return ProtocolMessageProt21.EBFBuffTypeNone;
				case EBFBuffTypeStun:
					return ProtocolMessageProt21.EBFBuffTypeStun;
				case EBFBuffTypeConfuse:
					return ProtocolMessageProt21.EBFBuffTypeConfuse;
				case EBFBuffTypeCover:
					return ProtocolMessageProt21.EBFBuffTypeCover;
				case EBFBuffTypeEShock:
					return ProtocolMessageProt21.EBFBuffTypeEShock;
				case EBFBuffTypeBlock:
					return ProtocolMessageProt21.EBFBuffTypeBlock;
				case EBFBuffTypeInvincible:
					return ProtocolMessageProt21.EBFBuffTypeInvincible;
				case EBFBuffTypeShield:
					return ProtocolMessageProt21.EBFBuffTypeShield;
				case EBFBuffTypePierce:
					return ProtocolMessageProt21.EBFBuffTypePierce;
				case EBFBuffTypeBleed:
					return ProtocolMessageProt21.EBFBuffTypeBleed;
				case EBFBuffTypeForget:
					return ProtocolMessageProt21.EBFBuffTypeForget;
				case EBFBuffTypeFreeze:
					return ProtocolMessageProt21.EBFBuffTypeFreeze;
				case EBFBuffTypeBurned:
					return ProtocolMessageProt21.EBFBuffTypeBurned;
				case EBFBuffTypeAtkAdd:
					return ProtocolMessageProt21.EBFBuffTypeAtkAdd;
				case EBFBuffTypeAtkSub:
					return ProtocolMessageProt21.EBFBuffTypeAtkSub;
				case EBFBuffTypeRedAdd:
					return ProtocolMessageProt21.EBFBuffTypeRedAdd;
				case EBFBuffTypeRedSub:
					return ProtocolMessageProt21.EBFBuffTypeRedSub;
				case EBFBuffTypeStoned:
					return ProtocolMessageProt21.EBFBuffTypeStoned;
				case EBFBuffTypePoison:
					return ProtocolMessageProt21.EBFBuffTypePoison;
				case EBFBuffTypeHide:
					return ProtocolMessageProt21.EBFBuffTypeHide;
				case EBFBuffTypeBronze:
					return ProtocolMessageProt21.EBFBuffTypeBronze;
				case EBFBuffTypeKingkong:
					return ProtocolMessageProt21.EBFBuffTypeKingkong;
				case EBFBuffTypeDmgReduce:
					return ProtocolMessageProt21.EBFBuffTypeDmgReduce;
				case EBFBuffTypeDmgAdd:
					return ProtocolMessageProt21.EBFBuffTypeDmgAdd;
				case EBFBuffTypeCongest:
					return ProtocolMessageProt21.EBFBuffTypeCongest;
				case EBFBuffTypeReflect:
					return ProtocolMessageProt21.EBFBuffTypeReflect;
				case EBFBuffTypeHitDown:
					return ProtocolMessageProt21.EBFBuffTypeHitDown;
				case EBFBuffTypeClone:
					return ProtocolMessageProt21.EBFBuffTypeClone;
				case EBFBuffTypeSealed:
					return ProtocolMessageProt21.EBFBuffTypeSealed;
				case EBFBuffTypeBeDmgReudce:
					return ProtocolMessageProt21.EBFBuffTypeBeDmgReudce;
				case EBFBuffTypeBlind:
					return ProtocolMessageProt21.EBFBuffTypeBlind;
				case EBFBuffTypeSmoke:
					return ProtocolMessageProt21.EBFBuffTypeSmoke;
				case EBFBuffTypeGuard:
					return ProtocolMessageProt21.EBFBuffTypeGuard;
				case EBFBuffTypeKindKing:
					return ProtocolMessageProt21.EBFBuffTypeKindKing;
				case EBFBuffTypeBlunt:
					return ProtocolMessageProt21.EBFBuffTypeBlunt;
				case EBFBuffTypeIceBlade:
					return ProtocolMessageProt21.EBFBuffTypeIceBlade;
				case EBFBuffTypeThunderBlade:
					return ProtocolMessageProt21.EBFBuffTypeThunderBlade;
				case EBFBuffTypeFireBlade:
					return ProtocolMessageProt21.EBFBuffTypeFireBlade;
				case EBFBuffTypeSnowSoul:
					return ProtocolMessageProt21.EBFBuffTypeSnowSoul;
				case EBFBuffTypeHaloRed:
					return ProtocolMessageProt21.EBFBuffTypeHaloRed;
				case EBFBuffTypeHaloBlue:
					return ProtocolMessageProt21.EBFBuffTypeHaloBlue;
				case EBFBuffTypeDrogenSting:
					return ProtocolMessageProt21.EBFBuffTypeDrogenSting;
				case EBFBuffTypeDmgShare:
					return ProtocolMessageProt21.EBFBuffTypeDmgShare;
				case EBFBuffTypeAttrAdd:
					return ProtocolMessageProt21.EBFBuffTypeAttrAdd;
				case EBFBuffTypeAttrSub:
					return ProtocolMessageProt21.EBFBuffTypeAttrSub;
				case EBFBuffTypeActAtkAdd:
					return ProtocolMessageProt21.EBFBuffTypeActAtkAdd;
				case EBFBuffTypeActDefAdd:
					return ProtocolMessageProt21.EBFBuffTypeActDefAdd;
				case EBFBuffTypeMax:
					return ProtocolMessageProt21.EBFBuffTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
