/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    LoginProt.as
//  Purpose:      登陆LoginServer的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：登陆LoginServer的协议
	 */
	public class LoginProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：登陆请求
		 * @param qwUsrID (无符号64位整数)帐号ID
		 * @param usGroupID (无符号16位整数)区号
		 * @param dwVersion (无符号32位整数)版本号
		 * @param strPassword 验证key
		 */
		public function send_LoginReq(qwUsrID:BigInteger, usGroupID:uint, dwVersion:uint, strPassword:ByteArray):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwUsrID);
			bytes_.writeShort(usGroupID);
			bytes_.writeUnsignedInt(dwVersion);
			BytesUtil.writeBytes(bytes_, strPassword);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：登陆结果返回
		private function _doRecv_LoginAck(bytes:ByteArray):void
		{
			var eLoginResult:uint = bytes.readUnsignedByte(); //(枚举类型：ELoginResult)请求登录结果
			var qwRoleId:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色ID
			var strGateIP:String = BytesUtil.readString(bytes); //GateServer的IP
			var wGatePort:uint = bytes.readUnsignedShort(); //(无符号16位整数)GateServer端口
			var dwCryptoCode:uint = bytes.readUnsignedInt(); //(无符号32位整数)登录验证码
			var event_:REvt_LoginAck = new REvt_LoginAck(REvt_LoginAck.DATA_RECEIVE);
			event_.eLoginResult = eLoginResult;
			event_.qwRoleId = qwRoleId;
			event_.strGateIP = strGateIP;
			event_.wGatePort = wGatePort;
			event_.dwCryptoCode = dwCryptoCode;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:LoginProt;

		public static function get instance():LoginProt
		{
			if(_instance == null)
				_instance = new LoginProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;

		public function LoginProt()
		{
			_protID = 1;
			_recvFuncList = [
				_doRecv_LoginAck //FuncID: 1
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0 || funcID > _recvFuncList.length)
				return false;
			var func:Function;
			if(funcID > 0)
				func = _recvFuncList[funcID - 1];
			if(func != null)
			{
				func(bytes);
				return true;
			}
			return false;
		}
	}
}