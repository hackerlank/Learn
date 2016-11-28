/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAppearState.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
 {
	import net.protocol.Message.ProtocolMessageProt5;
	/**
	 * 地图上生物的外观状态
	 */
	public final class EAppearState
	{
		public static const eAppearNone:uint = 0; //无
		public static const eAppearFight:uint = 1; //战斗状态
		public static const eAppearGhost:uint = 2; //灵魂状态
		public static const eAppearDie:uint = 3; //死亡状态
		public static const end:uint = eAppearDie;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAppearNone:
					return ProtocolMessageProt5.eAppearNone;
				case eAppearFight:
					return ProtocolMessageProt5.eAppearFight;
				case eAppearGhost:
					return ProtocolMessageProt5.eAppearGhost;
				case eAppearDie:
					return ProtocolMessageProt5.eAppearDie;
				default:
					return "Unknown Error";
			}
		}
	}
}
