/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    BattleGS.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.itemProt.SResource;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：战斗通信协议
	 */
	public class BattleGS extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求战斗
		 * @param qwDefenseID (无符号64位整数)防守ID
		 */
		public function send_BattleReq(qwDefenseID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwDefenseID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求战报
		 * @param qwReportID (无符号64位整数)请求战报ID
		 * @param qwMasterID (无符号64位整数)视角角色ID
		 */
		public function send_BattleReportReq(qwReportID:BigInteger, qwMasterID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwReportID);
			BytesUtil.writeUInt64(bytes_, qwMasterID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：战报阅读完成
		 * @param qwReportID (无符号64位整数)请求战报ID
		 */
		public function send_FinishBattleReport(qwReportID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwReportID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：战斗请求结果
		private function _doRecv_BattleAck(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EBattleReqResult)返回结果
			var event_:REvt_BattleAck = new REvt_BattleAck(REvt_BattleAck.DATA_RECEIVE);
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		//接收处理：请求战报结果
		private function _doRecv_BattleReportAck(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EReportReqResult)战报请求结果
			var event_:REvt_BattleReportAck = new REvt_BattleReportAck(REvt_BattleReportAck.DATA_RECEIVE);
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		//接收处理：战报
		private function _doRecv_BattleReportData(bytes:ByteArray):void
		{
			var strBattleReport:ByteArray = BytesUtil.readBytes(bytes); //战报
			var qwMasterID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)视角角色ID
			var wFighterID:uint = bytes.readUnsignedShort(); //(无符号16位整数)主将ID
			var event_:REvt_BattleReportData = new REvt_BattleReportData(REvt_BattleReportData.DATA_RECEIVE);
			event_.strBattleReport = strBattleReport;
			event_.qwMasterID = qwMasterID;
			event_.wFighterID = wFighterID;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:BattleGS;

		public static function get instance():BattleGS
		{
			if(_instance == null)
				_instance = new BattleGS();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;

		public function BattleGS()
		{
			_protID = 21;
			_recvFuncList = [
				_doRecv_BattleAck, //FuncID: 1
				_doRecv_BattleReportAck, //FuncID: 2
				_doRecv_BattleReportData //FuncID: 3
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