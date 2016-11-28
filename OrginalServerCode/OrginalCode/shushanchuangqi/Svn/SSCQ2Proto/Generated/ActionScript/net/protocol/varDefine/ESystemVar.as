/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESystemVar.as
//  Purpose:      Var变量定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.varDefine
 {
	import net.protocol.Message.ProtocolMessageProt62;
	/**
	 * 系统var变量(大于60000)
	 */
	public final class ESystemVar
	{
		public static const eSystemVarNone:uint = 60000; //无定义
		public static const eSystemVarArena:uint = 60001; //竞技场结算
		public static const eSystemVarGuildStatue:uint = 60002; //帮派神像奖励结算
		public static const eSystemVarGuildBattleAward:uint = 60003; //帮派战奖励结算
		public static const eSystemVarDemonTowerMaxTop:uint = 60004; //锁妖塔通关最高层数
		public static const eSystemVarQQCoinConsumeValue:uint = 60005; //QQ养成计划奖励消费额度
		public static const eSystemVarQQCoinMaxValue:uint = 60006; //QQ养成计划奖励最大额度
		public static const eSystemVarQQCoinActTime:uint = 60007; //QQ养成计划活动时间
		public static const eSystemVarAnswer:uint = 60008; //答题活动时间
		public static const eSystemVarAnswerTopicID:uint = 60009; //答题活动当前题目ID
		public static const eSystemVarZeroTime:uint = 60010; //零点时间
		public static const eSystemVarOpenServerActivity:uint = 60011; //开服活动开始时间
		public static const eSystemVar_WorldBossActBeginTime:uint = 60500; //世界BOSS开始时间
		public static const eSystemVar_WorldBossActEndTime:uint = 60501; //世界BOSS结束时间
		public static const eSystemVar_LangHuanBlessActBeginTime:uint = 60502; //琅寰福地开始时间
		public static const eSystemVar_LangHuanBlessActEndTime:uint = 60503; //琅寰福地结束时间
		public static const eSystemVar_GodChest:uint = 60504; //天赐宝箱活动
		public static const eSystemVar_DragonBallActPeriod:uint = 60506; //当前七龙珠活动第多少期
		public static const eSystemVar_SevenConsumeActBeginTime:uint = 60507; //七日消费活动开始时间
		public static const eSystemVar_SevenConsumeActEndTime:uint = 60508; //七日消费活动结束时间
		public static const eSystemVar_DragonBallActBeginTime:uint = 60509; //七龙珠活动开始时间
		public static const eSystemVar_DragonBallActEndTime:uint = 60510; //七龙珠活动结束时间
		public static const eSystemVar_NewGuildBattleGate1HP:uint = 60511; //新帮派战山头一城门血量
		public static const eSystemVar_NewGuildBattleGate2HP:uint = 60512; //新帮派战山头二城门血量
		public static const eSystemVar_NewGuildBattleGate3HP:uint = 60513; //新帮派战山头三城门血量
		public static const eSystemVar_NewGuildBattleGate1Attack:uint = 60514; //新帮派战山头一城门血量
		public static const eSystemVar_NewGuildBattleGate2Attack:uint = 60515; //新帮派战山头二城门攻击力
		public static const eSystemVar_NewGuildBattleGate3Attack:uint = 60516; //新帮派战山头三城门攻击力
		public static const eSystemVarMax:uint = 60517; //最大值
		public static const end:uint = eSystemVarMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSystemVarNone:
					return ProtocolMessageProt62.eSystemVarNone;
				case eSystemVarArena:
					return ProtocolMessageProt62.eSystemVarArena;
				case eSystemVarGuildStatue:
					return ProtocolMessageProt62.eSystemVarGuildStatue;
				case eSystemVarGuildBattleAward:
					return ProtocolMessageProt62.eSystemVarGuildBattleAward;
				case eSystemVarDemonTowerMaxTop:
					return ProtocolMessageProt62.eSystemVarDemonTowerMaxTop;
				case eSystemVarQQCoinConsumeValue:
					return ProtocolMessageProt62.eSystemVarQQCoinConsumeValue;
				case eSystemVarQQCoinMaxValue:
					return ProtocolMessageProt62.eSystemVarQQCoinMaxValue;
				case eSystemVarQQCoinActTime:
					return ProtocolMessageProt62.eSystemVarQQCoinActTime;
				case eSystemVarAnswer:
					return ProtocolMessageProt62.eSystemVarAnswer;
				case eSystemVarAnswerTopicID:
					return ProtocolMessageProt62.eSystemVarAnswerTopicID;
				case eSystemVarZeroTime:
					return ProtocolMessageProt62.eSystemVarZeroTime;
				case eSystemVarOpenServerActivity:
					return ProtocolMessageProt62.eSystemVarOpenServerActivity;
				case eSystemVar_WorldBossActBeginTime:
					return ProtocolMessageProt62.eSystemVar_WorldBossActBeginTime;
				case eSystemVar_WorldBossActEndTime:
					return ProtocolMessageProt62.eSystemVar_WorldBossActEndTime;
				case eSystemVar_LangHuanBlessActBeginTime:
					return ProtocolMessageProt62.eSystemVar_LangHuanBlessActBeginTime;
				case eSystemVar_LangHuanBlessActEndTime:
					return ProtocolMessageProt62.eSystemVar_LangHuanBlessActEndTime;
				case eSystemVar_GodChest:
					return ProtocolMessageProt62.eSystemVar_GodChest;
				case eSystemVar_DragonBallActPeriod:
					return ProtocolMessageProt62.eSystemVar_DragonBallActPeriod;
				case eSystemVar_SevenConsumeActBeginTime:
					return ProtocolMessageProt62.eSystemVar_SevenConsumeActBeginTime;
				case eSystemVar_SevenConsumeActEndTime:
					return ProtocolMessageProt62.eSystemVar_SevenConsumeActEndTime;
				case eSystemVar_DragonBallActBeginTime:
					return ProtocolMessageProt62.eSystemVar_DragonBallActBeginTime;
				case eSystemVar_DragonBallActEndTime:
					return ProtocolMessageProt62.eSystemVar_DragonBallActEndTime;
				case eSystemVar_NewGuildBattleGate1HP:
					return ProtocolMessageProt62.eSystemVar_NewGuildBattleGate1HP;
				case eSystemVar_NewGuildBattleGate2HP:
					return ProtocolMessageProt62.eSystemVar_NewGuildBattleGate2HP;
				case eSystemVar_NewGuildBattleGate3HP:
					return ProtocolMessageProt62.eSystemVar_NewGuildBattleGate3HP;
				case eSystemVar_NewGuildBattleGate1Attack:
					return ProtocolMessageProt62.eSystemVar_NewGuildBattleGate1Attack;
				case eSystemVar_NewGuildBattleGate2Attack:
					return ProtocolMessageProt62.eSystemVar_NewGuildBattleGate2Attack;
				case eSystemVar_NewGuildBattleGate3Attack:
					return ProtocolMessageProt62.eSystemVar_NewGuildBattleGate3Attack;
				case eSystemVarMax:
					return ProtocolMessageProt62.eSystemVarMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
