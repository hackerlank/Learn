/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPkgType.as
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanweiweiProt
 {
	import net.protocol.Message.ProtocolMessageProt93;
	/**
	 * 领奖类型
	 */
	public final class EPkgType
	{
		public static const eWeibo:uint = 0; //微博
		public static const eWeixin:uint = 1; //微信
		public static const eMax:uint = 2; //最大值
		public static const end:uint = eMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWeibo:
					return ProtocolMessageProt93.eWeibo;
				case eWeixin:
					return ProtocolMessageProt93.eWeixin;
				case eMax:
					return ProtocolMessageProt93.eMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
