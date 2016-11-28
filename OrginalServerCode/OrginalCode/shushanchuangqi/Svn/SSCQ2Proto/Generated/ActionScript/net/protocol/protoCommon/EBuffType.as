/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuffType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * Buff大类
	 */
	public final class EBuffType
	{
		public static const eBTNone:uint = 0; //无效Buff大类
		public static const eBTUser:uint = 1; //帐号相关Buff类型
		public static const eBTPlayer:uint = 2; //玩家自带Buff类型
		public static const eBTMainFighter:uint = 3; //主将相关Buff类型
		public static const eBTFighter:uint = 4; //散仙相关Buff类型
		public static const eBTMonster:uint = 5; //怪物相关Buff类型
		public static const eBTNPC:uint = 6; //NPC相关Buff类型
		public static const eBTMax:uint = 7; //Buff大类最大值
		public static const end:uint = eBTMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBTNone:
					return ProtocolMessageProt258.eBTNone;
				case eBTUser:
					return ProtocolMessageProt258.eBTUser;
				case eBTPlayer:
					return ProtocolMessageProt258.eBTPlayer;
				case eBTMainFighter:
					return ProtocolMessageProt258.eBTMainFighter;
				case eBTFighter:
					return ProtocolMessageProt258.eBTFighter;
				case eBTMonster:
					return ProtocolMessageProt258.eBTMonster;
				case eBTNPC:
					return ProtocolMessageProt258.eBTNPC;
				case eBTMax:
					return ProtocolMessageProt258.eBTMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
