/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EOpResult.as
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
 {
	import net.protocol.Message.ProtocolMessageProt200;
	/**
	 * 操作结果
	 */
	public final class EOpResult
	{
		public static const eOtherError:uint = 0; //其他错误
		public static const eShortLevel:uint = 1; //等级不够
		public static const eNotActive:uint = 2; //未开通QQ黄钻
		public static const eNotYear:uint = 3; //未开通年费黄钻贵族
		public static const eNotLuxury:uint = 4; //未开通QQ豪华黄钻
		public static const eAreadyGain:uint = 5; //已经领取
		public static const eBagFull:uint = 6; //背包空间不足
		public static const eSuccess:uint = 7; //操作成功
		public static const end:uint = eSuccess;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eOtherError:
					return ProtocolMessageProt200.eOtherError;
				case eShortLevel:
					return ProtocolMessageProt200.eShortLevel;
				case eNotActive:
					return ProtocolMessageProt200.eNotActive;
				case eNotYear:
					return ProtocolMessageProt200.eNotYear;
				case eNotLuxury:
					return ProtocolMessageProt200.eNotLuxury;
				case eAreadyGain:
					return ProtocolMessageProt200.eAreadyGain;
				case eBagFull:
					return ProtocolMessageProt200.eBagFull;
				case eSuccess:
					return ProtocolMessageProt200.eSuccess;
				default:
					return "Unknown Error";
			}
		}
	}
}
