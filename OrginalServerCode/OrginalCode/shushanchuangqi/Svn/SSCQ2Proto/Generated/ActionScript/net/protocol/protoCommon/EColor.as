/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EColor.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 颜色
	 */
	public final class EColor
	{
		public static const ECOLOR_BLACK:uint = 0; //黑
		public static const ECOLOR_WHITE:uint = 1;
		public static const ECOLOR_GREEN:uint = 2; //绿
		public static const ECOLOR_BLUE:uint = 3; //兰
		public static const ECOLOR_PURPLE:uint = 4; //紫
		public static const ECOLOR_ORANGE:uint = 5; //橙
		public static const end:uint = ECOLOR_ORANGE;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ECOLOR_BLACK:
					return ProtocolMessageProt258.ECOLOR_BLACK;
				case ECOLOR_WHITE:
					return ProtocolMessageProt258.ECOLOR_WHITE;
				case ECOLOR_GREEN:
					return ProtocolMessageProt258.ECOLOR_GREEN;
				case ECOLOR_BLUE:
					return ProtocolMessageProt258.ECOLOR_BLUE;
				case ECOLOR_PURPLE:
					return ProtocolMessageProt258.ECOLOR_PURPLE;
				case ECOLOR_ORANGE:
					return ProtocolMessageProt258.ECOLOR_ORANGE;
				default:
					return "Unknown Error";
			}
		}
	}
}
