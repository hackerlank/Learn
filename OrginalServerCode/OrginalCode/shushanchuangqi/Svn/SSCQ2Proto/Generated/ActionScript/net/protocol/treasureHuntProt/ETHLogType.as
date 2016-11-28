/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETHLogType.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
 {
	import net.protocol.Message.ProtocolMessageProt85;
	/**
	 * 寻宝日志类型
	 */
	public final class ETHLogType
	{
		public static const eTHLogTypeA:int = 0; //遇到怪物/BOSS (注：参数：NPCID)
		public static const eTHLogTypeB:int = 1; //击败怪物 (注：参数：NPCID)
		public static const eTHLogTypeC:int = 2; //获得银币 (注：参数：Silver)
		public static const eTHLogTypeD:int = 3; //获得修为 (注：参数：Pexp)
		public static const eTHLogTypeE:int = 4; //获得宝物 (注：参数：ItemNum)
		public static const eTHLogTypeF:int = 5; //击败BOSS,造成XX伤害 (注：参数：BOSSID, HPValue)
		public static const eTHLogTypeG:int = 6; //被BOSS击败,查看战报 (注：参数：BOSSID, HPValue, ReportID)
		public static const eTHLogTypeH:int = 7; //使用BUFF (注：参数：BUFFID)
		public static const eTHLogTypeI:int = 8; //对BOSS,造成XX伤害 (注：参数：BOSSID, HPValue)
		public static const eTHLogTypeJ:int = 9; //获得心法残页数量 (注：参数：XFCYNum)
		public static const end:int = eTHLogTypeJ;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eTHLogTypeA:
					return ProtocolMessageProt85.eTHLogTypeA;
				case eTHLogTypeB:
					return ProtocolMessageProt85.eTHLogTypeB;
				case eTHLogTypeC:
					return ProtocolMessageProt85.eTHLogTypeC;
				case eTHLogTypeD:
					return ProtocolMessageProt85.eTHLogTypeD;
				case eTHLogTypeE:
					return ProtocolMessageProt85.eTHLogTypeE;
				case eTHLogTypeF:
					return ProtocolMessageProt85.eTHLogTypeF;
				case eTHLogTypeG:
					return ProtocolMessageProt85.eTHLogTypeG;
				case eTHLogTypeH:
					return ProtocolMessageProt85.eTHLogTypeH;
				case eTHLogTypeI:
					return ProtocolMessageProt85.eTHLogTypeI;
				case eTHLogTypeJ:
					return ProtocolMessageProt85.eTHLogTypeJ;
				default:
					return "Unknown Error";
			}
		}
	}
}
