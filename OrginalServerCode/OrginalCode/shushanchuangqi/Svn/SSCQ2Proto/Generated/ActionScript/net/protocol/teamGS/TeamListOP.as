/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    TeamListOP.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
 {
	import net.protocol.Message.ProtocolMessageProt56;
	/**
	 * 队伍状态
	 */
	public final class TeamListOP
	{
		public static const ETeam_Create:uint = 0; //队伍创建
		public static const ETeam_UpDate:uint = 1; //队伍更新
		public static const ETeam_Del:uint = 2; //队伍删除
		public static const end:uint = ETeam_Del;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ETeam_Create:
					return ProtocolMessageProt56.ETeam_Create;
				case ETeam_UpDate:
					return ProtocolMessageProt56.ETeam_UpDate;
				case ETeam_Del:
					return ProtocolMessageProt56.ETeam_Del;
				default:
					return "Unknown Error";
			}
		}
	}
}
