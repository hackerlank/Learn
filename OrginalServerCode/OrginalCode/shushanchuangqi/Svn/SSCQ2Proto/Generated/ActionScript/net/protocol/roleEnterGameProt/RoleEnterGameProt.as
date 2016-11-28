/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    RoleEnterGameProt.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：角色信息相关操作协议
	 */
	public class RoleEnterGameProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求进入游戏
		 * @param stEnterParam 信息
		 */
		public function send_EnterGameReq(stEnterParam:SEnterParam):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			stEnterParam.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：创建角色请求
		 * @param stCreateInfo 创角信息
		 */
		public function send_CreateRoleReq(stCreateInfo:SCreateRoleInfo):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			stCreateInfo.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家请求推荐名字
		 * @param byIsMale (无符号8位整数)非0表示男性
		 */
		public function send_PlayerRamdomNameReq(byIsMale:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeByte(byIsMale);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：角色信息查询
		 */
		public function send_GetUserInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：请求进入游戏应答
		private function _doRecv_EnterGameAck(bytes:ByteArray):void
		{
			var eEnterResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEnterResult)登陆结果
			var dwNowTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)目前服务器的时间
			var event_:REvt_EnterGameAck = new REvt_EnterGameAck(REvt_EnterGameAck.DATA_RECEIVE);
			event_.eEnterResult = eEnterResult;
			event_.dwNowTimer = dwNowTimer;
			dispatchEvent(event_);
		}

		//接收处理：创建角色应答
		private function _doRecv_CreateRoleAck(bytes:ByteArray):void
		{
			var eCreateRoleResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECreateRoleResult)创建结果
			var event_:REvt_CreateRoleAck = new REvt_CreateRoleAck(REvt_CreateRoleAck.DATA_RECEIVE);
			event_.eCreateRoleResult = eCreateRoleResult;
			dispatchEvent(event_);
		}

		//接收处理：玩家请求推荐名字返回
		private function _doRecv_PlayerRamdomNameAck(bytes:ByteArray):void
		{
			var strName:String = BytesUtil.readString(bytes); //空表示没有得到
			var event_:REvt_PlayerRamdomNameAck = new REvt_PlayerRamdomNameAck(REvt_PlayerRamdomNameAck.DATA_RECEIVE);
			event_.strName = strName;
			dispatchEvent(event_);
		}

		//接收处理：角色查询返回
		private function _doRecv_GetUserInfoAck(bytes:ByteArray):void
		{
			var stRoleEnterInfo:RoleEnterGameData = RoleEnterGameData.fromByteArray(bytes); //进入信息
			var event_:REvt_GetUserInfoAck = new REvt_GetUserInfoAck(REvt_GetUserInfoAck.DATA_RECEIVE);
			event_.stRoleEnterInfo = stRoleEnterInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:RoleEnterGameProt;

		public static function get instance():RoleEnterGameProt
		{
			if(_instance == null)
				_instance = new RoleEnterGameProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;

		public function RoleEnterGameProt()
		{
			_protID = 3;
			_recvFuncList = [
				_doRecv_EnterGameAck, //FuncID: 1
				_doRecv_CreateRoleAck, //FuncID: 2
				_doRecv_PlayerRamdomNameAck, //FuncID: 3
				_doRecv_GetUserInfoAck //FuncID: 4
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