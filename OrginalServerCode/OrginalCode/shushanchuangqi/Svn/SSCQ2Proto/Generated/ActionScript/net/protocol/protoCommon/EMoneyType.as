/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMoneyType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 货币类型
	 */
	public final class EMoneyType
	{
		public static const EMONEY_NONE:uint = 0; //无类型表示不消耗
		public static const EMONEY_GOLD:uint = 1; //仙石
		public static const EMONEY_SILVER:uint = 2; //银币
		public static const EMONEY_COUPON:uint = 3; //礼券
		public static const EMONEY_GIFTCOIN:uint = 4; //金券
		public static const EMONEY_EXP:uint = 5; //经验
		public static const EMONEY_PRESTIGE:uint = 6; //声望
		public static const EMONEY_SOUL:uint = 7; //魂魄
		public static const EMONEY_HONOR:uint = 8; //荣誉
		public static const EMONEY_PEXP:uint = 9; //修为
		public static const EMONEY_SIGIL:uint = 10; //符印
		public static const EMONEY_CENTSY:uint = 11; //仙元
		public static const EMONEY_ACTION:uint = 12; //体力
		public static const EMONEY_SOP:uint = 13; //阅历
		public static const EMONEY_TAOISM:uint = 14; //道术
		public static const EMONEY_POTEN:uint = 15; //渡劫点数
		public static const EMONEY_REIKI:uint = 16; //副本星级
		public static const EMONEY_HFP:uint = 17; //寻仙积分
		public static const EMONEY_DEMONSOUL:uint = 18; //封印点
		public static const EMONEY_SOULATTACK:uint = 19; //攻击之魂
		public static const EMONEY_SOULHP:uint = 20; //生命之魂
		public static const EMONEY_SOULCRITICAL:uint = 21; //暴击之魂
		public static const EMONEY_SOULCOUNTER:uint = 22; //反击之魂
		public static const EMONEY_SOULSPEED:uint = 23; //身法之魂
		public static const EMONEY_SOULDEFENCE:uint = 24; //防御之魂
		public static const EMONEY_SOULHIT:uint = 25; //命中之魂
		public static const EMONEY_SOULDODGE:uint = 26; //闪避之魂
		public static const EMONEY_ACHIEVEMENTAP:uint = 27; //成就点
		public static const EMONEY_COLLECTAP:uint = 28; //收藏点
		public static const EMONEY_GUILDCONTRIB:uint = 29; //帮派贡献
		public static const EMONEY_STAMPHUANG:uint = 30; //橙阶除魔印
		public static const EMONEY_STAMPXUAN:uint = 31; //蓝阶除魔印
		public static const EMONEY_STAMPDI:uint = 32; //绿阶除魔印
		public static const EMONEY_STAMPTIAN:uint = 33; //紫阶除魔印
		public static const EMONEY_STAMPXING:uint = 34; //星阶除魔印
		public static const EMONEY_STAMPYUE:uint = 35; //月阶除魔印
		public static const EMONEY_STAMPDI2:uint = 36; //帝阶除魔印
		public static const EMONEY_STAMPXIAN:uint = 37; //仙阶除魔印
		public static const EMONEY_STAMPSHENG:uint = 38; //圣阶除魔印
		public static const EMONEY_STAMPFO:uint = 39; //佛阶除魔印
		public static const EMONEY_LOVEHEART:uint = 40; //爱心
		public static const EMONEY_BLUEFAIRYFATE:uint = 51; //蓝色仙缘
		public static const EMONEY_PURPLEFAIRYFATE:uint = 52; //紫色仙缘
		public static const EMONEY_ORANGEFAIRYFATE:uint = 53; //橙色仙缘
		public static const EMONEY_DUJIEFU:uint = 56; //渡劫符
		public static const EMONEY_LUCKYCOUPON:uint = 57; //抽奖券
		public static const EMONEY_END:uint = 100; //货币类型上限标志
		public static const end:uint = EMONEY_END;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMONEY_NONE:
					return ProtocolMessageProt258.EMONEY_NONE;
				case EMONEY_GOLD:
					return ProtocolMessageProt258.EMONEY_GOLD;
				case EMONEY_SILVER:
					return ProtocolMessageProt258.EMONEY_SILVER;
				case EMONEY_COUPON:
					return ProtocolMessageProt258.EMONEY_COUPON;
				case EMONEY_GIFTCOIN:
					return ProtocolMessageProt258.EMONEY_GIFTCOIN;
				case EMONEY_EXP:
					return ProtocolMessageProt258.EMONEY_EXP;
				case EMONEY_PRESTIGE:
					return ProtocolMessageProt258.EMONEY_PRESTIGE;
				case EMONEY_SOUL:
					return ProtocolMessageProt258.EMONEY_SOUL;
				case EMONEY_HONOR:
					return ProtocolMessageProt258.EMONEY_HONOR;
				case EMONEY_PEXP:
					return ProtocolMessageProt258.EMONEY_PEXP;
				case EMONEY_SIGIL:
					return ProtocolMessageProt258.EMONEY_SIGIL;
				case EMONEY_CENTSY:
					return ProtocolMessageProt258.EMONEY_CENTSY;
				case EMONEY_ACTION:
					return ProtocolMessageProt258.EMONEY_ACTION;
				case EMONEY_SOP:
					return ProtocolMessageProt258.EMONEY_SOP;
				case EMONEY_TAOISM:
					return ProtocolMessageProt258.EMONEY_TAOISM;
				case EMONEY_POTEN:
					return ProtocolMessageProt258.EMONEY_POTEN;
				case EMONEY_REIKI:
					return ProtocolMessageProt258.EMONEY_REIKI;
				case EMONEY_HFP:
					return ProtocolMessageProt258.EMONEY_HFP;
				case EMONEY_DEMONSOUL:
					return ProtocolMessageProt258.EMONEY_DEMONSOUL;
				case EMONEY_SOULATTACK:
					return ProtocolMessageProt258.EMONEY_SOULATTACK;
				case EMONEY_SOULHP:
					return ProtocolMessageProt258.EMONEY_SOULHP;
				case EMONEY_SOULCRITICAL:
					return ProtocolMessageProt258.EMONEY_SOULCRITICAL;
				case EMONEY_SOULCOUNTER:
					return ProtocolMessageProt258.EMONEY_SOULCOUNTER;
				case EMONEY_SOULSPEED:
					return ProtocolMessageProt258.EMONEY_SOULSPEED;
				case EMONEY_SOULDEFENCE:
					return ProtocolMessageProt258.EMONEY_SOULDEFENCE;
				case EMONEY_SOULHIT:
					return ProtocolMessageProt258.EMONEY_SOULHIT;
				case EMONEY_SOULDODGE:
					return ProtocolMessageProt258.EMONEY_SOULDODGE;
				case EMONEY_ACHIEVEMENTAP:
					return ProtocolMessageProt258.EMONEY_ACHIEVEMENTAP;
				case EMONEY_COLLECTAP:
					return ProtocolMessageProt258.EMONEY_COLLECTAP;
				case EMONEY_GUILDCONTRIB:
					return ProtocolMessageProt258.EMONEY_GUILDCONTRIB;
				case EMONEY_STAMPHUANG:
					return ProtocolMessageProt258.EMONEY_STAMPHUANG;
				case EMONEY_STAMPXUAN:
					return ProtocolMessageProt258.EMONEY_STAMPXUAN;
				case EMONEY_STAMPDI:
					return ProtocolMessageProt258.EMONEY_STAMPDI;
				case EMONEY_STAMPTIAN:
					return ProtocolMessageProt258.EMONEY_STAMPTIAN;
				case EMONEY_STAMPXING:
					return ProtocolMessageProt258.EMONEY_STAMPXING;
				case EMONEY_STAMPYUE:
					return ProtocolMessageProt258.EMONEY_STAMPYUE;
				case EMONEY_STAMPDI2:
					return ProtocolMessageProt258.EMONEY_STAMPDI2;
				case EMONEY_STAMPXIAN:
					return ProtocolMessageProt258.EMONEY_STAMPXIAN;
				case EMONEY_STAMPSHENG:
					return ProtocolMessageProt258.EMONEY_STAMPSHENG;
				case EMONEY_STAMPFO:
					return ProtocolMessageProt258.EMONEY_STAMPFO;
				case EMONEY_LOVEHEART:
					return ProtocolMessageProt258.EMONEY_LOVEHEART;
				case EMONEY_BLUEFAIRYFATE:
					return ProtocolMessageProt258.EMONEY_BLUEFAIRYFATE;
				case EMONEY_PURPLEFAIRYFATE:
					return ProtocolMessageProt258.EMONEY_PURPLEFAIRYFATE;
				case EMONEY_ORANGEFAIRYFATE:
					return ProtocolMessageProt258.EMONEY_ORANGEFAIRYFATE;
				case EMONEY_DUJIEFU:
					return ProtocolMessageProt258.EMONEY_DUJIEFU;
				case EMONEY_LUCKYCOUPON:
					return ProtocolMessageProt258.EMONEY_LUCKYCOUPON;
				case EMONEY_END:
					return ProtocolMessageProt258.EMONEY_END;
				default:
					return "Unknown Error";
			}
		}
	}
}
