/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELHBResult.as
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
 {
	import net.protocol.Message.ProtocolMessageProt79;
	/**
	 * 操作结果
	 */
	public final class ELHBResult
	{
		public static const eLHBResult_none:uint = 0; //无此技能
		public static const eLHBResult_empty:uint = 1; //次数用完
		public static const eLHBResult_inCD:uint = 2; //技能CD中
		public static const eLHBResult_hasBuff:uint = 3; //身上有Buff
		public static const eLHBResult_success:uint = 4; //操作成功
		public static const eLHBResult_CMapError:uint = 5; //创建地图失败
		public static const eLHBResult_enterMapError:uint = 6; //进入地图失败
		public static const eLHBResult_otherError:uint = 7; //其他错误
		public static const eLHBResult_lowLevel:uint = 8; //玩家等级不够
		public static const eLHBResult_notBegin:uint = 9; //活动未开始
		public static const eLHBResult_end:uint = 10; //玩家已经结束
		public static const eLHBResult_wait5min:uint = 11; //玩家逃跑需要等待5分钟
		public static const end:uint = eLHBResult_wait5min;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLHBResult_none:
					return ProtocolMessageProt79.eLHBResult_none;
				case eLHBResult_empty:
					return ProtocolMessageProt79.eLHBResult_empty;
				case eLHBResult_inCD:
					return ProtocolMessageProt79.eLHBResult_inCD;
				case eLHBResult_hasBuff:
					return ProtocolMessageProt79.eLHBResult_hasBuff;
				case eLHBResult_success:
					return ProtocolMessageProt79.eLHBResult_success;
				case eLHBResult_CMapError:
					return ProtocolMessageProt79.eLHBResult_CMapError;
				case eLHBResult_enterMapError:
					return ProtocolMessageProt79.eLHBResult_enterMapError;
				case eLHBResult_otherError:
					return ProtocolMessageProt79.eLHBResult_otherError;
				case eLHBResult_lowLevel:
					return ProtocolMessageProt79.eLHBResult_lowLevel;
				case eLHBResult_notBegin:
					return ProtocolMessageProt79.eLHBResult_notBegin;
				case eLHBResult_end:
					return ProtocolMessageProt79.eLHBResult_end;
				case eLHBResult_wait5min:
					return ProtocolMessageProt79.eLHBResult_wait5min;
				default:
					return "Unknown Error";
			}
		}
	}
}
