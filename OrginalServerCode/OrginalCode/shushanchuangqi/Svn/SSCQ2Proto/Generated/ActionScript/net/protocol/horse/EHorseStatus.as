/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EHorseStatus.as
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
 {
	import net.protocol.Message.ProtocolMessageProt74;
	/**
	 * 骑乘状态
	 */
	public final class EHorseStatus
	{
		public static const eHorseStatusUnMount:uint = 0; //下马
		public static const eHorseStatusMounted:uint = 1; //上马
		public static const end:uint = eHorseStatusMounted;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eHorseStatusUnMount:
					return ProtocolMessageProt74.eHorseStatusUnMount;
				case eHorseStatusMounted:
					return ProtocolMessageProt74.eHorseStatusMounted;
				default:
					return "Unknown Error";
			}
		}
	}
}
