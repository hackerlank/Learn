/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEnterResult.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
 {
	import net.protocol.Message.ProtocolMessageProt3;
	/**
	 * 登录结果
	 */
	public final class EEnterResult
	{
		public static const eEnterSucceed:uint = 0; //成功
		public static const eRoleNoExist:uint = 1; //角色未创建
		public static const eEnterAlready:uint = 2; //已经在游戏中
		public static const eEnterDataErr:uint = 3; //角色数据错误
		public static const eEnterStateErr:uint = 4; //状态错误
		public static const eEnterFreezErr:uint = 5; //帐号被封
		public static const eEnterOtherErr:uint = 6; //其它错误
		public static const end:uint = eEnterOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eEnterSucceed:
					return ProtocolMessageProt3.eEnterSucceed;
				case eRoleNoExist:
					return ProtocolMessageProt3.eRoleNoExist;
				case eEnterAlready:
					return ProtocolMessageProt3.eEnterAlready;
				case eEnterDataErr:
					return ProtocolMessageProt3.eEnterDataErr;
				case eEnterStateErr:
					return ProtocolMessageProt3.eEnterStateErr;
				case eEnterFreezErr:
					return ProtocolMessageProt3.eEnterFreezErr;
				case eEnterOtherErr:
					return ProtocolMessageProt3.eEnterOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
