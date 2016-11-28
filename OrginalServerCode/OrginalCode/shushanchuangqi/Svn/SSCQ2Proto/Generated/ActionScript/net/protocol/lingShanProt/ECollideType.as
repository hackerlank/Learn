/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECollideType.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
 {
	import net.protocol.Message.ProtocolMessageProt135;
	/**
	 * 碰撞类型
	 */
	public final class ECollideType
	{
		public static const eCollideType_Invalid:uint = 0; //无效数据
		public static const eCollideType_Path:uint = 1; //路径碰撞
		public static const eCollideType_Grid:uint = 2; //格子碰撞
		public static const end:uint = eCollideType_Grid;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCollideType_Invalid:
					return ProtocolMessageProt135.eCollideType_Invalid;
				case eCollideType_Path:
					return ProtocolMessageProt135.eCollideType_Path;
				case eCollideType_Grid:
					return ProtocolMessageProt135.eCollideType_Grid;
				default:
					return "Unknown Error";
			}
		}
	}
}
