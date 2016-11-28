/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPropClass.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
 {
	import net.protocol.Message.ProtocolMessageProt17;
	/**
	 * 变更对象类型
	 */
	public final class EPropClass
	{
		public static const eClassRole:uint = 0; //角色
		public static const eClassFighter:uint = 1; //将
		public static const eClassEquip:uint = 2; //装备
		public static const eClassORole:uint = 3; //其他角色
		public static const end:uint = eClassORole;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eClassRole:
					return ProtocolMessageProt17.eClassRole;
				case eClassFighter:
					return ProtocolMessageProt17.eClassFighter;
				case eClassEquip:
					return ProtocolMessageProt17.eClassEquip;
				case eClassORole:
					return ProtocolMessageProt17.eClassORole;
				default:
					return "Unknown Error";
			}
		}
	}
}
