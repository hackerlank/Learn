/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMapOverLoad.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
 {
	import net.protocol.Message.ProtocolMessageProt5;
	/**
	 * 地图负载
	 */
	public final class EMapOverLoad
	{
		public static const eMapFree:uint = 0; //空闲
		public static const eMapBusy:uint = 1; //地图忙
		public static const eMapFull:uint = 2; //地图满
		public static const end:uint = eMapFull;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eMapFree:
					return ProtocolMessageProt5.eMapFree;
				case eMapBusy:
					return ProtocolMessageProt5.eMapBusy;
				case eMapFull:
					return ProtocolMessageProt5.eMapFull;
				default:
					return "Unknown Error";
			}
		}
	}
}
