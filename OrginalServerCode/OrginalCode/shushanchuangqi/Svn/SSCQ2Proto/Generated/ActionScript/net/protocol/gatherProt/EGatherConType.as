/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGatherConType.as
//  Purpose:      采集协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
 {
	import net.protocol.Message.ProtocolMessageProt60;
	/**
	 * 采集条件
	 */
	public final class EGatherConType
	{
		public static const eGCT_None:uint = 0; //无定义
		public static const eGCT_Level:uint = 1; //等级
		public static const eGCT_Item:uint = 2; //道具，包括仙石等
		public static const eGCT_VIP:uint = 3; //VIP宝箱
		public static const eGCT_End:uint = 4; //定义完毕
		public static const end:uint = eGCT_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGCT_None:
					return ProtocolMessageProt60.eGCT_None;
				case eGCT_Level:
					return ProtocolMessageProt60.eGCT_Level;
				case eGCT_Item:
					return ProtocolMessageProt60.eGCT_Item;
				case eGCT_VIP:
					return ProtocolMessageProt60.eGCT_VIP;
				case eGCT_End:
					return ProtocolMessageProt60.eGCT_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
