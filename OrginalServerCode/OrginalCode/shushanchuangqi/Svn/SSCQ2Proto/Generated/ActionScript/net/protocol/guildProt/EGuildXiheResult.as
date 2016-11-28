/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGuildXiheResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 羲和神车操作返回结果
	 */
	public final class EGuildXiheResult
	{
		public static const eXiheResultSuccess:uint = 0; //操作成功
		public static const eXiheResultFailed:uint = 1; //操作失败
		public static const eXiheResultNoGuild:uint = 2; //不存在帮派
		public static const eXiheResultUnfinish:uint = 3; //货物未装满
		public static const eXiheResultFinish:uint = 4; //货物已装箱
		public static const eXiheResultHasRequest:uint = 5; //货物已请求帮助
		public static const eXiheResultNotRequest:uint = 6; //货物未请求帮助
		public static const eXiheResultNotTruck:uint = 7; //不存在这个货物
		public static const eXiheResultNotItem:uint = 8; //道具不足不能装货
		public static const eXiheResultNotGold:uint = 9; //仙石不足不能装货
		public static const eXiheResultNoSameGuild:uint = 10; //不是同一帮派
		public static const eXiheResultForHelpNumMax:uint = 11; //此次任务请求帮助次数已达上限
		public static const eXiheResultNotRequestLimit:uint = 12; //已装货物未达到4个不能请求帮助
		public static const end:uint = eXiheResultNotRequestLimit;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eXiheResultSuccess:
					return ProtocolMessageProt16.eXiheResultSuccess;
				case eXiheResultFailed:
					return ProtocolMessageProt16.eXiheResultFailed;
				case eXiheResultNoGuild:
					return ProtocolMessageProt16.eXiheResultNoGuild;
				case eXiheResultUnfinish:
					return ProtocolMessageProt16.eXiheResultUnfinish;
				case eXiheResultFinish:
					return ProtocolMessageProt16.eXiheResultFinish;
				case eXiheResultHasRequest:
					return ProtocolMessageProt16.eXiheResultHasRequest;
				case eXiheResultNotRequest:
					return ProtocolMessageProt16.eXiheResultNotRequest;
				case eXiheResultNotTruck:
					return ProtocolMessageProt16.eXiheResultNotTruck;
				case eXiheResultNotItem:
					return ProtocolMessageProt16.eXiheResultNotItem;
				case eXiheResultNotGold:
					return ProtocolMessageProt16.eXiheResultNotGold;
				case eXiheResultNoSameGuild:
					return ProtocolMessageProt16.eXiheResultNoSameGuild;
				case eXiheResultForHelpNumMax:
					return ProtocolMessageProt16.eXiheResultForHelpNumMax;
				case eXiheResultNotRequestLimit:
					return ProtocolMessageProt16.eXiheResultNotRequestLimit;
				default:
					return "Unknown Error";
			}
		}
	}
}
