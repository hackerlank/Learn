/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMemberStatus.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
 {
	import net.protocol.Message.ProtocolMessageProt56;
	/**
	 * 队伍状态
	 */
	public final class EMemberStatus
	{
		public static const EMEMBER_NONE:uint = 0; //无状态
		public static const EMEMBER_READY:uint = 1; //已准备好
		public static const EMEMBER_ERR:uint = 2; //不满足条件提示
		public static const end:uint = EMEMBER_ERR;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMEMBER_NONE:
					return ProtocolMessageProt56.EMEMBER_NONE;
				case EMEMBER_READY:
					return ProtocolMessageProt56.EMEMBER_READY;
				case EMEMBER_ERR:
					return ProtocolMessageProt56.EMEMBER_ERR;
				default:
					return "Unknown Error";
			}
		}
	}
}
