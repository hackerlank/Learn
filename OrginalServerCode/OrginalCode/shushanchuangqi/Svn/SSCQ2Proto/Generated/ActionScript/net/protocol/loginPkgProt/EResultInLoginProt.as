/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EResultInLoginProt.as
//  Purpose:      累计登入礼包协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginPkgProt
 {
	import net.protocol.Message.ProtocolMessageProt92;
	/**
	 * 操作结果
	 */
	public final class EResultInLoginProt
	{
		public static const ePkgError:uint = 0; //错误
		public static const ePkgGain:uint = 1; //已经领取
		public static const ePkgFull:uint = 2; //背包已满
		public static const ePkgSuccess:uint = 3; //成功
		public static const end:uint = ePkgSuccess;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePkgError:
					return ProtocolMessageProt92.ePkgError;
				case ePkgGain:
					return ProtocolMessageProt92.ePkgGain;
				case ePkgFull:
					return ProtocolMessageProt92.ePkgFull;
				case ePkgSuccess:
					return ProtocolMessageProt92.ePkgSuccess;
				default:
					return "Unknown Error";
			}
		}
	}
}
