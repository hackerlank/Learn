/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFighterAttr.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 属性枚举
	 */
	public final class EFighterAttr
	{
		public static const EFIGHTATTR_MIN:uint = 0; //属性枚举最小值
		public static const EFIGHTATTR_PHYATK:uint = 1; //物理攻击
		public static const EFIGHTATTR_MGCATK:uint = 2; //法术攻击
		public static const EFIGHTATTR_PHYDEF:uint = 3; //物理防御
		public static const EFIGHTATTR_MGCDEF:uint = 4; //法术防御
		public static const EFIGHTATTR_PHYRDC:uint = 5; //物理免伤
		public static const EFIGHTATTR_MGCRDC:uint = 6; //魔法免伤
		public static const EFIGHTATTR_MAXHP:uint = 7; //最大生命
		public static const EFIGHTATTR_SPEED:uint = 8; //身法
		public static const EFIGHTATTR_HIT:uint = 9; //命中值
		public static const EFIGHTATTR_HITRATE:uint = 10; //命中率
		public static const EFIGHTATTR_DODGE:uint = 11; //闪避值
		public static const EFIGHTATTR_DODGERATE:uint = 12; //闪避率
		public static const EFIGHTATTR_CRITICAL:uint = 13; //暴击值
		public static const EFIGHTATTR_CRTRATE:uint = 14; //暴击率
		public static const EFIGHTATTR_ANTICRITCAL:uint = 15; //稳固值
		public static const EFIGHTATTR_ANTICRTRATE:uint = 16; //稳固率
		public static const EFIGHTATTR_BLOCK:uint = 17; //格挡值
		public static const EFIGHTATTR_BLOCKRATE:uint = 18; //格挡率
		public static const EFIGHTATTR_PIERCE:uint = 19; //穿透值
		public static const EFIGHTATTR_PIERCERATE:uint = 20; //穿透率
		public static const EFIGHTATTR_COUNTER:uint = 21; //反击值
		public static const EFIGHTATTR_COUNTERRATE:uint = 22; //反击率
		public static const EFIGHTATTR_RESIST:uint = 23; //压制值
		public static const EFIGHTATTR_RESISTRATE:uint = 24; //压制率
		public static const EFIGHTATTR_INITAURA:uint = 25; //入场灵气
		public static const EFIGHTATTR_MAXAURA:uint = 26; //最大灵气
		public static const EFIGHTATTR_CRIEXTRAADD:uint = 27; //暴击伤害增加
		public static const EFIGHTATTR_CRIEXTRARDC:uint = 28; //暴击伤害减免
		public static const EFIGHTATTR_METALATK:uint = 29; //金攻
		public static const EFIGHTATTR_WOODATK:uint = 30; //木攻
		public static const EFIGHTATTR_WATERATK:uint = 31; //水攻
		public static const EFIGHTATTR_FIREATK:uint = 32; //火攻
		public static const EFIGHTATTR_EARTHATK:uint = 33; //土攻
		public static const EFIGHTATTR_METALDEF:uint = 34; //金防
		public static const EFIGHTATTR_WOODDEF:uint = 35; //木防
		public static const EFIGHTATTR_WATERDEF:uint = 36; //水防
		public static const EFIGHTATTR_FIREDEF:uint = 37; //火防
		public static const EFIGHTATTR_EARTHDEF:uint = 38; //土防
		public static const EFIGHTATTR_PHYATK_PER:uint = 39; //物理攻击%
		public static const EFIGHTATTR_MGCATK_PER:uint = 40; //法术攻击%
		public static const EFIGHTATTR_PHYDEF_PER:uint = 41; //物理防御%
		public static const EFIGHTATTR_MGCDEF_PER:uint = 42; //法术防御%
		public static const EFIGHTATTR_MAXHP_PER:uint = 43; //最大生命%
		public static const EFIGHTATTR_SPEED_PER:uint = 44; //身法%
		public static const EFIGHTATTR_HIT_PER:uint = 45; //命中值%
		public static const EFIGHTATTR_DODGE_PER:uint = 46; //闪避值%
		public static const EFIGHTATTR_CRITICAL_PER:uint = 47; //暴击值%
		public static const EFIGHTATTR_ANTICRITCAL_PER:uint = 48; //稳固值%
		public static const EFIGHTATTR_BLOCK_PER:uint = 49; //格挡值%
		public static const EFIGHTATTR_PIERCE_PER:uint = 50; //穿透值%
		public static const EFIGHTATTR_COUNTER_PER:uint = 51; //反击值%
		public static const EFIGHTATTR_RESIST_PER:uint = 52; //压制值%
		public static const EFIGHTATTR_ANTIEFFECT:uint = 53; //法术抵抗
		public static const EFIGHTATTR_COUTEREXTRAADD:uint = 54; //反击伤害增加
		public static const EFIGHTATTR_COUTEREXTRARDC:uint = 55; //反击伤害减免
		public static const EFIGHTATTR_MAX:uint = 56; //属性枚举最大值
		public static const end:uint = EFIGHTATTR_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EFIGHTATTR_MIN:
					return ProtocolMessageProt258.EFIGHTATTR_MIN;
				case EFIGHTATTR_PHYATK:
					return ProtocolMessageProt258.EFIGHTATTR_PHYATK;
				case EFIGHTATTR_MGCATK:
					return ProtocolMessageProt258.EFIGHTATTR_MGCATK;
				case EFIGHTATTR_PHYDEF:
					return ProtocolMessageProt258.EFIGHTATTR_PHYDEF;
				case EFIGHTATTR_MGCDEF:
					return ProtocolMessageProt258.EFIGHTATTR_MGCDEF;
				case EFIGHTATTR_PHYRDC:
					return ProtocolMessageProt258.EFIGHTATTR_PHYRDC;
				case EFIGHTATTR_MGCRDC:
					return ProtocolMessageProt258.EFIGHTATTR_MGCRDC;
				case EFIGHTATTR_MAXHP:
					return ProtocolMessageProt258.EFIGHTATTR_MAXHP;
				case EFIGHTATTR_SPEED:
					return ProtocolMessageProt258.EFIGHTATTR_SPEED;
				case EFIGHTATTR_HIT:
					return ProtocolMessageProt258.EFIGHTATTR_HIT;
				case EFIGHTATTR_HITRATE:
					return ProtocolMessageProt258.EFIGHTATTR_HITRATE;
				case EFIGHTATTR_DODGE:
					return ProtocolMessageProt258.EFIGHTATTR_DODGE;
				case EFIGHTATTR_DODGERATE:
					return ProtocolMessageProt258.EFIGHTATTR_DODGERATE;
				case EFIGHTATTR_CRITICAL:
					return ProtocolMessageProt258.EFIGHTATTR_CRITICAL;
				case EFIGHTATTR_CRTRATE:
					return ProtocolMessageProt258.EFIGHTATTR_CRTRATE;
				case EFIGHTATTR_ANTICRITCAL:
					return ProtocolMessageProt258.EFIGHTATTR_ANTICRITCAL;
				case EFIGHTATTR_ANTICRTRATE:
					return ProtocolMessageProt258.EFIGHTATTR_ANTICRTRATE;
				case EFIGHTATTR_BLOCK:
					return ProtocolMessageProt258.EFIGHTATTR_BLOCK;
				case EFIGHTATTR_BLOCKRATE:
					return ProtocolMessageProt258.EFIGHTATTR_BLOCKRATE;
				case EFIGHTATTR_PIERCE:
					return ProtocolMessageProt258.EFIGHTATTR_PIERCE;
				case EFIGHTATTR_PIERCERATE:
					return ProtocolMessageProt258.EFIGHTATTR_PIERCERATE;
				case EFIGHTATTR_COUNTER:
					return ProtocolMessageProt258.EFIGHTATTR_COUNTER;
				case EFIGHTATTR_COUNTERRATE:
					return ProtocolMessageProt258.EFIGHTATTR_COUNTERRATE;
				case EFIGHTATTR_RESIST:
					return ProtocolMessageProt258.EFIGHTATTR_RESIST;
				case EFIGHTATTR_RESISTRATE:
					return ProtocolMessageProt258.EFIGHTATTR_RESISTRATE;
				case EFIGHTATTR_INITAURA:
					return ProtocolMessageProt258.EFIGHTATTR_INITAURA;
				case EFIGHTATTR_MAXAURA:
					return ProtocolMessageProt258.EFIGHTATTR_MAXAURA;
				case EFIGHTATTR_CRIEXTRAADD:
					return ProtocolMessageProt258.EFIGHTATTR_CRIEXTRAADD;
				case EFIGHTATTR_CRIEXTRARDC:
					return ProtocolMessageProt258.EFIGHTATTR_CRIEXTRARDC;
				case EFIGHTATTR_METALATK:
					return ProtocolMessageProt258.EFIGHTATTR_METALATK;
				case EFIGHTATTR_WOODATK:
					return ProtocolMessageProt258.EFIGHTATTR_WOODATK;
				case EFIGHTATTR_WATERATK:
					return ProtocolMessageProt258.EFIGHTATTR_WATERATK;
				case EFIGHTATTR_FIREATK:
					return ProtocolMessageProt258.EFIGHTATTR_FIREATK;
				case EFIGHTATTR_EARTHATK:
					return ProtocolMessageProt258.EFIGHTATTR_EARTHATK;
				case EFIGHTATTR_METALDEF:
					return ProtocolMessageProt258.EFIGHTATTR_METALDEF;
				case EFIGHTATTR_WOODDEF:
					return ProtocolMessageProt258.EFIGHTATTR_WOODDEF;
				case EFIGHTATTR_WATERDEF:
					return ProtocolMessageProt258.EFIGHTATTR_WATERDEF;
				case EFIGHTATTR_FIREDEF:
					return ProtocolMessageProt258.EFIGHTATTR_FIREDEF;
				case EFIGHTATTR_EARTHDEF:
					return ProtocolMessageProt258.EFIGHTATTR_EARTHDEF;
				case EFIGHTATTR_PHYATK_PER:
					return ProtocolMessageProt258.EFIGHTATTR_PHYATK_PER;
				case EFIGHTATTR_MGCATK_PER:
					return ProtocolMessageProt258.EFIGHTATTR_MGCATK_PER;
				case EFIGHTATTR_PHYDEF_PER:
					return ProtocolMessageProt258.EFIGHTATTR_PHYDEF_PER;
				case EFIGHTATTR_MGCDEF_PER:
					return ProtocolMessageProt258.EFIGHTATTR_MGCDEF_PER;
				case EFIGHTATTR_MAXHP_PER:
					return ProtocolMessageProt258.EFIGHTATTR_MAXHP_PER;
				case EFIGHTATTR_SPEED_PER:
					return ProtocolMessageProt258.EFIGHTATTR_SPEED_PER;
				case EFIGHTATTR_HIT_PER:
					return ProtocolMessageProt258.EFIGHTATTR_HIT_PER;
				case EFIGHTATTR_DODGE_PER:
					return ProtocolMessageProt258.EFIGHTATTR_DODGE_PER;
				case EFIGHTATTR_CRITICAL_PER:
					return ProtocolMessageProt258.EFIGHTATTR_CRITICAL_PER;
				case EFIGHTATTR_ANTICRITCAL_PER:
					return ProtocolMessageProt258.EFIGHTATTR_ANTICRITCAL_PER;
				case EFIGHTATTR_BLOCK_PER:
					return ProtocolMessageProt258.EFIGHTATTR_BLOCK_PER;
				case EFIGHTATTR_PIERCE_PER:
					return ProtocolMessageProt258.EFIGHTATTR_PIERCE_PER;
				case EFIGHTATTR_COUNTER_PER:
					return ProtocolMessageProt258.EFIGHTATTR_COUNTER_PER;
				case EFIGHTATTR_RESIST_PER:
					return ProtocolMessageProt258.EFIGHTATTR_RESIST_PER;
				case EFIGHTATTR_ANTIEFFECT:
					return ProtocolMessageProt258.EFIGHTATTR_ANTIEFFECT;
				case EFIGHTATTR_COUTEREXTRAADD:
					return ProtocolMessageProt258.EFIGHTATTR_COUTEREXTRAADD;
				case EFIGHTATTR_COUTEREXTRARDC:
					return ProtocolMessageProt258.EFIGHTATTR_COUTEREXTRARDC;
				case EFIGHTATTR_MAX:
					return ProtocolMessageProt258.EFIGHTATTR_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
