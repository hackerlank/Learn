/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMapResult.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
 {
	import net.protocol.Message.ProtocolMessageProt5;
	/**
	 * 地图结果
	 */
	public final class EMapResult
	{
		public static const eMapSuccess:uint = 0; //成功
		public static const eMapNotGhostErr:uint = 1; //没处于灵魂状态
		public static const eMapCoinErr:uint = 2; //仙石不足
		public static const eMapNotInDungeonErr:uint = 3; //不在副本
		public static const eMapOtherErr:uint = 4; //其他错误
		public static const end:uint = eMapOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eMapSuccess:
					return ProtocolMessageProt5.eMapSuccess;
				case eMapNotGhostErr:
					return ProtocolMessageProt5.eMapNotGhostErr;
				case eMapCoinErr:
					return ProtocolMessageProt5.eMapCoinErr;
				case eMapNotInDungeonErr:
					return ProtocolMessageProt5.eMapNotInDungeonErr;
				case eMapOtherErr:
					return ProtocolMessageProt5.eMapOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
