/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECreateRoleResult.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
 {
	import net.protocol.Message.ProtocolMessageProt3;
	/**
	 * 角色操作的结果
	 */
	public final class ECreateRoleResult
	{
		public static const eRoleSucceed:uint = 0; //成功
		public static const eRoleExist:uint = 1; //角色已存在
		public static const eRoleNameExist:uint = 2; //角色名已存在
		public static const eRoleNameInvalid:uint = 3; //角色名称有非法字符
		public static const eRoleNameTooLong:uint = 4; //角色名过长
		public static const eRoleNameTooShort:uint = 5; //角色名过短
		public static const eRoleStateErr:uint = 6; //状态错误
		public static const eRoleJobErr:uint = 7; //职业错误
		public static const eRoleSexErr:uint = 8; //性别错误
		public static const eRoleOtherErr:uint = 9; //其它错误
		public static const end:uint = eRoleOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eRoleSucceed:
					return ProtocolMessageProt3.eRoleSucceed;
				case eRoleExist:
					return ProtocolMessageProt3.eRoleExist;
				case eRoleNameExist:
					return ProtocolMessageProt3.eRoleNameExist;
				case eRoleNameInvalid:
					return ProtocolMessageProt3.eRoleNameInvalid;
				case eRoleNameTooLong:
					return ProtocolMessageProt3.eRoleNameTooLong;
				case eRoleNameTooShort:
					return ProtocolMessageProt3.eRoleNameTooShort;
				case eRoleStateErr:
					return ProtocolMessageProt3.eRoleStateErr;
				case eRoleJobErr:
					return ProtocolMessageProt3.eRoleJobErr;
				case eRoleSexErr:
					return ProtocolMessageProt3.eRoleSexErr;
				case eRoleOtherErr:
					return ProtocolMessageProt3.eRoleOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
