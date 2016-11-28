/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuildingType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派建筑类型
	 */
	public final class EBuildingType
	{
		public static const eBuildingNone:uint = 0; //无效建筑
		public static const eBuildingOracle:uint = 1; //神谕塔
		public static const eBuildingDepot:uint = 2; //仓库
		public static const eBuildingSword:uint = 3; //剑阁
		public static const eBuildingStore:uint = 4; //商店
		public static const eBuildingBlood:uint = 5; //血池
		public static const eBuildingMax:uint = 6; //最高建筑
		public static const end:uint = eBuildingMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBuildingNone:
					return ProtocolMessageProt16.eBuildingNone;
				case eBuildingOracle:
					return ProtocolMessageProt16.eBuildingOracle;
				case eBuildingDepot:
					return ProtocolMessageProt16.eBuildingDepot;
				case eBuildingSword:
					return ProtocolMessageProt16.eBuildingSword;
				case eBuildingStore:
					return ProtocolMessageProt16.eBuildingStore;
				case eBuildingBlood:
					return ProtocolMessageProt16.eBuildingBlood;
				case eBuildingMax:
					return ProtocolMessageProt16.eBuildingMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
