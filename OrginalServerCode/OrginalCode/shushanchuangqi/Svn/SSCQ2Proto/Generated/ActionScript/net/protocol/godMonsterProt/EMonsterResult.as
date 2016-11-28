/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMonsterResult.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
 {
	import net.protocol.Message.ProtocolMessageProt96;
	/**
	 * 操作结果
	 */
	public final class EMonsterResult
	{
		public static const EMonsterResult_suc:uint = 0; //操作成功
		public static const EMonsterResult_ful:uint = 1; //背包满
		public static const EMonsterResult_get:uint = 2; //奖励已经领取
		public static const EMonsterResult_not:uint = 3; //无此奖励
		public static const EMonsterResult_lack:uint = 4; //仙石不足
		public static const EMonsterResult_Level:uint = 5; //等级不够
		public static const EMonsterResult_Devote:uint = 6; //贡献度不够
		public static const EMonsterResult_guild:uint = 7; //不在帮派
		public static const EMonsterResult_Num:uint = 8; //数量不足
		public static const EMonsterResult_Err:uint = 9; //操作失败
		public static const end:uint = EMonsterResult_Err;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMonsterResult_suc:
					return ProtocolMessageProt96.EMonsterResult_suc;
				case EMonsterResult_ful:
					return ProtocolMessageProt96.EMonsterResult_ful;
				case EMonsterResult_get:
					return ProtocolMessageProt96.EMonsterResult_get;
				case EMonsterResult_not:
					return ProtocolMessageProt96.EMonsterResult_not;
				case EMonsterResult_lack:
					return ProtocolMessageProt96.EMonsterResult_lack;
				case EMonsterResult_Level:
					return ProtocolMessageProt96.EMonsterResult_Level;
				case EMonsterResult_Devote:
					return ProtocolMessageProt96.EMonsterResult_Devote;
				case EMonsterResult_guild:
					return ProtocolMessageProt96.EMonsterResult_guild;
				case EMonsterResult_Num:
					return ProtocolMessageProt96.EMonsterResult_Num;
				case EMonsterResult_Err:
					return ProtocolMessageProt96.EMonsterResult_Err;
				default:
					return "Unknown Error";
			}
		}
	}
}
