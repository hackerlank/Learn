/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFeedBackRet.as
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
 {
	import net.protocol.Message.ProtocolMessageProt144;
	/**
	 * 消费回馈错误码
	 */
	public final class EFeedBackRet
	{
		public static const eFeedBackRet_Sucess:uint = 0; //成功
		public static const eFeedBackRet_MoneyLimit:uint = 1; //仙元不足
		public static const eFeedBackRet_TakeCntLimit:uint = 2; //领取次数限制
		public static const eFeedBackRet_IDError:uint = 3; //领奖id错误
		public static const eFeedBackRet_TimeError:uint = 4; //不在限购时间
		public static const eFeedBackRet_CFGError:uint = 5; //配置错误
		public static const eFeedBackRet_ParamError:uint = 6; //参数错误
		public static const eFeedBackRet_PackError:uint = 7; //背包空间不足
		public static const eFeedBackRet_ActiveTimeError:uint = 8; //不在活动时间内
		public static const eFeedBackRet_PrizeCntError:uint = 9; //领奖次数限制
		public static const end:uint = eFeedBackRet_PrizeCntError;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFeedBackRet_Sucess:
					return ProtocolMessageProt144.eFeedBackRet_Sucess;
				case eFeedBackRet_MoneyLimit:
					return ProtocolMessageProt144.eFeedBackRet_MoneyLimit;
				case eFeedBackRet_TakeCntLimit:
					return ProtocolMessageProt144.eFeedBackRet_TakeCntLimit;
				case eFeedBackRet_IDError:
					return ProtocolMessageProt144.eFeedBackRet_IDError;
				case eFeedBackRet_TimeError:
					return ProtocolMessageProt144.eFeedBackRet_TimeError;
				case eFeedBackRet_CFGError:
					return ProtocolMessageProt144.eFeedBackRet_CFGError;
				case eFeedBackRet_ParamError:
					return ProtocolMessageProt144.eFeedBackRet_ParamError;
				case eFeedBackRet_PackError:
					return ProtocolMessageProt144.eFeedBackRet_PackError;
				case eFeedBackRet_ActiveTimeError:
					return ProtocolMessageProt144.eFeedBackRet_ActiveTimeError;
				case eFeedBackRet_PrizeCntError:
					return ProtocolMessageProt144.eFeedBackRet_PrizeCntError;
				default:
					return "Unknown Error";
			}
		}
	}
}
