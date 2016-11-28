/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBCaveAttackResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战洞府战战斗返回结果
	 */
	public final class ENGBCaveAttackResult
	{
		public static const eNGBCARSuccess:uint = 0; //战斗成功
		public static const eNGBCARFailed:uint = 1; //战斗失败
		public static const eNGBCARBeCaptured:uint = 2; //已被他人占领
		public static const eNGBCARCountLimit:uint = 3; //已经到达上限
		public static const eNGBCARWrongTime:uint = 4; //不在正确的时间段内
		public static const eNGBCARTargetDead:uint = 5; //目标已经死亡
		public static const eNGBCARNotInCore:uint = 6; //不在阵眼上
		public static const eNGBCARInCore:uint = 7; //在阵眼上无法攻击
		public static const eNGBCARSelfIsDead:uint = 8; //还在死亡冷却中
		public static const eNGBCARSelfSide:uint = 9; //不能攻击自己人
		public static const end:uint = eNGBCARSelfSide;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBCARSuccess:
					return ProtocolMessageProt68.eNGBCARSuccess;
				case eNGBCARFailed:
					return ProtocolMessageProt68.eNGBCARFailed;
				case eNGBCARBeCaptured:
					return ProtocolMessageProt68.eNGBCARBeCaptured;
				case eNGBCARCountLimit:
					return ProtocolMessageProt68.eNGBCARCountLimit;
				case eNGBCARWrongTime:
					return ProtocolMessageProt68.eNGBCARWrongTime;
				case eNGBCARTargetDead:
					return ProtocolMessageProt68.eNGBCARTargetDead;
				case eNGBCARNotInCore:
					return ProtocolMessageProt68.eNGBCARNotInCore;
				case eNGBCARInCore:
					return ProtocolMessageProt68.eNGBCARInCore;
				case eNGBCARSelfIsDead:
					return ProtocolMessageProt68.eNGBCARSelfIsDead;
				case eNGBCARSelfSide:
					return ProtocolMessageProt68.eNGBCARSelfSide;
				default:
					return "Unknown Error";
			}
		}
	}
}
