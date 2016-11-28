/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EQQPtType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * QQ平台类型
	 */
	public final class EQQPtType
	{
		public static const eQQPtTypeNone:uint = 0; //无
		public static const eQQPtTypeYellow:uint = 1; //黄钻平台
		public static const eQQPtTypeBlue:uint = 2; //蓝钻平台
		public static const eQQPtTypeRed:uint = 3; //红钻/VIP平台
		public static const eQQPtTypeMax:uint = 4; //最大值
		public static const end:uint = eQQPtTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eQQPtTypeNone:
					return ProtocolMessageProt258.eQQPtTypeNone;
				case eQQPtTypeYellow:
					return ProtocolMessageProt258.eQQPtTypeYellow;
				case eQQPtTypeBlue:
					return ProtocolMessageProt258.eQQPtTypeBlue;
				case eQQPtTypeRed:
					return ProtocolMessageProt258.eQQPtTypeRed;
				case eQQPtTypeMax:
					return ProtocolMessageProt258.eQQPtTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
