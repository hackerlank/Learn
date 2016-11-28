/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EHorseOpType.as
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
 {
	import net.protocol.Message.ProtocolMessageProt74;
	/**
	 * 坐骑信息更新类型
	 */
	public final class EHorseOpType
	{
		public static const eHorseOpType_Add:uint = 0; //添加坐骑
		public static const eHorseOpType_Update:uint = 1; //更新坐骑信息
		public static const end:uint = eHorseOpType_Update;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eHorseOpType_Add:
					return ProtocolMessageProt74.eHorseOpType_Add;
				case eHorseOpType_Update:
					return ProtocolMessageProt74.eHorseOpType_Update;
				default:
					return "Unknown Error";
			}
		}
	}
}
