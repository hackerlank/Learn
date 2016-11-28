/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBGateAttackResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战城门战攻击返回结果
	 */
	public final class ENGBGateAttackResult
	{
		public static const eNGBGARSuccess:uint = 0; //攻击成功
		public static const eNGBGARFailed:uint = 1; //攻击失败
		public static const eNGBGARTargetIsDead:uint = 2; //目标已经死亡
		public static const eNGBGARSelfIsDead:uint = 3; //还在死亡冷却中
		public static const eNGBGARWrongTime:uint = 4; //不在正确的时间段内
		public static const eNGBGARDefencer:uint = 5; //防守方不能攻击城门
		public static const eNGBGARDefencerAlive:uint = 6; //存在防守方成员
		public static const end:uint = eNGBGARDefencerAlive;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBGARSuccess:
					return ProtocolMessageProt68.eNGBGARSuccess;
				case eNGBGARFailed:
					return ProtocolMessageProt68.eNGBGARFailed;
				case eNGBGARTargetIsDead:
					return ProtocolMessageProt68.eNGBGARTargetIsDead;
				case eNGBGARSelfIsDead:
					return ProtocolMessageProt68.eNGBGARSelfIsDead;
				case eNGBGARWrongTime:
					return ProtocolMessageProt68.eNGBGARWrongTime;
				case eNGBGARDefencer:
					return ProtocolMessageProt68.eNGBGARDefencer;
				case eNGBGARDefencerAlive:
					return ProtocolMessageProt68.eNGBGARDefencerAlive;
				default:
					return "Unknown Error";
			}
		}
	}
}
