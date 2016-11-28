/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ERankResult.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
 {
	import net.protocol.Message.ProtocolMessageProt80;
	/**
	 * 排行榜返回结果集
	 */
	public final class ERankResult
	{
		public static const eRRSuccess:uint = 0; //操作成功
		public static const eRRFailed:uint = 1; //操作失败
		public static const eRRNotExist:uint = 2; //不存在
		public static const end:uint = eRRNotExist;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eRRSuccess:
					return ProtocolMessageProt80.eRRSuccess;
				case eRRFailed:
					return ProtocolMessageProt80.eRRFailed;
				case eRRNotExist:
					return ProtocolMessageProt80.eRRNotExist;
				default:
					return "Unknown Error";
			}
		}
	}
}
