/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECareerType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 枚举类型示例
	 */
	public final class ECareerType
	{
		public static const ECAREER_ALL:uint = 0; //所有职业
		public static const ECAREER_RU:uint = 1; //儒
		public static const ECAREER_SHI:uint = 2; //释
		public static const ECAREER_DAO:uint = 3; //道
		public static const ECAREER_MO:uint = 4; //墨
		public static const ECAREER_MAX:uint = 5; //最大值
		public static const end:uint = ECAREER_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ECAREER_ALL:
					return ProtocolMessageProt258.ECAREER_ALL;
				case ECAREER_RU:
					return ProtocolMessageProt258.ECAREER_RU;
				case ECAREER_SHI:
					return ProtocolMessageProt258.ECAREER_SHI;
				case ECAREER_DAO:
					return ProtocolMessageProt258.ECAREER_DAO;
				case ECAREER_MO:
					return ProtocolMessageProt258.ECAREER_MO;
				case ECAREER_MAX:
					return ProtocolMessageProt258.ECAREER_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
