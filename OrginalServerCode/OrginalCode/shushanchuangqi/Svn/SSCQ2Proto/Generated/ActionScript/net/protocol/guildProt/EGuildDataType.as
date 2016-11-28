/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGuildDataType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派数据类型
	 */
	public final class EGuildDataType
	{
		public static const eGDTBaseInfo:uint = 0; //帮派基本数据
		public static const eGDTUser:uint = 1; //帮派成员信息
		public static const eGDTApplyInfo:uint = 2; //帮派申请列表信息
		public static const eGDTAuthority:uint = 3; //帮派职位可选权限
		public static const eGDTBuilding:uint = 4; //帮派建筑
		public static const eGDTStatue:uint = 5; //帮派神像
		public static const eGDTLog:uint = 6; //帮派日志
		public static const eGDTLSSBLog:uint = 7; //帮派灵山商店购买日志
		public static const eGDTMax:uint = 8; //最大值
		public static const eGDTTech:uint = 9; //帮派科技
		public static const end:uint = eGDTTech;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGDTBaseInfo:
					return ProtocolMessageProt16.eGDTBaseInfo;
				case eGDTUser:
					return ProtocolMessageProt16.eGDTUser;
				case eGDTApplyInfo:
					return ProtocolMessageProt16.eGDTApplyInfo;
				case eGDTAuthority:
					return ProtocolMessageProt16.eGDTAuthority;
				case eGDTBuilding:
					return ProtocolMessageProt16.eGDTBuilding;
				case eGDTStatue:
					return ProtocolMessageProt16.eGDTStatue;
				case eGDTLog:
					return ProtocolMessageProt16.eGDTLog;
				case eGDTLSSBLog:
					return ProtocolMessageProt16.eGDTLSSBLog;
				case eGDTMax:
					return ProtocolMessageProt16.eGDTMax;
				case eGDTTech:
					return ProtocolMessageProt16.eGDTTech;
				default:
					return "Unknown Error";
			}
		}
	}
}
