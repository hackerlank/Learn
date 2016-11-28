/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETaskResult.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
 {
	import net.protocol.Message.ProtocolMessageProt15;
	/**
	 * 任务的结果
	 */
	public final class ETaskResult
	{
		public static const eTaskSucceed:uint = 0; //成功
		public static const eTaskNotExist:uint = 1; //任务不存在
		public static const eTaskAlreadyAccept:uint = 2; //任务已经接取
		public static const eTaskErrFinish:uint = 3; //任务不能完成
		public static const eTaskErrGiveUp:uint = 4; //任务不能取消
		public static const eTaskErrAccept:uint = 5; //接取任务失败
		public static const eTaskErrPackFull:uint = 6; //背包已满错误
		public static const eTaskErrRepeat:uint = 7; //不能接取重复任务
		public static const eTaskErrFull:uint = 8; //已接任务数已满
		public static const eTaskErrSex:uint = 9; //性别错误
		public static const eTaskErrPrepTask:uint = 10; //前置任务
		public static const eTaskErrLevel:uint = 11; //等级不符
		public static const eTaskErrNoSelOptAward:uint = 12; //未选取奖励
		public static const eTaskErrMap:uint = 13; //所在地图不符
		public static const eTaskNoDiamond:uint = 14; //钻石不足
		public static const eTaskNoGiftCoin:uint = 15; //礼金不足
		public static const eTaskNoFamily:uint = 16; //无家族
		public static const eTaskNoGuild:uint = 17; //无公会
		public static const eTaskErrCamp:uint = 18; //阵营不对
		public static const eTaskNoRepution:uint = 19; //声望不够
		public static const eTaskNoJob:uint = 20; //职业限制
		public static const eTaskNoRace:uint = 21; //种族限制
		public static const eTaskNoGold:uint = 22; //仙石不足
		public static const eTaskNoSliver:uint = 23; //银币不足
		public static const eTaskGroupFull:uint = 24; //师门任务只能接一个
		public static const eTaskYaMenFull:uint = 25; //衙门任务只能接一个
		public static const eTaskCircleFull:uint = 26; //环任务只能接一个
		public static const eTaskErrOther:uint = 27; //其它错误
		public static const end:uint = eTaskErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTaskSucceed:
					return ProtocolMessageProt15.eTaskSucceed;
				case eTaskNotExist:
					return ProtocolMessageProt15.eTaskNotExist;
				case eTaskAlreadyAccept:
					return ProtocolMessageProt15.eTaskAlreadyAccept;
				case eTaskErrFinish:
					return ProtocolMessageProt15.eTaskErrFinish;
				case eTaskErrGiveUp:
					return ProtocolMessageProt15.eTaskErrGiveUp;
				case eTaskErrAccept:
					return ProtocolMessageProt15.eTaskErrAccept;
				case eTaskErrPackFull:
					return ProtocolMessageProt15.eTaskErrPackFull;
				case eTaskErrRepeat:
					return ProtocolMessageProt15.eTaskErrRepeat;
				case eTaskErrFull:
					return ProtocolMessageProt15.eTaskErrFull;
				case eTaskErrSex:
					return ProtocolMessageProt15.eTaskErrSex;
				case eTaskErrPrepTask:
					return ProtocolMessageProt15.eTaskErrPrepTask;
				case eTaskErrLevel:
					return ProtocolMessageProt15.eTaskErrLevel;
				case eTaskErrNoSelOptAward:
					return ProtocolMessageProt15.eTaskErrNoSelOptAward;
				case eTaskErrMap:
					return ProtocolMessageProt15.eTaskErrMap;
				case eTaskNoDiamond:
					return ProtocolMessageProt15.eTaskNoDiamond;
				case eTaskNoGiftCoin:
					return ProtocolMessageProt15.eTaskNoGiftCoin;
				case eTaskNoFamily:
					return ProtocolMessageProt15.eTaskNoFamily;
				case eTaskNoGuild:
					return ProtocolMessageProt15.eTaskNoGuild;
				case eTaskErrCamp:
					return ProtocolMessageProt15.eTaskErrCamp;
				case eTaskNoRepution:
					return ProtocolMessageProt15.eTaskNoRepution;
				case eTaskNoJob:
					return ProtocolMessageProt15.eTaskNoJob;
				case eTaskNoRace:
					return ProtocolMessageProt15.eTaskNoRace;
				case eTaskNoGold:
					return ProtocolMessageProt15.eTaskNoGold;
				case eTaskNoSliver:
					return ProtocolMessageProt15.eTaskNoSliver;
				case eTaskGroupFull:
					return ProtocolMessageProt15.eTaskGroupFull;
				case eTaskYaMenFull:
					return ProtocolMessageProt15.eTaskYaMenFull;
				case eTaskCircleFull:
					return ProtocolMessageProt15.eTaskCircleFull;
				case eTaskErrOther:
					return ProtocolMessageProt15.eTaskErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
