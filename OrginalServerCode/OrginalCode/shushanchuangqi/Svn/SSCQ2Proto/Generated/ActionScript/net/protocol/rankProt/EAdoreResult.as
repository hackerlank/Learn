/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAdoreResult.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
 {
	import net.protocol.Message.ProtocolMessageProt80;
	/**
	 * 排行榜返回结果集
	 */
	public final class EAdoreResult
	{
		public static const eARSuccess:uint = 0; //操作成功
		public static const eARFailed:uint = 1; //操作失败
		public static const eARNotExist:uint = 2; //不存在
		public static const end:uint = eARNotExist;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eARSuccess:
					return ProtocolMessageProt80.eARSuccess;
				case eARFailed:
					return ProtocolMessageProt80.eARFailed;
				case eARNotExist:
					return ProtocolMessageProt80.eARNotExist;
				default:
					return "Unknown Error";
			}
		}
	}
}
