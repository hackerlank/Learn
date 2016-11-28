/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELotteryBeautyType.as
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
 {
	import net.protocol.Message.ProtocolMessageProt131;
	/**
	 * 抽奖类型
	 */
	public final class ELotteryBeautyType
	{
		public static const eLotteryBeautyType_OneSilver:uint = 1001; //单次银币抽奖
		public static const eLotteryBeautyType_OneGold:uint = 1002; //单次仙石抽奖
		public static const eLotteryBeautyType_OneLoveHeart:uint = 1003; //单次爱心抽奖
		public static const eLotteryBeautyType_OneFreeGold:uint = 1004; //单次仙石免费抽奖
		public static const eLotteryBeautyType_TenSilver:uint = 2001; //10次银币抽奖
		public static const eLotteryBeautyType_TenGold:uint = 2002; //10次仙石抽奖
		public static const eLotteryBeautyType_TenLoveHeart:uint = 2003; //10次爱心抽奖
		public static const end:uint = eLotteryBeautyType_TenLoveHeart;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLotteryBeautyType_OneSilver:
					return ProtocolMessageProt131.eLotteryBeautyType_OneSilver;
				case eLotteryBeautyType_OneGold:
					return ProtocolMessageProt131.eLotteryBeautyType_OneGold;
				case eLotteryBeautyType_OneLoveHeart:
					return ProtocolMessageProt131.eLotteryBeautyType_OneLoveHeart;
				case eLotteryBeautyType_OneFreeGold:
					return ProtocolMessageProt131.eLotteryBeautyType_OneFreeGold;
				case eLotteryBeautyType_TenSilver:
					return ProtocolMessageProt131.eLotteryBeautyType_TenSilver;
				case eLotteryBeautyType_TenGold:
					return ProtocolMessageProt131.eLotteryBeautyType_TenGold;
				case eLotteryBeautyType_TenLoveHeart:
					return ProtocolMessageProt131.eLotteryBeautyType_TenLoveHeart;
				default:
					return "Unknown Error";
			}
		}
	}
}
