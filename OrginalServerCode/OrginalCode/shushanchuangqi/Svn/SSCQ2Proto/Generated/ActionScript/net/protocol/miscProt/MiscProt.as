/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    MiscProt.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.utils.ByteArray;
	import net.protocol.protoCommon.SMoneyCount;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：不好归类的小协议
	 */
	public class MiscProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：设置防沉迷状态
		 * @param bIndulge 设置防沉迷状态
		 */
		public function send_SetIndulge(bIndulge:Boolean):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeBoolean(bIndulge);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：设置防沉迷收益率
		 * @param dwIndulgeRate (无符号32位整数)设置防沉迷收益率
		 */
		public function send_SetIndulgeRate(dwIndulgeRate:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(dwIndulgeRate);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买体力
		 */
		public function send_BuyAction(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_BuyAction = new SOrigParam_BuyAction();
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
		 * 发送：获取购买体力次数
		 */
		public function send_GetBuyActionCount(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetBuyActionCount = new SOrigParam_GetBuyActionCount();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取体力buff数值
		 */
		public function send_GetActionBuff():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：发送udplog
		 * @param strParam1 参数1
		 * @param strParam2 参数2
		 */
		public function send_SendUdpLog(strParam1:String, strParam2:String):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			BytesUtil.writeString(bytes_, strParam1);
			BytesUtil.writeString(bytes_, strParam2);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取货币基础数值
		 */
		public function send_GetMoneyList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetMoneyList = new SOrigParam_GetMoneyList();
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
		 * 发送：领取体力buff
		 */
		public function send_TakeActionBuff():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：客户端黑屏Log
		 * @param strParam1 参数1
		 */
		public function send_ClientBlankScreenLog(strParam1:String):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			BytesUtil.writeString(bytes_, strParam1);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：天赐宝箱
		 */
		public function send_OnEnter():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得回合数和活动状态
		 */
		public function send_GetRount():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家抽奖
		 */
		public function send_Draw(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_Draw = new SOrigParam_Draw();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：客户端通知动画播放完毕
		 */
		public function send_DrawRet():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：同步客户端玩家抽奖
		 * @param dwTotalNum (无符号32位整数)总的抽奖信息条数
		 * @param dwSelfNum (无符号32位整数)自己的抽奖信息条数
		 */
		public function send_SendLottery(dwTotalNum:uint, dwSelfNum:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(dwTotalNum);
			bytes_.writeUnsignedInt(dwSelfNum);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取每日冲值奖励
		 */
		public function send_GetEveryDayRechargeAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetEveryDayRechargeAward = new SOrigParam_GetEveryDayRechargeAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取每日冲值金额
		 */
		public function send_GetEveryDayRecharge(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetEveryDayRecharge = new SOrigParam_GetEveryDayRecharge();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：分宝岩购买活动
		 * @param wNum (无符号16位整数)购买数量
		 */
		public function send_BuyFenbaoyan(wNum:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_BuyFenbaoyan = new SOrigParam_BuyFenbaoyan();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 17;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wNum);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：分宝岩购买活动时间
		 */
		public function send_FenbaoyanTime(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_FenbaoyanTime = new SOrigParam_FenbaoyanTime();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 18;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：聊天信息通知
		private function _doRecv_IndulgeTimeNotify(bytes:ByteArray):void
		{
			var dwIndulgeTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)防沉迷时间(秒)
			var event_:REvt_IndulgeTimeNotify = new REvt_IndulgeTimeNotify(REvt_IndulgeTimeNotify.DATA_RECEIVE);
			event_.dwIndulgeTime = dwIndulgeTime;
			dispatchEvent(event_);
		}

		//接收处理：聊天信息通知
		private function _doRecv_IndulgeNextLoginTime(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)可以登陆时间(秒)
			var event_:REvt_IndulgeNextLoginTime = new REvt_IndulgeNextLoginTime(REvt_IndulgeNextLoginTime.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：Buffer中的体力
		private function _doRecv_GetActionBuffNotify(bytes:ByteArray):void
		{
			var dwValue:uint = bytes.readUnsignedInt(); //(无符号32位整数)Buffer中的体力
			var TakeTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)最近领取时间
			var event_:REvt_GetActionBuffNotify = new REvt_GetActionBuffNotify(REvt_GetActionBuffNotify.DATA_RECEIVE);
			event_.dwValue = dwValue;
			event_.TakeTime = TakeTime;
			dispatchEvent(event_);
		}

		//接收处理：通知活动开始
		private function _doRecv_OnBegin(bytes:ByteArray):void
		{
			var event_:REvt_OnBegin = new REvt_OnBegin(REvt_OnBegin.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：宝箱下一波公告
		private function _doRecv_SendNotice(bytes:ByteArray):void
		{
			var byRount:uint = bytes.readUnsignedByte(); //(无符号8位整数)剩余波数
			var byMaxRount:uint = bytes.readUnsignedByte(); //(无符号8位整数)最大波数
			var event_:REvt_SendNotice = new REvt_SendNotice(REvt_SendNotice.DATA_RECEIVE);
			event_.byRount = byRount;
			event_.byMaxRount = byMaxRount;
			dispatchEvent(event_);
		}

		//接收处理：通知倒计时
		private function _doRecv_OnCountDown(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)活动倒计时时间
			var event_:REvt_OnCountDown = new REvt_OnCountDown(REvt_OnCountDown.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：通知活动结束
		private function _doRecv_OnEnd(bytes:ByteArray):void
		{
			var event_:REvt_OnEnd = new REvt_OnEnd(REvt_OnEnd.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：通知宝箱活动剩余轮次
		private function _doRecv_SyncChestInfo(bytes:ByteArray):void
		{
			var sInfo:SGodChestInfo = SGodChestInfo.fromByteArray(bytes); //宝箱信息
			var event_:REvt_SyncChestInfo = new REvt_SyncChestInfo(REvt_SyncChestInfo.DATA_RECEIVE);
			event_.sInfo = sInfo;
			dispatchEvent(event_);
		}

		//接收处理：通知宝箱活动剩余轮次
		private function _doRecv_SyncLotteryInfo(bytes:ByteArray):void
		{
			var dwLottery:uint = bytes.readUnsignedInt(); //(无符号32位整数)抽奖券
			var vecTotalInfo:Vector.<SLotteryInfo> = SLotteryInfo.vectorFromByteArray(bytes); //总的抽奖信息
			var vecSelfInfo:Vector.<SLotteryInfo> = SLotteryInfo.vectorFromByteArray(bytes); //自己抽奖信息
			var event_:REvt_SyncLotteryInfo = new REvt_SyncLotteryInfo(REvt_SyncLotteryInfo.DATA_RECEIVE);
			event_.dwLottery = dwLottery;
			event_.vecTotalInfo = vecTotalInfo;
			event_.vecSelfInfo = vecSelfInfo;
			dispatchEvent(event_);
		}

		//接收处理：同步今日冲值仙石总数
		private function _doRecv_SyncRechargeToday(bytes:ByteArray):void
		{
			var dwTotalRechargeToday:uint = bytes.readUnsignedInt(); //(无符号32位整数)仙石
			var event_:REvt_SyncRechargeToday = new REvt_SyncRechargeToday(REvt_SyncRechargeToday.DATA_RECEIVE);
			event_.dwTotalRechargeToday = dwTotalRechargeToday;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：购买体力
		private function _doReturn_BuyAction(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyAction = new SRetParam_BuyAction();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果
			var dwCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)购买体力次数
			var dwPrice:uint = bytes.readUnsignedInt(); //(无符号32位整数)购买体力价格
			retParam_.dwRet = dwRet;
			retParam_.dwCount = dwCount;
			retParam_.dwPrice = dwPrice;
			var origParam_:SOrigParam_BuyAction = _sessionMgr.getData(sessionID_) as SOrigParam_BuyAction;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyAction = new TEvt_BuyAction(TEvt_BuyAction.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买体力
		private function _onTimeOut_BuyAction(sessionID:uint):void
		{
			var retParam:SRetParam_BuyAction = new SRetParam_BuyAction();
			var event_:TEvt_BuyAction = new TEvt_BuyAction(TEvt_BuyAction.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取购买体力次数
		private function _doReturn_GetBuyActionCount(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBuyActionCount = new SRetParam_GetBuyActionCount();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)购买体力次数
			var dwPrice:uint = bytes.readUnsignedInt(); //(无符号32位整数)购买体力价格
			var dwAction:uint = bytes.readUnsignedInt(); //(无符号32位整数)体力
			retParam_.dwCount = dwCount;
			retParam_.dwPrice = dwPrice;
			retParam_.dwAction = dwAction;
			var origParam_:SOrigParam_GetBuyActionCount = _sessionMgr.getData(sessionID_) as SOrigParam_GetBuyActionCount;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBuyActionCount = new TEvt_GetBuyActionCount(TEvt_GetBuyActionCount.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取购买体力次数
		private function _onTimeOut_GetBuyActionCount(sessionID:uint):void
		{
			var retParam:SRetParam_GetBuyActionCount = new SRetParam_GetBuyActionCount();
			var event_:TEvt_GetBuyActionCount = new TEvt_GetBuyActionCount(TEvt_GetBuyActionCount.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取货币基础数值
		private function _doReturn_GetMoneyList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetMoneyList = new SRetParam_GetMoneyList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecMoneyCount:Vector.<SMoneyCount> = SMoneyCount.vectorFromByteArray(bytes); //货币列表（货币数量为0的不发送）
			retParam_.vecMoneyCount = vecMoneyCount;
			var origParam_:SOrigParam_GetMoneyList = _sessionMgr.getData(sessionID_) as SOrigParam_GetMoneyList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetMoneyList = new TEvt_GetMoneyList(TEvt_GetMoneyList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取货币基础数值
		private function _onTimeOut_GetMoneyList(sessionID:uint):void
		{
			var retParam:SRetParam_GetMoneyList = new SRetParam_GetMoneyList();
			var event_:TEvt_GetMoneyList = new TEvt_GetMoneyList(TEvt_GetMoneyList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家抽奖
		private function _doReturn_Draw(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Draw = new SRetParam_Draw();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wLotteryID:uint = bytes.readUnsignedShort(); //(无符号16位整数)抽奖号码
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ELotteryRes)操作结果
			retParam_.wLotteryID = wLotteryID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Draw = _sessionMgr.getData(sessionID_) as SOrigParam_Draw;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Draw = new TEvt_Draw(TEvt_Draw.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家抽奖
		private function _onTimeOut_Draw(sessionID:uint):void
		{
			var retParam:SRetParam_Draw = new SRetParam_Draw();
			var event_:TEvt_Draw = new TEvt_Draw(TEvt_Draw.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取每日冲值奖励
		private function _doReturn_GetEveryDayRechargeAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetEveryDayRechargeAward = new SRetParam_GetEveryDayRechargeAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEveryDayReChargeAward)消息返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetEveryDayRechargeAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetEveryDayRechargeAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetEveryDayRechargeAward = new TEvt_GetEveryDayRechargeAward(TEvt_GetEveryDayRechargeAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取每日冲值奖励
		private function _onTimeOut_GetEveryDayRechargeAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetEveryDayRechargeAward = new SRetParam_GetEveryDayRechargeAward();
			var event_:TEvt_GetEveryDayRechargeAward = new TEvt_GetEveryDayRechargeAward(TEvt_GetEveryDayRechargeAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取每日冲值金额
		private function _doReturn_GetEveryDayRecharge(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetEveryDayRecharge = new SRetParam_GetEveryDayRecharge();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwTotalRechargeToday:uint = bytes.readUnsignedInt(); //(无符号32位整数)仙石
			retParam_.dwTotalRechargeToday = dwTotalRechargeToday;
			var origParam_:SOrigParam_GetEveryDayRecharge = _sessionMgr.getData(sessionID_) as SOrigParam_GetEveryDayRecharge;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetEveryDayRecharge = new TEvt_GetEveryDayRecharge(TEvt_GetEveryDayRecharge.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取每日冲值金额
		private function _onTimeOut_GetEveryDayRecharge(sessionID:uint):void
		{
			var retParam:SRetParam_GetEveryDayRecharge = new SRetParam_GetEveryDayRecharge();
			var event_:TEvt_GetEveryDayRecharge = new TEvt_GetEveryDayRecharge(TEvt_GetEveryDayRecharge.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：分宝岩购买活动
		private function _doReturn_BuyFenbaoyan(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyFenbaoyan = new SRetParam_BuyFenbaoyan();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EMiscOptRes)购买结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_BuyFenbaoyan = _sessionMgr.getData(sessionID_) as SOrigParam_BuyFenbaoyan;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyFenbaoyan = new TEvt_BuyFenbaoyan(TEvt_BuyFenbaoyan.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：分宝岩购买活动
		private function _onTimeOut_BuyFenbaoyan(sessionID:uint):void
		{
			var retParam:SRetParam_BuyFenbaoyan = new SRetParam_BuyFenbaoyan();
			var event_:TEvt_BuyFenbaoyan = new TEvt_BuyFenbaoyan(TEvt_BuyFenbaoyan.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：分宝岩购买活动时间
		private function _doReturn_FenbaoyanTime(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FenbaoyanTime = new SRetParam_FenbaoyanTime();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwBegin:uint = bytes.readUnsignedInt(); //(无符号32位整数)开始时间
			var dwEnd:uint = bytes.readUnsignedInt(); //(无符号32位整数)结束时间
			retParam_.dwBegin = dwBegin;
			retParam_.dwEnd = dwEnd;
			var origParam_:SOrigParam_FenbaoyanTime = _sessionMgr.getData(sessionID_) as SOrigParam_FenbaoyanTime;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FenbaoyanTime = new TEvt_FenbaoyanTime(TEvt_FenbaoyanTime.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：分宝岩购买活动时间
		private function _onTimeOut_FenbaoyanTime(sessionID:uint):void
		{
			var retParam:SRetParam_FenbaoyanTime = new SRetParam_FenbaoyanTime();
			var event_:TEvt_FenbaoyanTime = new TEvt_FenbaoyanTime(TEvt_FenbaoyanTime.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:MiscProt;

		public static function get instance():MiscProt
		{
			if(_instance == null)
				_instance = new MiscProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function MiscProt()
		{
			_protID = 72;
			_recvFuncList = [
				_doRecv_IndulgeTimeNotify, //FuncID: 1
				_doRecv_IndulgeNextLoginTime, //FuncID: 2
				_doRecv_GetActionBuffNotify, //FuncID: 3
				_doRecv_OnBegin, //FuncID: 4
				_doRecv_SendNotice, //FuncID: 5
				_doRecv_OnCountDown, //FuncID: 6
				_doRecv_OnEnd, //FuncID: 7
				_doRecv_SyncChestInfo, //FuncID: 8
				_doRecv_SyncLotteryInfo, //FuncID: 9
				_doRecv_SyncRechargeToday //FuncID: 10
			];

			_retFuncList = [
				_doReturn_BuyAction, //FuncID: 1
				_doReturn_GetBuyActionCount, //FuncID: 2
				_doReturn_GetMoneyList, //FuncID: 3
				_doReturn_Draw, //FuncID: 4
				_doReturn_GetEveryDayRechargeAward, //FuncID: 5
				_doReturn_GetEveryDayRecharge, //FuncID: 6
				_doReturn_BuyFenbaoyan, //FuncID: 7
				_doReturn_FenbaoyanTime //FuncID: 8
			];

			_timeFuncList = [
				_onTimeOut_BuyAction, //FuncID: 1
				_onTimeOut_GetBuyActionCount, //FuncID: 2
				_onTimeOut_GetMoneyList, //FuncID: 3
				_onTimeOut_Draw, //FuncID: 4
				_onTimeOut_GetEveryDayRechargeAward, //FuncID: 5
				_onTimeOut_GetEveryDayRecharge, //FuncID: 6
				_onTimeOut_BuyFenbaoyan, //FuncID: 7
				_onTimeOut_FenbaoyanTime //FuncID: 8
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