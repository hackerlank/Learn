/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESwitcherType.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
 {
	import net.protocol.Message.ProtocolMessageProt5;
	/**
	 * 传送阵开关类型
	 */
	public final class ESwitcherType
	{
		public static const eSwitcherNone:uint = 0; //无
		public static const eSwitcherJump:uint = 1; //副本传送开关
		public static const eSwitcherCamp:uint = 2; //阵营选择开关
		public static const eSwitcherTower:uint = 3; //试练之塔传送开关
		public static const eSwitcherUpTower:uint = 4; //锁妖塔塔上传开关
		public static const eSwitcherDownTower:uint = 5; //锁妖塔下传开关
		public static const end:uint = eSwitcherDownTower;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSwitcherNone:
					return ProtocolMessageProt5.eSwitcherNone;
				case eSwitcherJump:
					return ProtocolMessageProt5.eSwitcherJump;
				case eSwitcherCamp:
					return ProtocolMessageProt5.eSwitcherCamp;
				case eSwitcherTower:
					return ProtocolMessageProt5.eSwitcherTower;
				case eSwitcherUpTower:
					return ProtocolMessageProt5.eSwitcherUpTower;
				case eSwitcherDownTower:
					return ProtocolMessageProt5.eSwitcherDownTower;
				default:
					return "Unknown Error";
			}
		}
	}
}
