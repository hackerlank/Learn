/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELoginResult.as
//  Purpose:      登陆LoginServer的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginProt
 {
	import net.protocol.Message.ProtocolMessageProt1;
	/**
	 * 登陆结果
	 */
	public final class ELoginResult
	{
		public static const eLoginSucceed:uint = 0; //登陆成功
		public static const eVersionLess:uint = 1; //客户端版本号低于服务器
		public static const eNotActivated:uint = 2; //帐号未激活此区服
		public static const eAccountInvalid:uint = 3; //帐号错误
		public static const ePasswordInvalid:uint = 4; //密码错误
		public static const eAccPwdErr:uint = 5; //账号不存在或密码错误
		public static const eUsrStateErr:uint = 6; //帐号状态异常
		public static const eAccountFreeze:uint = 7; //帐号冻结
		public static const eAccountLogin:uint = 8; //帐号正在登陆中
		public static const eReqOverTime:uint = 9; //请求超时
		public static const eReqTooFreqent:uint = 10; //请求太频繁
		public static const eServerFull:uint = 11; //服务器已满
		public static const eRoleOnline:uint = 12; //已有角色在线
		public static const eKickWait:uint = 13; //踢帐号等待
		public static const eLeaveWait:uint = 14; //下线等待
		public static const eEnterTooFreqent:uint = 15; //请求太频繁
		public static const eLoginServerErr:uint = 16; //服务器内部错误
		public static const eServerInitErr:uint = 17; //服务器未启动完毕
		public static const eLoginOtherErr:uint = 18; //系统错误
		public static const end:uint = eLoginOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLoginSucceed:
					return ProtocolMessageProt1.eLoginSucceed;
				case eVersionLess:
					return ProtocolMessageProt1.eVersionLess;
				case eNotActivated:
					return ProtocolMessageProt1.eNotActivated;
				case eAccountInvalid:
					return ProtocolMessageProt1.eAccountInvalid;
				case ePasswordInvalid:
					return ProtocolMessageProt1.ePasswordInvalid;
				case eAccPwdErr:
					return ProtocolMessageProt1.eAccPwdErr;
				case eUsrStateErr:
					return ProtocolMessageProt1.eUsrStateErr;
				case eAccountFreeze:
					return ProtocolMessageProt1.eAccountFreeze;
				case eAccountLogin:
					return ProtocolMessageProt1.eAccountLogin;
				case eReqOverTime:
					return ProtocolMessageProt1.eReqOverTime;
				case eReqTooFreqent:
					return ProtocolMessageProt1.eReqTooFreqent;
				case eServerFull:
					return ProtocolMessageProt1.eServerFull;
				case eRoleOnline:
					return ProtocolMessageProt1.eRoleOnline;
				case eKickWait:
					return ProtocolMessageProt1.eKickWait;
				case eLeaveWait:
					return ProtocolMessageProt1.eLeaveWait;
				case eEnterTooFreqent:
					return ProtocolMessageProt1.eEnterTooFreqent;
				case eLoginServerErr:
					return ProtocolMessageProt1.eLoginServerErr;
				case eServerInitErr:
					return ProtocolMessageProt1.eServerInitErr;
				case eLoginOtherErr:
					return ProtocolMessageProt1.eLoginOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
