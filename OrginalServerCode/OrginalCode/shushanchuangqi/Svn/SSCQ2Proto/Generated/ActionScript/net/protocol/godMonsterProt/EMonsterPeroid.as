/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMonsterPeroid.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
 {
	import net.protocol.Message.ProtocolMessageProt96;
	/**
	 * 神兽阶段
	 */
	public final class EMonsterPeroid
	{
		public static const EMonsterPeroid_none:uint = 0; //无
		public static const EMonsterPeroid_1:uint = 1; //神兽元胎
		public static const EMonsterPeroid_2:uint = 2; //神兽幼年期
		public static const EMonsterPeroid_3:uint = 3; //神兽成年期
		public static const EMonsterPeroid_4:uint = 4; //神兽青年期
		public static const EMonsterPeroid_5:uint = 5; //亚圣兽期
		public static const EMonsterPeroid_6:uint = 6; //天元神兽
		public static const EMonsterPeroid_end:uint = 7; //最大值
		public static const end:uint = EMonsterPeroid_end;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMonsterPeroid_none:
					return ProtocolMessageProt96.EMonsterPeroid_none;
				case EMonsterPeroid_1:
					return ProtocolMessageProt96.EMonsterPeroid_1;
				case EMonsterPeroid_2:
					return ProtocolMessageProt96.EMonsterPeroid_2;
				case EMonsterPeroid_3:
					return ProtocolMessageProt96.EMonsterPeroid_3;
				case EMonsterPeroid_4:
					return ProtocolMessageProt96.EMonsterPeroid_4;
				case EMonsterPeroid_5:
					return ProtocolMessageProt96.EMonsterPeroid_5;
				case EMonsterPeroid_6:
					return ProtocolMessageProt96.EMonsterPeroid_6;
				case EMonsterPeroid_end:
					return ProtocolMessageProt96.EMonsterPeroid_end;
				default:
					return "Unknown Error";
			}
		}
	}
}
