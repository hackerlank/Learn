/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWorshipType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 捐献类型
	 */
	public final class EWorshipType
	{
		public static const eWorshipNone:uint = 0; //无效供奉类型
		public static const eWorshipFlower:uint = 1; //鲜花供奉
		public static const eWorshipRedFruit:uint = 2; //朱果供奉
		public static const eWorshipPeach:uint = 3; //蟠桃供奉
		public static const eWorshipMax:uint = 4; //供奉类型最大值
		public static const end:uint = eWorshipMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWorshipNone:
					return ProtocolMessageProt16.eWorshipNone;
				case eWorshipFlower:
					return ProtocolMessageProt16.eWorshipFlower;
				case eWorshipRedFruit:
					return ProtocolMessageProt16.eWorshipRedFruit;
				case eWorshipPeach:
					return ProtocolMessageProt16.eWorshipPeach;
				case eWorshipMax:
					return ProtocolMessageProt16.eWorshipMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
