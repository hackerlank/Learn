/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBEnterResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战进入结果
	 */
	public final class EGBEnterResult
	{
		public static const eGBEnterSuccess:uint = 0; //进入成功
		public static const eGBEnterFailed:uint = 1; //进入失败
		public static const eGBEnterNotInGuild:uint = 2; //进入时不存在帮派
		public static const eGBEnterRepeat:uint = 3; //进入重复
		public static const eGBEnterWrongTime:uint = 4; //不在进入时段
		public static const end:uint = eGBEnterWrongTime;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBEnterSuccess:
					return ProtocolMessageProt76.eGBEnterSuccess;
				case eGBEnterFailed:
					return ProtocolMessageProt76.eGBEnterFailed;
				case eGBEnterNotInGuild:
					return ProtocolMessageProt76.eGBEnterNotInGuild;
				case eGBEnterRepeat:
					return ProtocolMessageProt76.eGBEnterRepeat;
				case eGBEnterWrongTime:
					return ProtocolMessageProt76.eGBEnterWrongTime;
				default:
					return "Unknown Error";
			}
		}
	}
}
