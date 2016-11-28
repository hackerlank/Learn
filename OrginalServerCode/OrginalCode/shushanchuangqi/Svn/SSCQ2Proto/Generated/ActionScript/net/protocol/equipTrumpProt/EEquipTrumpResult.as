/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝操作结果
	 */
	public final class EEquipTrumpResult
	{
		public static const eETRSuccess:uint = 0; //成功
		public static const eETRFailed:uint = 1; //失败
		public static const eETRNotExist:uint = 2; //不存在
		public static const eETRInOthers:uint = 3; //在其他人身上
		public static const eETRSlotFull:uint = 4; //槽位已满
		public static const eETRSlotLock:uint = 5; //槽位未开启
		public static const eETRSlotConflict:uint = 6; //法宝冲突
		public static const eETRMax:uint = 7; //最大值
		public static const end:uint = eETRMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eETRSuccess:
					return ProtocolMessageProt30.eETRSuccess;
				case eETRFailed:
					return ProtocolMessageProt30.eETRFailed;
				case eETRNotExist:
					return ProtocolMessageProt30.eETRNotExist;
				case eETRInOthers:
					return ProtocolMessageProt30.eETRInOthers;
				case eETRSlotFull:
					return ProtocolMessageProt30.eETRSlotFull;
				case eETRSlotLock:
					return ProtocolMessageProt30.eETRSlotLock;
				case eETRSlotConflict:
					return ProtocolMessageProt30.eETRSlotConflict;
				case eETRMax:
					return ProtocolMessageProt30.eETRMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
