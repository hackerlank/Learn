/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_LoginAck.as
//  Purpose:      协议:登陆LoginServer的协议, 函数:登陆结果返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数LoginAck[登陆结果返回]的接收事件
	 */
	public final class REvt_LoginAck extends Event
	{
		public static const DATA_RECEIVE:String = "LoginProt_LoginAck";
		public static const DATA_ERROR:String = "LoginProt_LoginAck_Error";

		public var eLoginResult:uint; //(枚举类型：ELoginResult)请求登录结果
		public var qwRoleId:BigInteger; //(无符号64位整数)角色ID
		public var strGateIP:String; //GateServer的IP
		public var wGatePort:uint; //(无符号16位整数)GateServer端口
		public var dwCryptoCode:uint; //(无符号32位整数)登录验证码

		public function REvt_LoginAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_LoginAck eLoginResult={eLoginResult} qwRoleId={qwRoleId} strGateIP={strGateIP} wGatePort={wGatePort} dwCryptoCode={dwCryptoCode}/>;
			return topXml;
		}
	}
}
