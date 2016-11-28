/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ShipProt.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：元江金船协议
	 */
	public class ShipProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取自己显示信息
		 */
		public function send_GetShipSelfView():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取所有金船显示信息
		 */
		public function send_GetShipList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetShipList = new SOrigParam_GetShipList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：不再关注列表
		 */
		public function send_DelList():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取某条船的信息
		 * @param qwInsID (无符号64位整数)金船唯一ID
		 */
		public function send_GetShipInfo(qwInsID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetShipInfo = new SOrigParam_GetShipInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInsID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取历史信息
		 */
		public function send_GetShipReport():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：雇佣船只,开始运船
		 */
		public function send_OpenShip(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_OpenShip = new SOrigParam_OpenShip();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买运船次数
		 */
		public function send_BuyOpenShipTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_BuyOpenShipTimes = new SOrigParam_BuyOpenShipTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买抢劫次数
		 */
		public function send_BuyRoBShipTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_BuyRoBShipTimes = new SOrigParam_BuyRoBShipTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买刷新次数
		 */
		public function send_BuyReflushShipTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_BuyReflushShipTimes = new SOrigParam_BuyReflushShipTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：刷新船只
		 * @param byVip (无符号8位整数)0,表示非vip ,非0表示vip
		 */
		public function send_ReFlushShip(byVip:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_ReFlushShip = new SOrigParam_ReFlushShip();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byVip);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：邀请护送船只
		 * @param qwFriend (无符号64位整数)好友
		 */
		public function send_InViteFriend(qwFriend:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_InViteFriend = new SOrigParam_InViteFriend();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwFriend);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：回应邀请护送船只
		 * @param bySuc (无符号8位整数)0,同意，1拒绝
		 * @param qwFriend (无符号64位整数)好友
		 * @param dwCode (无符号32位整数)验证码
		 */
		public function send_InViteOtherAgree(bySuc:uint, qwFriend:BigInteger, dwCode:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_InViteOtherAgree = new SOrigParam_InViteOtherAgree();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(bySuc);
			BytesUtil.writeUInt64(bytes_, qwFriend);
			bytes_.writeUnsignedInt(dwCode);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：船主踢出护送者
		 * @param qwFriend (无符号64位整数)好友
		 */
		public function send_FireDefense(qwFriend:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_FireDefense = new SOrigParam_FireDefense();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwFriend);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：打劫船只
		 * @param qwInsID (无符号64位整数)金船唯一ID
		 */
		public function send_DoRoBShip(qwInsID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_DoRoBShip = new SOrigParam_DoRoBShip();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInsID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：返抢
		 * @param qwShipID (无符号64位整数)金船唯一ID
		 * @param qwRoBID (无符号64位整数)打劫者ID
		 */
		public function send_DoGrapShip(qwShipID:BigInteger, qwRoBID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_DoGrapShip = new SOrigParam_DoGrapShip();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwShipID);
			BytesUtil.writeUInt64(bytes_, qwRoBID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：一键完成运送
		 */
		public function send_FinishShipOneKey(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_FinishShipOneKey = new SOrigParam_FinishShipOneKey();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：发送玩家信息
		private function _doRecv_SendView(bytes:ByteArray):void
		{
			var stViewInfo:PlayerSelfView = PlayerSelfView.fromByteArray(bytes); //玩家信息
			var event_:REvt_SendView = new REvt_SendView(REvt_SendView.DATA_RECEIVE);
			event_.stViewInfo = stViewInfo;
			dispatchEvent(event_);
		}

		//接收处理：发送船只增加消息
		private function _doRecv_UpDateShipAdd(bytes:ByteArray):void
		{
			var stShipInfo:PlayerShipForList = PlayerShipForList.fromByteArray(bytes); //船只信息
			var event_:REvt_UpDateShipAdd = new REvt_UpDateShipAdd(REvt_UpDateShipAdd.DATA_RECEIVE);
			event_.stShipInfo = stShipInfo;
			dispatchEvent(event_);
		}

		//接收处理：发送船只删除消息
		private function _doRecv_UpDateShipDel(bytes:ByteArray):void
		{
			var qwInsID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)金船唯一ID
			var event_:REvt_UpDateShipDel = new REvt_UpDateShipDel(REvt_UpDateShipDel.DATA_RECEIVE);
			event_.qwInsID = qwInsID;
			dispatchEvent(event_);
		}

		//接收处理：发送玩家战报信息
		private function _doRecv_SendRePort(bytes:ByteArray):void
		{
			var vecReportInfo:Vector.<ShipReportForClient> = ShipReportForClient.vectorFromByteArray(bytes); //玩家战报信息
			var event_:REvt_SendRePort = new REvt_SendRePort(REvt_SendRePort.DATA_RECEIVE);
			event_.vecReportInfo = vecReportInfo;
			dispatchEvent(event_);
		}

		//接收处理：发送记录增加消息
		private function _doRecv_UpDateShipReportAdd(bytes:ByteArray):void
		{
			var stReport:ShipReportForClient = ShipReportForClient.fromByteArray(bytes); //记录信息
			var event_:REvt_UpDateShipReportAdd = new REvt_UpDateShipReportAdd(REvt_UpDateShipReportAdd.DATA_RECEIVE);
			event_.stReport = stReport;
			dispatchEvent(event_);
		}

		//接收处理：邀请别人的回复
		private function _doRecv_InviteAnswer(bytes:ByteArray):void
		{
			var qwDefense:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)护卫者ID
			var strName:String = BytesUtil.readString(bytes); //护卫者的名字
			var byColor:uint = bytes.readUnsignedByte(); //(无符号8位整数)护卫者的颜色
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			var event_:REvt_InviteAnswer = new REvt_InviteAnswer(REvt_InviteAnswer.DATA_RECEIVE);
			event_.qwDefense = qwDefense;
			event_.strName = strName;
			event_.byColor = byColor;
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取所有金船显示信息
		private function _doReturn_GetShipList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetShipList = new SRetParam_GetShipList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecShip:Vector.<PlayerShipForList> = PlayerShipForList.vectorFromByteArray(bytes); //获取结果
			retParam_.vecShip = vecShip;
			var origParam_:SOrigParam_GetShipList = _sessionMgr.getData(sessionID_) as SOrigParam_GetShipList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetShipList = new TEvt_GetShipList(TEvt_GetShipList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取所有金船显示信息
		private function _onTimeOut_GetShipList(sessionID:uint):void
		{
			var retParam:SRetParam_GetShipList = new SRetParam_GetShipList();
			var event_:TEvt_GetShipList = new TEvt_GetShipList(TEvt_GetShipList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取某条船的信息
		private function _doReturn_GetShipInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetShipInfo = new SRetParam_GetShipInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)获取结果
			var stShipInfo:PlayerShipForClient = PlayerShipForClient.fromByteArray(bytes); //金船信息
			retParam_.eResult = eResult;
			retParam_.stShipInfo = stShipInfo;
			var origParam_:SOrigParam_GetShipInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetShipInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetShipInfo = new TEvt_GetShipInfo(TEvt_GetShipInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取某条船的信息
		private function _onTimeOut_GetShipInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetShipInfo = new SRetParam_GetShipInfo();
			var event_:TEvt_GetShipInfo = new TEvt_GetShipInfo(TEvt_GetShipInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：雇佣船只,开始运船
		private function _doReturn_OpenShip(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OpenShip = new SRetParam_OpenShip();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_OpenShip = _sessionMgr.getData(sessionID_) as SOrigParam_OpenShip;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OpenShip = new TEvt_OpenShip(TEvt_OpenShip.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：雇佣船只,开始运船
		private function _onTimeOut_OpenShip(sessionID:uint):void
		{
			var retParam:SRetParam_OpenShip = new SRetParam_OpenShip();
			var event_:TEvt_OpenShip = new TEvt_OpenShip(TEvt_OpenShip.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买运船次数
		private function _doReturn_BuyOpenShipTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyOpenShipTimes = new SRetParam_BuyOpenShipTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyOpenShipTimes = _sessionMgr.getData(sessionID_) as SOrigParam_BuyOpenShipTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyOpenShipTimes = new TEvt_BuyOpenShipTimes(TEvt_BuyOpenShipTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买运船次数
		private function _onTimeOut_BuyOpenShipTimes(sessionID:uint):void
		{
			var retParam:SRetParam_BuyOpenShipTimes = new SRetParam_BuyOpenShipTimes();
			var event_:TEvt_BuyOpenShipTimes = new TEvt_BuyOpenShipTimes(TEvt_BuyOpenShipTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买抢劫次数
		private function _doReturn_BuyRoBShipTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyRoBShipTimes = new SRetParam_BuyRoBShipTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyRoBShipTimes = _sessionMgr.getData(sessionID_) as SOrigParam_BuyRoBShipTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyRoBShipTimes = new TEvt_BuyRoBShipTimes(TEvt_BuyRoBShipTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买抢劫次数
		private function _onTimeOut_BuyRoBShipTimes(sessionID:uint):void
		{
			var retParam:SRetParam_BuyRoBShipTimes = new SRetParam_BuyRoBShipTimes();
			var event_:TEvt_BuyRoBShipTimes = new TEvt_BuyRoBShipTimes(TEvt_BuyRoBShipTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买刷新次数
		private function _doReturn_BuyReflushShipTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyReflushShipTimes = new SRetParam_BuyReflushShipTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyReflushShipTimes = _sessionMgr.getData(sessionID_) as SOrigParam_BuyReflushShipTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyReflushShipTimes = new TEvt_BuyReflushShipTimes(TEvt_BuyReflushShipTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买刷新次数
		private function _onTimeOut_BuyReflushShipTimes(sessionID:uint):void
		{
			var retParam:SRetParam_BuyReflushShipTimes = new SRetParam_BuyReflushShipTimes();
			var event_:TEvt_BuyReflushShipTimes = new TEvt_BuyReflushShipTimes(TEvt_BuyReflushShipTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：刷新船只
		private function _doReturn_ReFlushShip(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReFlushShip = new SRetParam_ReFlushShip();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			var wShipId:uint = bytes.readUnsignedShort(); //(无符号16位整数)金船模板
			retParam_.eResult = eResult;
			retParam_.wShipId = wShipId;
			var origParam_:SOrigParam_ReFlushShip = _sessionMgr.getData(sessionID_) as SOrigParam_ReFlushShip;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReFlushShip = new TEvt_ReFlushShip(TEvt_ReFlushShip.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：刷新船只
		private function _onTimeOut_ReFlushShip(sessionID:uint):void
		{
			var retParam:SRetParam_ReFlushShip = new SRetParam_ReFlushShip();
			var event_:TEvt_ReFlushShip = new TEvt_ReFlushShip(TEvt_ReFlushShip.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：邀请护送船只
		private function _doReturn_InViteFriend(bytes:ByteArray):void
		{
			var retParam_:SRetParam_InViteFriend = new SRetParam_InViteFriend();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_InViteFriend = _sessionMgr.getData(sessionID_) as SOrigParam_InViteFriend;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_InViteFriend = new TEvt_InViteFriend(TEvt_InViteFriend.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：邀请护送船只
		private function _onTimeOut_InViteFriend(sessionID:uint):void
		{
			var retParam:SRetParam_InViteFriend = new SRetParam_InViteFriend();
			var event_:TEvt_InViteFriend = new TEvt_InViteFriend(TEvt_InViteFriend.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：回应邀请护送船只
		private function _doReturn_InViteOtherAgree(bytes:ByteArray):void
		{
			var retParam_:SRetParam_InViteOtherAgree = new SRetParam_InViteOtherAgree();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_InViteOtherAgree = _sessionMgr.getData(sessionID_) as SOrigParam_InViteOtherAgree;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_InViteOtherAgree = new TEvt_InViteOtherAgree(TEvt_InViteOtherAgree.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：回应邀请护送船只
		private function _onTimeOut_InViteOtherAgree(sessionID:uint):void
		{
			var retParam:SRetParam_InViteOtherAgree = new SRetParam_InViteOtherAgree();
			var event_:TEvt_InViteOtherAgree = new TEvt_InViteOtherAgree(TEvt_InViteOtherAgree.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：船主踢出护送者
		private function _doReturn_FireDefense(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FireDefense = new SRetParam_FireDefense();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FireDefense = _sessionMgr.getData(sessionID_) as SOrigParam_FireDefense;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FireDefense = new TEvt_FireDefense(TEvt_FireDefense.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：船主踢出护送者
		private function _onTimeOut_FireDefense(sessionID:uint):void
		{
			var retParam:SRetParam_FireDefense = new SRetParam_FireDefense();
			var event_:TEvt_FireDefense = new TEvt_FireDefense(TEvt_FireDefense.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：打劫船只
		private function _doReturn_DoRoBShip(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoRoBShip = new SRetParam_DoRoBShip();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			var bySuc:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,失败，1胜利
			retParam_.eResult = eResult;
			retParam_.bySuc = bySuc;
			var origParam_:SOrigParam_DoRoBShip = _sessionMgr.getData(sessionID_) as SOrigParam_DoRoBShip;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoRoBShip = new TEvt_DoRoBShip(TEvt_DoRoBShip.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：打劫船只
		private function _onTimeOut_DoRoBShip(sessionID:uint):void
		{
			var retParam:SRetParam_DoRoBShip = new SRetParam_DoRoBShip();
			var event_:TEvt_DoRoBShip = new TEvt_DoRoBShip(TEvt_DoRoBShip.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：返抢
		private function _doReturn_DoGrapShip(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoGrapShip = new SRetParam_DoGrapShip();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			var bySuc:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,失败，1胜利
			retParam_.eResult = eResult;
			retParam_.bySuc = bySuc;
			var origParam_:SOrigParam_DoGrapShip = _sessionMgr.getData(sessionID_) as SOrigParam_DoGrapShip;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoGrapShip = new TEvt_DoGrapShip(TEvt_DoGrapShip.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：返抢
		private function _onTimeOut_DoGrapShip(sessionID:uint):void
		{
			var retParam:SRetParam_DoGrapShip = new SRetParam_DoGrapShip();
			var event_:TEvt_DoGrapShip = new TEvt_DoGrapShip(TEvt_DoGrapShip.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：一键完成运送
		private function _doReturn_FinishShipOneKey(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FinishShipOneKey = new SRetParam_FinishShipOneKey();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShipResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FinishShipOneKey = _sessionMgr.getData(sessionID_) as SOrigParam_FinishShipOneKey;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FinishShipOneKey = new TEvt_FinishShipOneKey(TEvt_FinishShipOneKey.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：一键完成运送
		private function _onTimeOut_FinishShipOneKey(sessionID:uint):void
		{
			var retParam:SRetParam_FinishShipOneKey = new SRetParam_FinishShipOneKey();
			var event_:TEvt_FinishShipOneKey = new TEvt_FinishShipOneKey(TEvt_FinishShipOneKey.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ShipProt;

		public static function get instance():ShipProt
		{
			if(_instance == null)
				_instance = new ShipProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ShipProt()
		{
			_protID = 84;
			_recvFuncList = [
				_doRecv_SendView, //FuncID: 1
				_doRecv_UpDateShipAdd, //FuncID: 2
				_doRecv_UpDateShipDel, //FuncID: 3
				_doRecv_SendRePort, //FuncID: 4
				_doRecv_UpDateShipReportAdd, //FuncID: 5
				_doRecv_InviteAnswer //FuncID: 6
			];

			_retFuncList = [
				_doReturn_GetShipList, //FuncID: 1
				_doReturn_GetShipInfo, //FuncID: 2
				_doReturn_OpenShip, //FuncID: 3
				_doReturn_BuyOpenShipTimes, //FuncID: 4
				_doReturn_BuyRoBShipTimes, //FuncID: 5
				_doReturn_BuyReflushShipTimes, //FuncID: 6
				_doReturn_ReFlushShip, //FuncID: 7
				_doReturn_InViteFriend, //FuncID: 8
				_doReturn_InViteOtherAgree, //FuncID: 9
				_doReturn_FireDefense, //FuncID: 10
				_doReturn_DoRoBShip, //FuncID: 11
				_doReturn_DoGrapShip, //FuncID: 12
				_doReturn_FinishShipOneKey //FuncID: 13
			];

			_timeFuncList = [
				_onTimeOut_GetShipList, //FuncID: 1
				_onTimeOut_GetShipInfo, //FuncID: 2
				_onTimeOut_OpenShip, //FuncID: 3
				_onTimeOut_BuyOpenShipTimes, //FuncID: 4
				_onTimeOut_BuyRoBShipTimes, //FuncID: 5
				_onTimeOut_BuyReflushShipTimes, //FuncID: 6
				_onTimeOut_ReFlushShip, //FuncID: 7
				_onTimeOut_InViteFriend, //FuncID: 8
				_onTimeOut_InViteOtherAgree, //FuncID: 9
				_onTimeOut_FireDefense, //FuncID: 10
				_onTimeOut_DoRoBShip, //FuncID: 11
				_onTimeOut_DoGrapShip, //FuncID: 12
				_onTimeOut_FinishShipOneKey //FuncID: 13
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0 || funcID > _recvFuncList.length
				 || funcID < -_retFuncList.length)
				return false;
			var func:Function;
			if(funcID > 0)
				func = _recvFuncList[funcID - 1];
			else
				func = _retFuncList[-funcID - 1];
			if(func != null)
			{
				func(bytes);
				return true;
			}
			return false;
		}

		public override function onTimeOut(funcID:uint, sessionID:uint):void
		{
			if(funcID == 0 || funcID > _timeFuncList.length)
				return;
			_timeFuncList[funcID - 1](sessionID);
		}
	}
}