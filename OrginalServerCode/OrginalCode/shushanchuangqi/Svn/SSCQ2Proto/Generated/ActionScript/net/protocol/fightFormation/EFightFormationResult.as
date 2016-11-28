/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFightFormationResult.as
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
 {
	import net.protocol.Message.ProtocolMessageProt132;
	/**
	 * 新阵型相关协议
	 */
	public final class EFightFormationResult
	{
		public static const eFightFormationResult_Succes:uint = 0; //操作成功
		public static const eFightFormationResult_Fail:uint = 1; //设置错误
		public static const end:uint = eFightFormationResult_Fail;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFightFormationResult_Succes:
					return ProtocolMessageProt132.eFightFormationResult_Succes;
				case eFightFormationResult_Fail:
					return ProtocolMessageProt132.eFightFormationResult_Fail;
				default:
					return "Unknown Error";
			}
		}
	}
}
