/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECreateResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 创建帮派返回结果
	 */
	public final class ECreateResult
	{
		public static const eGCreateSuccess:uint = 0; //操作成功
		public static const eGCreateFailed:uint = 1; //操作失败
		public static const eGCreateInGuild:uint = 2; //已经在帮派中
		public static const eGCreateLackOfGold:uint = 3; //银币不足
		public static const eGCreateLackOfLevel:uint = 4; //等级不足
		public static const eGCreateNameTooShort:uint = 5; //名称太短
		public static const eGCreateNameTooLong:uint = 6; //名称太长
		public static const eGCreateNameInvalid:uint = 7; //名称非法
		public static const eGCreateNameExisted:uint = 8; //名称存在
		public static const eGCreateExisted:uint = 9; //帮派存在
		public static const eGCreateLackOfVIP:uint = 10; //御剑等级不足
		public static const end:uint = eGCreateLackOfVIP;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGCreateSuccess:
					return ProtocolMessageProt16.eGCreateSuccess;
				case eGCreateFailed:
					return ProtocolMessageProt16.eGCreateFailed;
				case eGCreateInGuild:
					return ProtocolMessageProt16.eGCreateInGuild;
				case eGCreateLackOfGold:
					return ProtocolMessageProt16.eGCreateLackOfGold;
				case eGCreateLackOfLevel:
					return ProtocolMessageProt16.eGCreateLackOfLevel;
				case eGCreateNameTooShort:
					return ProtocolMessageProt16.eGCreateNameTooShort;
				case eGCreateNameTooLong:
					return ProtocolMessageProt16.eGCreateNameTooLong;
				case eGCreateNameInvalid:
					return ProtocolMessageProt16.eGCreateNameInvalid;
				case eGCreateNameExisted:
					return ProtocolMessageProt16.eGCreateNameExisted;
				case eGCreateExisted:
					return ProtocolMessageProt16.eGCreateExisted;
				case eGCreateLackOfVIP:
					return ProtocolMessageProt16.eGCreateLackOfVIP;
				default:
					return "Unknown Error";
			}
		}
	}
}
