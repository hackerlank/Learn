/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMapParam.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
 {
	import net.protocol.Message.ProtocolMessageProt5;
	/**
	 * 地图附加数据
	 */
	public final class EMapParam
	{
		public static const eMapParamDemonFloorID:uint = 0; //镇妖塔层数
		public static const eMapParamEnd:uint = 3; //数组最大长度，上面索引不同功能可以重复
		public static const end:uint = eMapParamEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eMapParamDemonFloorID:
					return ProtocolMessageProt5.eMapParamDemonFloorID;
				case eMapParamEnd:
					return ProtocolMessageProt5.eMapParamEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
