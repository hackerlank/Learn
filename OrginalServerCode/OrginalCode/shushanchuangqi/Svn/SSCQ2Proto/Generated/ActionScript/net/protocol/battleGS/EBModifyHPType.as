/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBModifyHPType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 修改血的类型
	 */
	public final class EBModifyHPType
	{
		public static const EBMODIFYHP_NORMAL:uint = 0; //普通
		public static const EBMODIFYHP_CRITICAL:uint = 1; //暴击
		public static const end:uint = EBMODIFYHP_CRITICAL;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBMODIFYHP_NORMAL:
					return ProtocolMessageProt21.EBMODIFYHP_NORMAL;
				case EBMODIFYHP_CRITICAL:
					return ProtocolMessageProt21.EBMODIFYHP_CRITICAL;
				default:
					return "Unknown Error";
			}
		}
	}
}
