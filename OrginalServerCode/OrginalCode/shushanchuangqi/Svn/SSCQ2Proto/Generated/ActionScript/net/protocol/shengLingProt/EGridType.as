/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGridType.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
 {
	import net.protocol.Message.ProtocolMessageProt98;
	/**
	 * 圣陵格子类型
	 */
	public final class EGridType
	{
		public static const EGridType_None:uint = 0; //无
		public static const EGridType_Empty:uint = 1; //空格子
		public static const EGridType_Normal:uint = 2; //普通怪物格子
		public static const EGridType_Elite:uint = 3; //精英怪物格子
		public static const EGridType_Boss:uint = 4; //Boss怪物格子
		public static const EGridType_Big:uint = 5; //小宝箱格子
		public static const EGridType_Mid:uint = 6; //中宝箱格子
		public static const EGridType_Small:uint = 7; //大宝箱格子
		public static const EGridType_Born:uint = 8; //出生格子
		public static const EGridType_Random:uint = 9; //随机格子
		public static const EGridType_Motu:uint = 10; //三消陷阱格子
		public static const EGridType_Pintu:uint = 11; //拼图陷阱格子
		public static const EGridType_Zadan:uint = 12; //砸蛋陷阱格子
		public static const EGridType_Go:uint = 13; //传送格子
		public static const EGridType_End:uint = 14; //最大值
		public static const end:uint = EGridType_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EGridType_None:
					return ProtocolMessageProt98.EGridType_None;
				case EGridType_Empty:
					return ProtocolMessageProt98.EGridType_Empty;
				case EGridType_Normal:
					return ProtocolMessageProt98.EGridType_Normal;
				case EGridType_Elite:
					return ProtocolMessageProt98.EGridType_Elite;
				case EGridType_Boss:
					return ProtocolMessageProt98.EGridType_Boss;
				case EGridType_Big:
					return ProtocolMessageProt98.EGridType_Big;
				case EGridType_Mid:
					return ProtocolMessageProt98.EGridType_Mid;
				case EGridType_Small:
					return ProtocolMessageProt98.EGridType_Small;
				case EGridType_Born:
					return ProtocolMessageProt98.EGridType_Born;
				case EGridType_Random:
					return ProtocolMessageProt98.EGridType_Random;
				case EGridType_Motu:
					return ProtocolMessageProt98.EGridType_Motu;
				case EGridType_Pintu:
					return ProtocolMessageProt98.EGridType_Pintu;
				case EGridType_Zadan:
					return ProtocolMessageProt98.EGridType_Zadan;
				case EGridType_Go:
					return ProtocolMessageProt98.EGridType_Go;
				case EGridType_End:
					return ProtocolMessageProt98.EGridType_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
