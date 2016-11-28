/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EXiheStage.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 羲和神车任务阶段
	 */
	public final class EXiheStage
	{
		public static const eXiheStageShipGoods:uint = 0; //装货阶段
		public static const eXiheStageTaskCool:uint = 1; //冷却阶段
		public static const eXiheStageWaitAcess:uint = 2; //等待玩家接取任务
		public static const end:uint = eXiheStageWaitAcess;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eXiheStageShipGoods:
					return ProtocolMessageProt16.eXiheStageShipGoods;
				case eXiheStageTaskCool:
					return ProtocolMessageProt16.eXiheStageTaskCool;
				case eXiheStageWaitAcess:
					return ProtocolMessageProt16.eXiheStageWaitAcess;
				default:
					return "Unknown Error";
			}
		}
	}
}
