/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMemberOperateType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派成员操作类型
	 */
	public final class EMemberOperateType
	{
		public static const eGMOpTypeNone:uint = 0; //无效操作
		public static const eGMOpTypeUp:uint = 1; //提升职位
		public static const eGMOpTypeKick:uint = 2; //踢出帮派
		public static const eGMOpTypeGiveOwner:uint = 3; //移交帮主
		public static const eGMOpTypeDown:uint = 4; //降低职位
		public static const eGMOpTypeFire:uint = 5; //免除职位
		public static const eGMOpTypeMax:uint = 6; //最大操作
		public static const end:uint = eGMOpTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGMOpTypeNone:
					return ProtocolMessageProt16.eGMOpTypeNone;
				case eGMOpTypeUp:
					return ProtocolMessageProt16.eGMOpTypeUp;
				case eGMOpTypeKick:
					return ProtocolMessageProt16.eGMOpTypeKick;
				case eGMOpTypeGiveOwner:
					return ProtocolMessageProt16.eGMOpTypeGiveOwner;
				case eGMOpTypeDown:
					return ProtocolMessageProt16.eGMOpTypeDown;
				case eGMOpTypeFire:
					return ProtocolMessageProt16.eGMOpTypeFire;
				case eGMOpTypeMax:
					return ProtocolMessageProt16.eGMOpTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
