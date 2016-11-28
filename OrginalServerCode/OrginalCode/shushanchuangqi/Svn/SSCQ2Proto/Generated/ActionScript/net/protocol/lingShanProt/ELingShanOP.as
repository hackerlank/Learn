/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELingShanOP.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
 {
	import net.protocol.Message.ProtocolMessageProt135;
	/**
	 * 灵山操作结果
	 */
	public final class ELingShanOP
	{
		public static const eLingShanOP_Sucess:uint = 0; //成功
		public static const eLingShanOP_Fail:uint = 1; //失败
		public static const eLingShanOP_Cd:uint = 2; //cd
		public static const eLingShanOP_ErrorPath:uint = 3; //目标点错误,没有路径
		public static const eLingShanOP_NoMove:uint = 4; //目前状态无法移动
		public static const eLingShanOP_NoOpen:uint = 5; //活动未开始
		public static const eLingShanOP_NoReg:uint = 6; //未报名
		public static const eLingShanOP_ErrorRoomId:uint = 7; //错误的房间
		public static const eLingShanOP_MoveCd:uint = 8; //移动cd限制
		public static const eLingShanOP_MapCFG:uint = 9; //获取地图配置错误
		public static const eLingShanOP_NotInRoom:uint = 10; //不在比赛地图
		public static const eLingShanOP_ErrorModelID:uint = 11; //错误的模型ｉｄ
		public static const eLingShanOP_ErrorCondID:uint = 12; //开启条件不满足
		public static const eLingShanOP_ActEnded:uint = 13; //活动已结束
		public static const eLingShanOP_ChatCD:uint = 14; //聊天ｃｄ
		public static const eLingShanOP_End:uint = 15;
		public static const end:uint = eLingShanOP_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLingShanOP_Sucess:
					return ProtocolMessageProt135.eLingShanOP_Sucess;
				case eLingShanOP_Fail:
					return ProtocolMessageProt135.eLingShanOP_Fail;
				case eLingShanOP_Cd:
					return ProtocolMessageProt135.eLingShanOP_Cd;
				case eLingShanOP_ErrorPath:
					return ProtocolMessageProt135.eLingShanOP_ErrorPath;
				case eLingShanOP_NoMove:
					return ProtocolMessageProt135.eLingShanOP_NoMove;
				case eLingShanOP_NoOpen:
					return ProtocolMessageProt135.eLingShanOP_NoOpen;
				case eLingShanOP_NoReg:
					return ProtocolMessageProt135.eLingShanOP_NoReg;
				case eLingShanOP_ErrorRoomId:
					return ProtocolMessageProt135.eLingShanOP_ErrorRoomId;
				case eLingShanOP_MoveCd:
					return ProtocolMessageProt135.eLingShanOP_MoveCd;
				case eLingShanOP_MapCFG:
					return ProtocolMessageProt135.eLingShanOP_MapCFG;
				case eLingShanOP_NotInRoom:
					return ProtocolMessageProt135.eLingShanOP_NotInRoom;
				case eLingShanOP_ErrorModelID:
					return ProtocolMessageProt135.eLingShanOP_ErrorModelID;
				case eLingShanOP_ErrorCondID:
					return ProtocolMessageProt135.eLingShanOP_ErrorCondID;
				case eLingShanOP_ActEnded:
					return ProtocolMessageProt135.eLingShanOP_ActEnded;
				case eLingShanOP_ChatCD:
					return ProtocolMessageProt135.eLingShanOP_ChatCD;
				case eLingShanOP_End:
					return ProtocolMessageProt135.eLingShanOP_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
