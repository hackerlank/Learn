/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EShengLingResult.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
 {
	import net.protocol.Message.ProtocolMessageProt98;
	/**
	 * 操作结果
	 */
	public final class EShengLingResult
	{
		public static const EShengLingResultSuc:uint = 0; //操作成功
		public static const EShengLingResultPackFul:uint = 1; //背包空间不足
		public static const EShengLingResultPrizeTaked:uint = 2; //奖励被领取
		public static const EShengLingResultFailed:uint = 3; //战斗失败
		public static const EShengLingResultGoldLack:uint = 4; //仙石不足
		public static const EShengLingResultEnterLack:uint = 5; //次数不足
		public static const EShengLingResultLifeLack:uint = 6; //生命不足
		public static const EShengLingResultControlDiceLack:uint = 7; //遥控骰子不足
		public static const EShengLingResultTurnDiceLack:uint = 8; //转向骰子不足
		public static const EShengLingResultScoreLack:uint = 9; //积分不够
		public static const EShengLingResultStepLack:uint = 10; //积分不够
		public static const EShengLingResultNotFinish:uint = 11; //格子未完成
		public static const EShengLingResultTypeError:uint = 12; //格子类型不对
		public static const EShengLingResultError:uint = 13; //操作失败
		public static const end:uint = EShengLingResultError;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EShengLingResultSuc:
					return ProtocolMessageProt98.EShengLingResultSuc;
				case EShengLingResultPackFul:
					return ProtocolMessageProt98.EShengLingResultPackFul;
				case EShengLingResultPrizeTaked:
					return ProtocolMessageProt98.EShengLingResultPrizeTaked;
				case EShengLingResultFailed:
					return ProtocolMessageProt98.EShengLingResultFailed;
				case EShengLingResultGoldLack:
					return ProtocolMessageProt98.EShengLingResultGoldLack;
				case EShengLingResultEnterLack:
					return ProtocolMessageProt98.EShengLingResultEnterLack;
				case EShengLingResultLifeLack:
					return ProtocolMessageProt98.EShengLingResultLifeLack;
				case EShengLingResultControlDiceLack:
					return ProtocolMessageProt98.EShengLingResultControlDiceLack;
				case EShengLingResultTurnDiceLack:
					return ProtocolMessageProt98.EShengLingResultTurnDiceLack;
				case EShengLingResultScoreLack:
					return ProtocolMessageProt98.EShengLingResultScoreLack;
				case EShengLingResultStepLack:
					return ProtocolMessageProt98.EShengLingResultStepLack;
				case EShengLingResultNotFinish:
					return ProtocolMessageProt98.EShengLingResultNotFinish;
				case EShengLingResultTypeError:
					return ProtocolMessageProt98.EShengLingResultTypeError;
				case EShengLingResultError:
					return ProtocolMessageProt98.EShengLingResultError;
				default:
					return "Unknown Error";
			}
		}
	}
}
