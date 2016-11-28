/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGEMBattleType.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
 {
	import net.protocol.Message.ProtocolMessageProt86;
	/**
	 * 战斗类型
	 */
	public final class EGEMBattleType
	{
		public static const eGEMBattleTypeA:int = 0; //播放战报战斗
		public static const eGEMBattleTypeB:int = 1; //不播放战报战斗
		public static const end:int = eGEMBattleTypeB;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eGEMBattleTypeA:
					return ProtocolMessageProt86.eGEMBattleTypeA;
				case eGEMBattleTypeB:
					return ProtocolMessageProt86.eGEMBattleTypeB;
				default:
					return "Unknown Error";
			}
		}
	}
}
