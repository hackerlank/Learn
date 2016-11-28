/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    DayActProt.as
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：活动
	 */
	public class DayActProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取活动列表
		 */
		public function send_GetActList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetActList = new SOrigParam_GetActList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：是否已领取首充礼包
		 */
		public function send_GetFirstRechargeStatus(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetFirstRechargeStatus = new SOrigParam_GetFirstRechargeStatus();
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
		 * 发送：领取首充礼包
		 */
		public function send_GetFirstRechargeAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetFirstRechargeAward = new SOrigParam_GetFirstRechargeAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：为自己购买蜀山基金
		 * @param byType (无符号8位整数)基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		 */
		public function send_BuyShushanFoundSelf(byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_BuyShushanFoundSelf = new SOrigParam_BuyShushanFoundSelf();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：为好友购买蜀山基金
		 * @param qwFriendID (无符号64位整数)好友ID
		 * @param byType (无符号8位整数)基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		 */
		public function send_BuyShushanFoundFirend(qwFriendID:BigInteger, byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_BuyShushanFoundFirend = new SOrigParam_BuyShushanFoundFirend();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwFriendID);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取玩家购买及领取蜀山基金的信息
		 */
		public function send_GetShushanFoundInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取蜀山基金奖励
		 * @param byType (无符号8位整数)基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		 * @param byDay (无符号8位整数)领取第几个(1~7)
		 */
		public function send_GetShushanFoundAward(byType:uint, byDay:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetShushanFoundAward = new SOrigParam_GetShushanFoundAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			bytes_.writeByte(byDay);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取二次充值礼包状态
		 */
		public function send_GetSecondRechargeStatus(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetSecondRechargeStatus = new SOrigParam_GetSecondRechargeStatus();
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
		 * 发送：领取二次充值礼包
		 */
		public function send_GetSecondRechargeAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetSecondRechargeAward = new SOrigParam_GetSecondRechargeAward();
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
		 * 发送：获取开服时间
		 */
		public function send_GetOpenServerTime(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_GetOpenServerTime = new SOrigParam_GetOpenServerTime();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：活动状态改变通知
		private function _doRecv_ActChangeNotify(bytes:ByteArray):void
		{
			var dwActType:uint = bytes.readUnsignedInt(); //(无符号32位整数)活动id
			var dwActStatus:uint = bytes.readUnsignedInt(); //(无符号32位整数)活动状态
			var event_:REvt_ActChangeNotify = new REvt_ActChangeNotify(REvt_ActChangeNotify.DATA_RECEIVE);
			event_.dwActType = dwActType;
			event_.dwActStatus = dwActStatus;
			dispatchEvent(event_);
		}

		//接收处理：蜀山基金活动改变通知
		private function _doRecv_ShushanFoundChangeNotify(bytes:ByteArray):void
		{
			var wGrowFoundInfo:uint = bytes.readUnsignedShort(); //(无符号16位整数)成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
			var wPExpFoundInfo:uint = bytes.readUnsignedShort(); //(无符号16位整数)修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
			var wSilverFoundInfo:uint = bytes.readUnsignedShort(); //(无符号16位整数)银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
			var wItemFoundInfo:uint = bytes.readUnsignedShort(); //(无符号16位整数)宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
			var dwLoginDays:uint = bytes.readUnsignedInt(); //(无符号32位整数)玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
			var event_:REvt_ShushanFoundChangeNotify = new REvt_ShushanFoundChangeNotify(REvt_ShushanFoundChangeNotify.DATA_RECEIVE);
			event_.wGrowFoundInfo = wGrowFoundInfo;
			event_.wPExpFoundInfo = wPExpFoundInfo;
			event_.wSilverFoundInfo = wSilverFoundInfo;
			event_.wItemFoundInfo = wItemFoundInfo;
			event_.dwLoginDays = dwLoginDays;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取活动列表
		private function _doReturn_GetActList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetActList = new SRetParam_GetActList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecActInfo:Vector.<SActInfo> = SActInfo.vectorFromByteArray(bytes); //活动列表
			retParam_.vecActInfo = vecActInfo;
			var origParam_:SOrigParam_GetActList = _sessionMgr.getData(sessionID_) as SOrigParam_GetActList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetActList = new TEvt_GetActList(TEvt_GetActList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取活动列表
		private function _onTimeOut_GetActList(sessionID:uint):void
		{
			var retParam:SRetParam_GetActList = new SRetParam_GetActList();
			var event_:TEvt_GetActList = new TEvt_GetActList(TEvt_GetActList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：是否已领取首充礼包
		private function _doReturn_GetFirstRechargeStatus(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFirstRechargeStatus = new SRetParam_GetFirstRechargeStatus();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0未充值 1已充值但未领取 2已领取
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_GetFirstRechargeStatus = _sessionMgr.getData(sessionID_) as SOrigParam_GetFirstRechargeStatus;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFirstRechargeStatus = new TEvt_GetFirstRechargeStatus(TEvt_GetFirstRechargeStatus.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：是否已领取首充礼包
		private function _onTimeOut_GetFirstRechargeStatus(sessionID:uint):void
		{
			var retParam:SRetParam_GetFirstRechargeStatus = new SRetParam_GetFirstRechargeStatus();
			var event_:TEvt_GetFirstRechargeStatus = new TEvt_GetFirstRechargeStatus(TEvt_GetFirstRechargeStatus.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取首充礼包
		private function _doReturn_GetFirstRechargeAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFirstRechargeAward = new SRetParam_GetFirstRechargeAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0失败 1成功 2未充值 3已领取
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_GetFirstRechargeAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetFirstRechargeAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFirstRechargeAward = new TEvt_GetFirstRechargeAward(TEvt_GetFirstRechargeAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取首充礼包
		private function _onTimeOut_GetFirstRechargeAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetFirstRechargeAward = new SRetParam_GetFirstRechargeAward();
			var event_:TEvt_GetFirstRechargeAward = new TEvt_GetFirstRechargeAward(TEvt_GetFirstRechargeAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：为自己购买蜀山基金
		private function _doReturn_BuyShushanFoundSelf(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyShushanFoundSelf = new SRetParam_BuyShushanFoundSelf();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0失败 1成功
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_BuyShushanFoundSelf = _sessionMgr.getData(sessionID_) as SOrigParam_BuyShushanFoundSelf;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyShushanFoundSelf = new TEvt_BuyShushanFoundSelf(TEvt_BuyShushanFoundSelf.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：为自己购买蜀山基金
		private function _onTimeOut_BuyShushanFoundSelf(sessionID:uint):void
		{
			var retParam:SRetParam_BuyShushanFoundSelf = new SRetParam_BuyShushanFoundSelf();
			var event_:TEvt_BuyShushanFoundSelf = new TEvt_BuyShushanFoundSelf(TEvt_BuyShushanFoundSelf.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：为好友购买蜀山基金
		private function _doReturn_BuyShushanFoundFirend(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyShushanFoundFirend = new SRetParam_BuyShushanFoundFirend();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0失败 1成功
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_BuyShushanFoundFirend = _sessionMgr.getData(sessionID_) as SOrigParam_BuyShushanFoundFirend;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyShushanFoundFirend = new TEvt_BuyShushanFoundFirend(TEvt_BuyShushanFoundFirend.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：为好友购买蜀山基金
		private function _onTimeOut_BuyShushanFoundFirend(sessionID:uint):void
		{
			var retParam:SRetParam_BuyShushanFoundFirend = new SRetParam_BuyShushanFoundFirend();
			var event_:TEvt_BuyShushanFoundFirend = new TEvt_BuyShushanFoundFirend(TEvt_BuyShushanFoundFirend.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取蜀山基金奖励
		private function _doReturn_GetShushanFoundAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetShushanFoundAward = new SRetParam_GetShushanFoundAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0失败 1成功
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_GetShushanFoundAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetShushanFoundAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetShushanFoundAward = new TEvt_GetShushanFoundAward(TEvt_GetShushanFoundAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取蜀山基金奖励
		private function _onTimeOut_GetShushanFoundAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetShushanFoundAward = new SRetParam_GetShushanFoundAward();
			var event_:TEvt_GetShushanFoundAward = new TEvt_GetShushanFoundAward(TEvt_GetShushanFoundAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取二次充值礼包状态
		private function _doReturn_GetSecondRechargeStatus(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSecondRechargeStatus = new SRetParam_GetSecondRechargeStatus();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0未充值 1已充值但未领取 2已领取
			var dwSecondRechargeValue:uint = bytes.readUnsignedInt(); //(无符号32位整数)二次充值累计金额
			retParam_.byRet = byRet;
			retParam_.dwSecondRechargeValue = dwSecondRechargeValue;
			var origParam_:SOrigParam_GetSecondRechargeStatus = _sessionMgr.getData(sessionID_) as SOrigParam_GetSecondRechargeStatus;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSecondRechargeStatus = new TEvt_GetSecondRechargeStatus(TEvt_GetSecondRechargeStatus.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取二次充值礼包状态
		private function _onTimeOut_GetSecondRechargeStatus(sessionID:uint):void
		{
			var retParam:SRetParam_GetSecondRechargeStatus = new SRetParam_GetSecondRechargeStatus();
			var event_:TEvt_GetSecondRechargeStatus = new TEvt_GetSecondRechargeStatus(TEvt_GetSecondRechargeStatus.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取二次充值礼包
		private function _doReturn_GetSecondRechargeAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSecondRechargeAward = new SRetParam_GetSecondRechargeAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0失败 1成功 2未充值 3已领取
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_GetSecondRechargeAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetSecondRechargeAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSecondRechargeAward = new TEvt_GetSecondRechargeAward(TEvt_GetSecondRechargeAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取二次充值礼包
		private function _onTimeOut_GetSecondRechargeAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetSecondRechargeAward = new SRetParam_GetSecondRechargeAward();
			var event_:TEvt_GetSecondRechargeAward = new TEvt_GetSecondRechargeAward(TEvt_GetSecondRechargeAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取开服时间
		private function _doReturn_GetOpenServerTime(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetOpenServerTime = new SRetParam_GetOpenServerTime();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			retParam_.dwTime = dwTime;
			var origParam_:SOrigParam_GetOpenServerTime = _sessionMgr.getData(sessionID_) as SOrigParam_GetOpenServerTime;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetOpenServerTime = new TEvt_GetOpenServerTime(TEvt_GetOpenServerTime.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取开服时间
		private function _onTimeOut_GetOpenServerTime(sessionID:uint):void
		{
			var retParam:SRetParam_GetOpenServerTime = new SRetParam_GetOpenServerTime();
			var event_:TEvt_GetOpenServerTime = new TEvt_GetOpenServerTime(TEvt_GetOpenServerTime.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:DayActProt;

		public static function get instance():DayActProt
		{
			if(_instance == null)
				_instance = new DayActProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function DayActProt()
		{
			_protID = 69;
			_recvFuncList = [
				_doRecv_ActChangeNotify, //FuncID: 1
				_doRecv_ShushanFoundChangeNotify //FuncID: 2
			];

			_retFuncList = [
				_doReturn_GetActList, //FuncID: 1
				_doReturn_GetFirstRechargeStatus, //FuncID: 2
				_doReturn_GetFirstRechargeAward, //FuncID: 3
				_doReturn_BuyShushanFoundSelf, //FuncID: 4
				_doReturn_BuyShushanFoundFirend, //FuncID: 5
				_doReturn_GetShushanFoundAward, //FuncID: 6
				_doReturn_GetSecondRechargeStatus, //FuncID: 7
				_doReturn_GetSecondRechargeAward, //FuncID: 8
				_doReturn_GetOpenServerTime //FuncID: 9
			];

			_timeFuncList = [
				_onTimeOut_GetActList, //FuncID: 1
				_onTimeOut_GetFirstRechargeStatus, //FuncID: 2
				_onTimeOut_GetFirstRechargeAward, //FuncID: 3
				_onTimeOut_BuyShushanFoundSelf, //FuncID: 4
				_onTimeOut_BuyShushanFoundFirend, //FuncID: 5
				_onTimeOut_GetShushanFoundAward, //FuncID: 6
				_onTimeOut_GetSecondRechargeStatus, //FuncID: 7
				_onTimeOut_GetSecondRechargeAward, //FuncID: 8
				_onTimeOut_GetOpenServerTime //FuncID: 9
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