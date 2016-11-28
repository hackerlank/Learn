/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECombineSlotOPType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 连携槽操作
	 */
	public final class ECombineSlotOPType
	{
		public static const eCSOPTLock:uint = 0; //关闭连携槽
		public static const eCSOPTUnLock:uint = 1; //开启连携槽
		public static const end:uint = eCSOPTUnLock;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCSOPTLock:
					return ProtocolMessageProt21.eCSOPTLock;
				case eCSOPTUnLock:
					return ProtocolMessageProt21.eCSOPTUnLock;
				default:
					return "Unknown Error";
			}
		}
	}
}
