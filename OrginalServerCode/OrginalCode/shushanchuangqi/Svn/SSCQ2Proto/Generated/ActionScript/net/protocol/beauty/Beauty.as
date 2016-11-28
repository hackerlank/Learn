/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    Beauty.as
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemCount;
	import net.protocol.itemProt.SItemGenInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：美女系统
	 */
	public class Beauty extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取美女信息
		 */
		public function send_GetBeatyInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetBeatyInfo = new SOrigParam_GetBeatyInfo();
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
		 * 发送：结识美女
		 * @param wBeautyID (无符号16位整数)美女id
		 */
		public function send_MeetBeauty(wBeautyID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_MeetBeauty = new SOrigParam_MeetBeauty();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBeautyID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：和美女聊天
		 * @param wBeautyID (无符号16位整数)美女id
		 */
		public function send_ChatBeauty(wBeautyID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_ChatBeauty = new SOrigParam_ChatBeauty();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBeautyID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：送美女礼品
		 * @param wBeautyID (无符号16位整数)美女id
		 * @param vecItemCount 物品列表
		 */
		public function send_SendPrizeBeauty(wBeautyID:uint, vecItemCount:Vector.<SItemCount>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_SendPrizeBeauty = new SOrigParam_SendPrizeBeauty();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBeautyID);
			SItemCount.vectorToByteArray(vecItemCount, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：抽奖
		 * @param eLotteryBeautyType (枚举类型：ELotteryBeautyType)抽奖类型
		 */
		public function send_LotteryBeauty(eLotteryBeautyType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_LotteryBeauty = new SOrigParam_LotteryBeauty();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(eLotteryBeautyType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：美女出战
		 * @param wBeautyID (无符号16位整数)美女id
		 */
		public function send_BeautyFight(wBeautyID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_BeautyFight = new SOrigParam_BeautyFight();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBeautyID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取稀有物品列表
		 */
		public function send_GetRareItemList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetRareItemList = new SOrigParam_GetRareItemList();
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
		 * 发送：获取当前已免费抽奖次数
		 */
		public function send_GetLotteryFreeCnt():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：美女信息更新
		private function _doRecv_BeautyNotify(bytes:ByteArray):void
		{
			var oBeauty:SBeauty = SBeauty.fromByteArray(bytes); //美女信息
			var event_:REvt_BeautyNotify = new REvt_BeautyNotify(REvt_BeautyNotify.DATA_RECEIVE);
			event_.oBeauty = oBeauty;
			dispatchEvent(event_);
		}

		//接收处理：爱心数目更新
		private function _doRecv_LoveHeartCntNotify(bytes:ByteArray):void
		{
			var dwLoveCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)爱心个数
			var event_:REvt_LoveHeartCntNotify = new REvt_LoveHeartCntNotify(REvt_LoveHeartCntNotify.DATA_RECEIVE);
			event_.dwLoveCnt = dwLoveCnt;
			dispatchEvent(event_);
		}

		//接收处理：聊天cd
		private function _doRecv_ChatCdNotify(bytes:ByteArray):void
		{
			var dwNextChatTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)下次聊天冷却时间
			var event_:REvt_ChatCdNotify = new REvt_ChatCdNotify(REvt_ChatCdNotify.DATA_RECEIVE);
			event_.dwNextChatTime = dwNextChatTime;
			dispatchEvent(event_);
		}

		//接收处理：免费抽奖cd
		private function _doRecv_FreeMoneyCdNotify(bytes:ByteArray):void
		{
			var eLotteryBeautyType:uint = bytes.readUnsignedShort(); //(枚举类型：ELotteryBeautyType)抽奖类型,只有单次金币，银币两种类型
			var dwNextChatTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)下次聊天冷却时间
			var event_:REvt_FreeMoneyCdNotify = new REvt_FreeMoneyCdNotify(REvt_FreeMoneyCdNotify.DATA_RECEIVE);
			event_.eLotteryBeautyType = eLotteryBeautyType;
			event_.dwNextChatTime = dwNextChatTime;
			dispatchEvent(event_);
		}

		//接收处理：当前已免费抽奖次数
		private function _doRecv_LotteryFreeCntNotify(bytes:ByteArray):void
		{
			var byFreeCnt:uint = bytes.readUnsignedByte(); //(无符号8位整数)已免费抽奖次数
			var event_:REvt_LotteryFreeCntNotify = new REvt_LotteryFreeCntNotify(REvt_LotteryFreeCntNotify.DATA_RECEIVE);
			event_.byFreeCnt = byFreeCnt;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取美女信息
		private function _doReturn_GetBeatyInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBeatyInfo = new SRetParam_GetBeatyInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecBeauty:Vector.<SBeauty> = SBeauty.vectorFromByteArray(bytes); //美女信息列表
			var dwLoveCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)爱心个数
			var dwNextChatTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)下次聊天冷却时间
			var dwNextGoldLotteryTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)下次免费金币抽奖冷却时间
			var dwNextSilverLotterTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)下次免费银币冷却时间
			var wBeautyID:uint = bytes.readUnsignedShort(); //(无符号16位整数)出战美女ID
			retParam_.vecBeauty = vecBeauty;
			retParam_.dwLoveCnt = dwLoveCnt;
			retParam_.dwNextChatTime = dwNextChatTime;
			retParam_.dwNextGoldLotteryTime = dwNextGoldLotteryTime;
			retParam_.dwNextSilverLotterTime = dwNextSilverLotterTime;
			retParam_.wBeautyID = wBeautyID;
			var origParam_:SOrigParam_GetBeatyInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetBeatyInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBeatyInfo = new TEvt_GetBeatyInfo(TEvt_GetBeatyInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取美女信息
		private function _onTimeOut_GetBeatyInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetBeatyInfo = new SRetParam_GetBeatyInfo();
			var event_:TEvt_GetBeatyInfo = new TEvt_GetBeatyInfo(TEvt_GetBeatyInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：结识美女
		private function _doReturn_MeetBeauty(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MeetBeauty = new SRetParam_MeetBeauty();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBeautyRet)操作结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_MeetBeauty = _sessionMgr.getData(sessionID_) as SOrigParam_MeetBeauty;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MeetBeauty = new TEvt_MeetBeauty(TEvt_MeetBeauty.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：结识美女
		private function _onTimeOut_MeetBeauty(sessionID:uint):void
		{
			var retParam:SRetParam_MeetBeauty = new SRetParam_MeetBeauty();
			var event_:TEvt_MeetBeauty = new TEvt_MeetBeauty(TEvt_MeetBeauty.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：和美女聊天
		private function _doReturn_ChatBeauty(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChatBeauty = new SRetParam_ChatBeauty();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBeautyRet)操作结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_ChatBeauty = _sessionMgr.getData(sessionID_) as SOrigParam_ChatBeauty;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChatBeauty = new TEvt_ChatBeauty(TEvt_ChatBeauty.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：和美女聊天
		private function _onTimeOut_ChatBeauty(sessionID:uint):void
		{
			var retParam:SRetParam_ChatBeauty = new SRetParam_ChatBeauty();
			var event_:TEvt_ChatBeauty = new TEvt_ChatBeauty(TEvt_ChatBeauty.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：送美女礼品
		private function _doReturn_SendPrizeBeauty(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SendPrizeBeauty = new SRetParam_SendPrizeBeauty();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBeautyRet)操作结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_SendPrizeBeauty = _sessionMgr.getData(sessionID_) as SOrigParam_SendPrizeBeauty;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SendPrizeBeauty = new TEvt_SendPrizeBeauty(TEvt_SendPrizeBeauty.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：送美女礼品
		private function _onTimeOut_SendPrizeBeauty(sessionID:uint):void
		{
			var retParam:SRetParam_SendPrizeBeauty = new SRetParam_SendPrizeBeauty();
			var event_:TEvt_SendPrizeBeauty = new TEvt_SendPrizeBeauty(TEvt_SendPrizeBeauty.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：抽奖
		private function _doReturn_LotteryBeauty(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LotteryBeauty = new SRetParam_LotteryBeauty();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBeautyRet)操作结果
			var vecItemGenInfo:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //物品列表
			retParam_.eRet = eRet;
			retParam_.vecItemGenInfo = vecItemGenInfo;
			var origParam_:SOrigParam_LotteryBeauty = _sessionMgr.getData(sessionID_) as SOrigParam_LotteryBeauty;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LotteryBeauty = new TEvt_LotteryBeauty(TEvt_LotteryBeauty.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：抽奖
		private function _onTimeOut_LotteryBeauty(sessionID:uint):void
		{
			var retParam:SRetParam_LotteryBeauty = new SRetParam_LotteryBeauty();
			var event_:TEvt_LotteryBeauty = new TEvt_LotteryBeauty(TEvt_LotteryBeauty.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：美女出战
		private function _doReturn_BeautyFight(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BeautyFight = new SRetParam_BeautyFight();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBeautyRet)操作结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_BeautyFight = _sessionMgr.getData(sessionID_) as SOrigParam_BeautyFight;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BeautyFight = new TEvt_BeautyFight(TEvt_BeautyFight.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：美女出战
		private function _onTimeOut_BeautyFight(sessionID:uint):void
		{
			var retParam:SRetParam_BeautyFight = new SRetParam_BeautyFight();
			var event_:TEvt_BeautyFight = new TEvt_BeautyFight(TEvt_BeautyFight.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取稀有物品列表
		private function _doReturn_GetRareItemList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRareItemList = new SRetParam_GetRareItemList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecItemID:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)稀有物品列表
			retParam_.vecItemID = vecItemID;
			var origParam_:SOrigParam_GetRareItemList = _sessionMgr.getData(sessionID_) as SOrigParam_GetRareItemList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRareItemList = new TEvt_GetRareItemList(TEvt_GetRareItemList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取稀有物品列表
		private function _onTimeOut_GetRareItemList(sessionID:uint):void
		{
			var retParam:SRetParam_GetRareItemList = new SRetParam_GetRareItemList();
			var event_:TEvt_GetRareItemList = new TEvt_GetRareItemList(TEvt_GetRareItemList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:Beauty;

		public static function get instance():Beauty
		{
			if(_instance == null)
				_instance = new Beauty();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function Beauty()
		{
			_protID = 131;
			_recvFuncList = [
				_doRecv_BeautyNotify, //FuncID: 1
				_doRecv_LoveHeartCntNotify, //FuncID: 2
				_doRecv_ChatCdNotify, //FuncID: 3
				_doRecv_FreeMoneyCdNotify, //FuncID: 4
				_doRecv_LotteryFreeCntNotify //FuncID: 5
			];

			_retFuncList = [
				_doReturn_GetBeatyInfo, //FuncID: 1
				_doReturn_MeetBeauty, //FuncID: 2
				_doReturn_ChatBeauty, //FuncID: 3
				_doReturn_SendPrizeBeauty, //FuncID: 4
				_doReturn_LotteryBeauty, //FuncID: 5
				_doReturn_BeautyFight, //FuncID: 6
				_doReturn_GetRareItemList, //FuncID: 7
			];

			_timeFuncList = [
				_onTimeOut_GetBeatyInfo, //FuncID: 1
				_onTimeOut_MeetBeauty, //FuncID: 2
				_onTimeOut_ChatBeauty, //FuncID: 3
				_onTimeOut_SendPrizeBeauty, //FuncID: 4
				_onTimeOut_LotteryBeauty, //FuncID: 5
				_onTimeOut_BeautyFight, //FuncID: 6
				_onTimeOut_GetRareItemList, //FuncID: 7
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