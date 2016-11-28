/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDgnType.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
 {
	import net.protocol.Message.ProtocolMessageProt59;
	/**
	 * 副本类型
	 */
	public final class EDgnType
	{
		public static const eNoneDgn:uint = 0; //无定义
		public static const ePlayerDgn:uint = 1; //单人副本
		public static const eGatherDgn:uint = 2; //采集副本
		public static const eTeamDgn:uint = 3; //组队副本
		public static const eDemonTowerDgn:uint = 4; //镇妖塔副本
		public static const end:uint = eDemonTowerDgn;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNoneDgn:
					return ProtocolMessageProt59.eNoneDgn;
				case ePlayerDgn:
					return ProtocolMessageProt59.ePlayerDgn;
				case eGatherDgn:
					return ProtocolMessageProt59.eGatherDgn;
				case eTeamDgn:
					return ProtocolMessageProt59.eTeamDgn;
				case eDemonTowerDgn:
					return ProtocolMessageProt59.eDemonTowerDgn;
				default:
					return "Unknown Error";
			}
		}
	}
}
