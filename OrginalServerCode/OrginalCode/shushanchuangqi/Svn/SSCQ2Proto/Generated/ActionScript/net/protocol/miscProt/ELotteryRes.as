/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELotteryRes.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
 {
	import net.protocol.Message.ProtocolMessageProt72;
	/**
	 * 抽奖操作结果
	 */
	public final class ELotteryRes
	{
		public static const eLotteryRes_Sucess:uint = 0; //成功
		public static const eLotteryRes_PackFul:uint = 1; //背包满
		public static const eLotteryRes_LackMoney:uint = 2; //缺钱
		public static const eLotteryRes_Error:uint = 3; //失败
		public static const end:uint = eLotteryRes_Error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLotteryRes_Sucess:
					return ProtocolMessageProt72.eLotteryRes_Sucess;
				case eLotteryRes_PackFul:
					return ProtocolMessageProt72.eLotteryRes_PackFul;
				case eLotteryRes_LackMoney:
					return ProtocolMessageProt72.eLotteryRes_LackMoney;
				case eLotteryRes_Error:
					return ProtocolMessageProt72.eLotteryRes_Error;
				default:
					return "Unknown Error";
			}
		}
	}
}
