/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETripodType.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
 {
	import net.protocol.Message.ProtocolMessageProt63;
	/**
	 * 九疑鼎操作结果
	 */
	public final class ETripodType
	{
		public static const eTripodSucc:uint = 0; //成功
		public static const eTripodFailed:uint = 1; //失败
		public static const eTripodCondIDErr:uint = 2; //激活条件不足
		public static const eTripodItemErr:uint = 3; //道具不足
		public static const eTripodNotFire:uint = 4; //未祈火
		public static const eTripodNoEnoughCnt:uint = 5; //剩余祈火次数不足
		public static const eTripodYuanqiNotFull:uint = 6; //元气值未满
		public static const eTripodYuanqiFull:uint = 7; //元气值已满
		public static const eTripodNotTime:uint = 8; //时间未到
		public static const eTripodShanfengFull:uint = 9; //扇风次数已满
		public static const eTripodHelpTimesFull:uint = 10; //协助次数已满
		public static const eTripodNotHelp:uint = 11; //不能协助
		public static const end:uint = eTripodNotHelp;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTripodSucc:
					return ProtocolMessageProt63.eTripodSucc;
				case eTripodFailed:
					return ProtocolMessageProt63.eTripodFailed;
				case eTripodCondIDErr:
					return ProtocolMessageProt63.eTripodCondIDErr;
				case eTripodItemErr:
					return ProtocolMessageProt63.eTripodItemErr;
				case eTripodNotFire:
					return ProtocolMessageProt63.eTripodNotFire;
				case eTripodNoEnoughCnt:
					return ProtocolMessageProt63.eTripodNoEnoughCnt;
				case eTripodYuanqiNotFull:
					return ProtocolMessageProt63.eTripodYuanqiNotFull;
				case eTripodYuanqiFull:
					return ProtocolMessageProt63.eTripodYuanqiFull;
				case eTripodNotTime:
					return ProtocolMessageProt63.eTripodNotTime;
				case eTripodShanfengFull:
					return ProtocolMessageProt63.eTripodShanfengFull;
				case eTripodHelpTimesFull:
					return ProtocolMessageProt63.eTripodHelpTimesFull;
				case eTripodNotHelp:
					return ProtocolMessageProt63.eTripodNotHelp;
				default:
					return "Unknown Error";
			}
		}
	}
}
