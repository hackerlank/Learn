/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDemonTowerPrize.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
 {
	import net.protocol.Message.ProtocolMessageProt71;
	/**
	 * 领取奖励
	 */
	public final class EDemonTowerPrize
	{
		public static const eDemonTower_Prize_Fail:uint = 1; //镇守失败奖励
		public static const eDemonTower_Prize_Day:uint = 2; //镇守1天收益奖励
		public static const eDemonTower_Prize_Seal:uint = 3; //封印每天奖励(改成gmeserver领取)
		public static const end:uint = eDemonTower_Prize_Seal;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDemonTower_Prize_Fail:
					return ProtocolMessageProt71.eDemonTower_Prize_Fail;
				case eDemonTower_Prize_Day:
					return ProtocolMessageProt71.eDemonTower_Prize_Day;
				case eDemonTower_Prize_Seal:
					return ProtocolMessageProt71.eDemonTower_Prize_Seal;
				default:
					return "Unknown Error";
			}
		}
	}
}
