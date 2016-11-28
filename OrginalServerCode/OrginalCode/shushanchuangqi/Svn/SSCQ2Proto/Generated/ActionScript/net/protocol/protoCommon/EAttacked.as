/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAttacked.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 被攻击类型
	 */
	public final class EAttacked
	{
		public static const eAttacked_None:uint = 0; //无
		public static const eAttacked_Demontower:uint = 1; //锁妖塔
		public static const eAttacked_Max:uint = 2; //类型上限
		public static const end:uint = eAttacked_Max;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAttacked_None:
					return ProtocolMessageProt258.eAttacked_None;
				case eAttacked_Demontower:
					return ProtocolMessageProt258.eAttacked_Demontower;
				case eAttacked_Max:
					return ProtocolMessageProt258.eAttacked_Max;
				default:
					return "Unknown Error";
			}
		}
	}
}
