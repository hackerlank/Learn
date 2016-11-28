/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMonsterRank.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
 {
	import net.protocol.Message.ProtocolMessageProt96;
	/**
	 * 排行榜
	 */
	public final class EMonsterRank
	{
		public static const EMonsterRank_none:uint = 0; //无
		public static const EMonsterRank_1:uint = 1; //个人榜
		public static const EMonsterRank_2:uint = 2; //帮派榜
		public static const EMonsterRank_end:uint = 3; //最大值
		public static const end:uint = EMonsterRank_end;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMonsterRank_none:
					return ProtocolMessageProt96.EMonsterRank_none;
				case EMonsterRank_1:
					return ProtocolMessageProt96.EMonsterRank_1;
				case EMonsterRank_2:
					return ProtocolMessageProt96.EMonsterRank_2;
				case EMonsterRank_end:
					return ProtocolMessageProt96.EMonsterRank_end;
				default:
					return "Unknown Error";
			}
		}
	}
}
