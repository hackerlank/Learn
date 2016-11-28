/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    AWARDTYPE.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 奖励类型
	 */
	public final class AWARDTYPE
	{
		public static const AWARDTYPE_TITLE:uint = 1; //称号
		public static const end:uint = AWARDTYPE_TITLE;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case AWARDTYPE_TITLE:
					return ProtocolMessageProt258.AWARDTYPE_TITLE;
				default:
					return "Unknown Error";
			}
		}
	}
}
