/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGatherResult.as
//  Purpose:      采集协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
 {
	import net.protocol.Message.ProtocolMessageProt60;
	/**
	 * 副本结果
	 */
	public final class EGatherResult
	{
		public static const eGatherSuccess:uint = 0; //成功
		public static const eGatherIn:uint = 1; //正在采集中
		public static const eGatherOut:uint = 2; //没有采集中
		public static const eGatherItemLimit:uint = 3; //采集所需物品不足
		public static const eGatherBusy:uint = 4; //玩家忙
		public static const eGatherPackEmptyMin:uint = 5; //采集空格子不足
		public static const eGatherVIP:uint = 6; //御剑等级不足
		public static const eGatherLevel:uint = 7; //等级不足
		public static const eGatherNotExist:uint = 8; //采集物不存在
		public static const eGatherTooFar:uint = 9; //采集物太远
		public static const eGatherNumLimit:uint = 10; //采集物数量不足
		public static const eGatherTask:uint = 11; //需要接相关任务才可以采集
		public static const eGatherCancel:uint = 12; //采集中断
		public static const eGatherFinish:uint = 13; //采集完成
		public static const eGatherLuaErr:uint = 14; //Lua脚本拒绝
		public static const eGatherOtherErr:uint = 15; //未知错误
		public static const end:uint = eGatherOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGatherSuccess:
					return ProtocolMessageProt60.eGatherSuccess;
				case eGatherIn:
					return ProtocolMessageProt60.eGatherIn;
				case eGatherOut:
					return ProtocolMessageProt60.eGatherOut;
				case eGatherItemLimit:
					return ProtocolMessageProt60.eGatherItemLimit;
				case eGatherBusy:
					return ProtocolMessageProt60.eGatherBusy;
				case eGatherPackEmptyMin:
					return ProtocolMessageProt60.eGatherPackEmptyMin;
				case eGatherVIP:
					return ProtocolMessageProt60.eGatherVIP;
				case eGatherLevel:
					return ProtocolMessageProt60.eGatherLevel;
				case eGatherNotExist:
					return ProtocolMessageProt60.eGatherNotExist;
				case eGatherTooFar:
					return ProtocolMessageProt60.eGatherTooFar;
				case eGatherNumLimit:
					return ProtocolMessageProt60.eGatherNumLimit;
				case eGatherTask:
					return ProtocolMessageProt60.eGatherTask;
				case eGatherCancel:
					return ProtocolMessageProt60.eGatherCancel;
				case eGatherFinish:
					return ProtocolMessageProt60.eGatherFinish;
				case eGatherLuaErr:
					return ProtocolMessageProt60.eGatherLuaErr;
				case eGatherOtherErr:
					return ProtocolMessageProt60.eGatherOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
