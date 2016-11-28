/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGuildPubDataType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 公共帮派数据类型
	 */
	public final class EGuildPubDataType
	{
		public static const eGPDTListInfo:uint = 0; //帮派列表信息
		public static const eGPDTBattleInfo:uint = 1; //帮派战相关数据
		public static const eGPDTMax:uint = 2; //帮派信息最大值
		public static const end:uint = eGPDTMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGPDTListInfo:
					return ProtocolMessageProt16.eGPDTListInfo;
				case eGPDTBattleInfo:
					return ProtocolMessageProt16.eGPDTBattleInfo;
				case eGPDTMax:
					return ProtocolMessageProt16.eGPDTMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
