/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAttackedType.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
 {
	import net.protocol.Message.ProtocolMessageProt70;
	/**
	 * 被攻击类型
	 */
	public final class EAttackedType
	{
		public static const eAttackedType_DemonTower:uint = 1; //锁妖塔
		public static const end:uint = eAttackedType_DemonTower;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAttackedType_DemonTower:
					return ProtocolMessageProt70.eAttackedType_DemonTower;
				default:
					return "Unknown Error";
			}
		}
	}
}
