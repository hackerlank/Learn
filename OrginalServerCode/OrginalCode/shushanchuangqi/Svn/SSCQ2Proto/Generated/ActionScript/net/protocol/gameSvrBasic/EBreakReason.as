/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBreakReason.as
//  Purpose:      GameServer的基本协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
 {
	import net.protocol.Message.ProtocolMessageProt13;
	/**
	 * 断开原因
	 */
	public final class EBreakReason
	{
		public static const eBreakNone:uint = 0; //无
		public static const eBreakUsrKick:uint = 1; //被另一处登录的帐号踢下线
		public static const eBreakSvrKick:uint = 2; //被服务器踢下线
		public static const eBreakExcept:uint = 3; //发生异常
		public static const eBreakOther:uint = 4; //其它原因
		public static const eBreakIndulgeKick:uint = 5; //防沉迷系统已启动，请休息5小时
		public static const eBreakIndulgeTimeKick:uint = 6; //防沉迷系统已启动，请休息完5小时后登陆
		public static const end:uint = eBreakIndulgeTimeKick;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBreakNone:
					return ProtocolMessageProt13.eBreakNone;
				case eBreakUsrKick:
					return ProtocolMessageProt13.eBreakUsrKick;
				case eBreakSvrKick:
					return ProtocolMessageProt13.eBreakSvrKick;
				case eBreakExcept:
					return ProtocolMessageProt13.eBreakExcept;
				case eBreakOther:
					return ProtocolMessageProt13.eBreakOther;
				case eBreakIndulgeKick:
					return ProtocolMessageProt13.eBreakIndulgeKick;
				case eBreakIndulgeTimeKick:
					return ProtocolMessageProt13.eBreakIndulgeTimeKick;
				default:
					return "Unknown Error";
			}
		}
	}
}
