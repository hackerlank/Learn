/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBSide.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战战斗方向
	 */
	public final class ENGBSide
	{
		public static const eNGBSideAttacker:uint = 0; //进攻方
		public static const eNGBSideDefencer:uint = 1; //防守方
		public static const eNGBSideInvalid:uint = 2; //无效方
		public static const end:uint = eNGBSideInvalid;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBSideAttacker:
					return ProtocolMessageProt68.eNGBSideAttacker;
				case eNGBSideDefencer:
					return ProtocolMessageProt68.eNGBSideDefencer;
				case eNGBSideInvalid:
					return ProtocolMessageProt68.eNGBSideInvalid;
				default:
					return "Unknown Error";
			}
		}
	}
}
