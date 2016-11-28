/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELingShanStatus.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
 {
	import net.protocol.Message.ProtocolMessageProt135;
	/**
	 * 玩家状态
	 */
	public final class ELingShanStatus
	{
		public static const eLingShanStatus_Init:uint = 0; //未报名状态
		public static const eLingShanStatus_Wait:uint = 1; //排队状态
		public static const eLingShanStatus_Move:uint = 2; //可移动状态
		public static const eLingShanStatus_PlayMovie:uint = 3; //播放动画状态
		public static const eLingShanStatus_End:uint = 4; //活动结束状态
		public static const end:uint = eLingShanStatus_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLingShanStatus_Init:
					return ProtocolMessageProt135.eLingShanStatus_Init;
				case eLingShanStatus_Wait:
					return ProtocolMessageProt135.eLingShanStatus_Wait;
				case eLingShanStatus_Move:
					return ProtocolMessageProt135.eLingShanStatus_Move;
				case eLingShanStatus_PlayMovie:
					return ProtocolMessageProt135.eLingShanStatus_PlayMovie;
				case eLingShanStatus_End:
					return ProtocolMessageProt135.eLingShanStatus_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
