/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGEMBattleRet.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
 {
	import net.protocol.Message.ProtocolMessageProt86;
	/**
	 * 战斗结果
	 */
	public final class EGEMBattleRet
	{
		public static const eGEMBattleFailed:int = 0; //战斗失败
		public static const eGEMBattleSucc:int = 1; //战斗成功
		public static const end:int = eGEMBattleSucc;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eGEMBattleFailed:
					return ProtocolMessageProt86.eGEMBattleFailed;
				case eGEMBattleSucc:
					return ProtocolMessageProt86.eGEMBattleSucc;
				default:
					return "Unknown Error";
			}
		}
	}
}
