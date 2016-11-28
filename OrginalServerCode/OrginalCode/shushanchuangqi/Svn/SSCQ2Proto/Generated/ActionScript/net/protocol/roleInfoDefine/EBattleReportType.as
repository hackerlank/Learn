/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleReportType.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
 {
	import net.protocol.Message.ProtocolMessageProt10;
	/**
	 * 战报类型
	 */
	public final class EBattleReportType
	{
		public static const eTypeLadder:uint = 0; //天梯
		public static const end:uint = eTypeLadder;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTypeLadder:
					return ProtocolMessageProt10.eTypeLadder;
				default:
					return "Unknown Error";
			}
		}
	}
}
