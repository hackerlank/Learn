/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMemberRank.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派职位
	 */
	public final class EMemberRank
	{
		public static const eMemberNone:uint = 0; //无效职位
		public static const eMemberNormal:uint = 1; //成员
		public static const eMemberElite:uint = 2; //精英
		public static const eMemberElder:uint = 3; //长老
		public static const eMemberViceOwner:uint = 4; //副帮主
		public static const eMemberOwner:uint = 5; //帮主
		public static const eMemberMax:uint = 6; //最高职位
		public static const end:uint = eMemberMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eMemberNone:
					return ProtocolMessageProt16.eMemberNone;
				case eMemberNormal:
					return ProtocolMessageProt16.eMemberNormal;
				case eMemberElite:
					return ProtocolMessageProt16.eMemberElite;
				case eMemberElder:
					return ProtocolMessageProt16.eMemberElder;
				case eMemberViceOwner:
					return ProtocolMessageProt16.eMemberViceOwner;
				case eMemberOwner:
					return ProtocolMessageProt16.eMemberOwner;
				case eMemberMax:
					return ProtocolMessageProt16.eMemberMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
