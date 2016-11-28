/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMonsterPrizeType.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
 {
	import net.protocol.Message.ProtocolMessageProt96;
	/**
	 * 奖励类型
	 */
	public final class EMonsterPrizeType
	{
		public static const EMonsterPrize_Begin:uint = 0; //礼包Begin
		public static const EMonsterPrize_1:uint = 1; //每日成长礼包
		public static const EMonsterPrize_2:uint = 2; //每日初级礼包
		public static const EMonsterPrize_3:uint = 3; //每日中级礼包
		public static const EMonsterPrize_4:uint = 4; //每日高级礼包
		public static const EMonsterPrize_5:uint = 5; //每日终极礼包
		public static const EMonsterPrize_End:uint = 6; //End
		public static const end:uint = EMonsterPrize_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMonsterPrize_Begin:
					return ProtocolMessageProt96.EMonsterPrize_Begin;
				case EMonsterPrize_1:
					return ProtocolMessageProt96.EMonsterPrize_1;
				case EMonsterPrize_2:
					return ProtocolMessageProt96.EMonsterPrize_2;
				case EMonsterPrize_3:
					return ProtocolMessageProt96.EMonsterPrize_3;
				case EMonsterPrize_4:
					return ProtocolMessageProt96.EMonsterPrize_4;
				case EMonsterPrize_5:
					return ProtocolMessageProt96.EMonsterPrize_5;
				case EMonsterPrize_End:
					return ProtocolMessageProt96.EMonsterPrize_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
