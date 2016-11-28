/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPtType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 平台类型定义
	 */
	public final class EPtType
	{
		public static const ePtTypeNone:uint = 0; //无
		public static const ePtTypeQQYellow:uint = 1; //QQ黄钻平台/Qzone
		public static const ePtTypeQQPengyou:uint = 2; //QQ朋友/校友/黄钻
		public static const ePtTypeQQWeibo:uint = 3; //QQ微博平台
		public static const ePtTypeQQPlus:uint = 4; //QQ/Q+平台
		public static const ePtTypeQQGame:uint = 5; //QQ蓝钻/游戏平台
		public static const ePtTypeQQ3366:uint = 6; //QQ蓝钻/3366平台/包子
		public static const ePtTypeQQKingxin:uint = 7; //QQ官网平台/QQ会员
		public static const ePtTypeKingxin:uint = 8; //恺英官网平台
		public static const ePtTypeMax:uint = 9; //最大值
		public static const end:uint = ePtTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePtTypeNone:
					return ProtocolMessageProt258.ePtTypeNone;
				case ePtTypeQQYellow:
					return ProtocolMessageProt258.ePtTypeQQYellow;
				case ePtTypeQQPengyou:
					return ProtocolMessageProt258.ePtTypeQQPengyou;
				case ePtTypeQQWeibo:
					return ProtocolMessageProt258.ePtTypeQQWeibo;
				case ePtTypeQQPlus:
					return ProtocolMessageProt258.ePtTypeQQPlus;
				case ePtTypeQQGame:
					return ProtocolMessageProt258.ePtTypeQQGame;
				case ePtTypeQQ3366:
					return ProtocolMessageProt258.ePtTypeQQ3366;
				case ePtTypeQQKingxin:
					return ProtocolMessageProt258.ePtTypeQQKingxin;
				case ePtTypeKingxin:
					return ProtocolMessageProt258.ePtTypeKingxin;
				case ePtTypeMax:
					return ProtocolMessageProt258.ePtTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
