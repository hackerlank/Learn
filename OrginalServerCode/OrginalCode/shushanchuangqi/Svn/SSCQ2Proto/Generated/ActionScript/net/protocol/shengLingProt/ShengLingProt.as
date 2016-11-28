/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ShengLingProt.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemGenInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：圣陵协议
	 */
	public class ShengLingProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：玩家打开活动面板
		 */
		public function send_OnOpen(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_OnOpen = new SOrigParam_OnOpen();
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
		 * 发送：玩家进入圣陵
		 */
		public function send_OnEnter(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_OnEnter = new SOrigParam_OnEnter();
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
		 * 发送：玩家摇骰子
		 */
		public function send_DrawDice(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_DrawDice = new SOrigParam_DrawDice();
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
		 * 发送：使用卡片
		 * @param eCardType (枚举类型：ECardType)卡片类型
		 * @param byIndex (无符号8位整数)骰子数(转向时byIndex=0)
		 */
		public function send_UseCard(eCardType:uint, byIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_UseCard = new SOrigParam_UseCard();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eCardType);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买
		 * @param eBuyType (枚举类型：EBuyType)购买类型
		 * @param byNum (无符号8位整数)购买次数
		 */
		public function send_Buy(eBuyType:uint, byNum:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_Buy = new SOrigParam_Buy();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eBuyType);
			bytes_.writeByte(byNum);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家领奖
		 * @param eGridType (枚举类型：EGridType)格子类型(小游戏）
		 * @param byIndex (无符号8位整数)三消中第几个奖励或者拼图是否一键完成(其他忽略此参数）
		 */
		public function send_TakePrize(eGridType:uint, byIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eGridType);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：三消中积分累计
		 * @param wScore (无符号16位整数)积分
		 * @param byStep (无符号8位整数)减少步数
		 * @param wPassword (无符号16位整数)密码
		 */
		public function send_AddScore(wScore:uint, byStep:uint, wPassword:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_AddScore = new SOrigParam_AddScore();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wScore);
			bytes_.writeByte(byStep);
			bytes_.writeShort(wPassword);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家完成或者放弃小游戏
		 */
		public function send_FinishTrapGrid(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_FinishTrapGrid = new SOrigParam_FinishTrapGrid();
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
		 * 发送：玩家离开圣陵
		 */
		public function send_Leave():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：玩家通关
		private function _doRecv_Clearance(bytes:ByteArray):void
		{
			var event_:REvt_Clearance = new REvt_Clearance(REvt_Clearance.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：玩家数据推送（0点)
		private function _doRecv_SyncData(bytes:ByteArray):void
		{
			var sInfo:SShengLingInfo = SShengLingInfo.fromByteArray(bytes); //玩家数据
			var event_:REvt_SyncData = new REvt_SyncData(REvt_SyncData.DATA_RECEIVE);
			event_.sInfo = sInfo;
			dispatchEvent(event_);
		}

		//接收处理：播放特效
		private function _doRecv_PlayEffect(bytes:ByteArray):void
		{
			var event_:REvt_PlayEffect = new REvt_PlayEffect(REvt_PlayEffect.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：获得奖励道具
		private function _doRecv_GetPrizeInfo(bytes:ByteArray):void
		{
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //玩家物品
			var event_:REvt_GetPrizeInfo = new REvt_GetPrizeInfo(REvt_GetPrizeInfo.DATA_RECEIVE);
			event_.vecItem = vecItem;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：玩家打开活动面板
		private function _doReturn_OnOpen(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OnOpen = new SRetParam_OnOpen();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byUseEnter:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家当日使用进入次数
			var byBuyEnter:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家购买进入次数
			var byBuyEnterToday:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家今天购买进入次数
			var bContinue:Boolean = bytes.readBoolean(); //是否继续
			retParam_.byUseEnter = byUseEnter;
			retParam_.byBuyEnter = byBuyEnter;
			retParam_.byBuyEnterToday = byBuyEnterToday;
			retParam_.bContinue = bContinue;
			var origParam_:SOrigParam_OnOpen = _sessionMgr.getData(sessionID_) as SOrigParam_OnOpen;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OnOpen = new TEvt_OnOpen(TEvt_OnOpen.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家打开活动面板
		private function _onTimeOut_OnOpen(sessionID:uint):void
		{
			var retParam:SRetParam_OnOpen = new SRetParam_OnOpen();
			var event_:TEvt_OnOpen = new TEvt_OnOpen(TEvt_OnOpen.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家进入圣陵
		private function _doReturn_OnEnter(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OnEnter = new SRetParam_OnEnter();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byBuyEnterToday:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家今天购买进入次数
			var sInfo:SShengLingInfo = SShengLingInfo.fromByteArray(bytes); //玩家数据
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.byBuyEnterToday = byBuyEnterToday;
			retParam_.sInfo = sInfo;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_OnEnter = _sessionMgr.getData(sessionID_) as SOrigParam_OnEnter;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OnEnter = new TEvt_OnEnter(TEvt_OnEnter.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家进入圣陵
		private function _onTimeOut_OnEnter(sessionID:uint):void
		{
			var retParam:SRetParam_OnEnter = new SRetParam_OnEnter();
			var event_:TEvt_OnEnter = new TEvt_OnEnter(TEvt_OnEnter.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家摇骰子
		private function _doReturn_DrawDice(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DrawDice = new SRetParam_DrawDice();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byIndex:uint = bytes.readUnsignedByte(); //(无符号8位整数)骰子数
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)战报ID
			var sInfo:SPlayerInfo = SPlayerInfo.fromByteArray(bytes); //玩家数据
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.byIndex = byIndex;
			retParam_.qwBattleID = qwBattleID;
			retParam_.sInfo = sInfo;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_DrawDice = _sessionMgr.getData(sessionID_) as SOrigParam_DrawDice;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DrawDice = new TEvt_DrawDice(TEvt_DrawDice.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家摇骰子
		private function _onTimeOut_DrawDice(sessionID:uint):void
		{
			var retParam:SRetParam_DrawDice = new SRetParam_DrawDice();
			var event_:TEvt_DrawDice = new TEvt_DrawDice(TEvt_DrawDice.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：使用卡片
		private function _doReturn_UseCard(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UseCard = new SRetParam_UseCard();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sCard:SCard = SCard.fromByteArray(bytes); //卡片信息
			var sInfo:SPlayerInfo = SPlayerInfo.fromByteArray(bytes); //玩家数据
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)战报ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.sCard = sCard;
			retParam_.sInfo = sInfo;
			retParam_.qwBattleID = qwBattleID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UseCard = _sessionMgr.getData(sessionID_) as SOrigParam_UseCard;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UseCard = new TEvt_UseCard(TEvt_UseCard.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：使用卡片
		private function _onTimeOut_UseCard(sessionID:uint):void
		{
			var retParam:SRetParam_UseCard = new SRetParam_UseCard();
			var event_:TEvt_UseCard = new TEvt_UseCard(TEvt_UseCard.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买
		private function _doReturn_Buy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Buy = new SRetParam_Buy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eBuyTypeRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBuyType)返回购买类型
			var byBuy:uint = bytes.readUnsignedByte(); //(无符号8位整数)返回购买次数
			var byBuyToday:uint = bytes.readUnsignedByte(); //(无符号8位整数)返回今日购买次数
			var byUse:uint = bytes.readUnsignedByte(); //(无符号8位整数)返回当日使用次数
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.eBuyTypeRet = eBuyTypeRet;
			retParam_.byBuy = byBuy;
			retParam_.byBuyToday = byBuyToday;
			retParam_.byUse = byUse;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Buy = _sessionMgr.getData(sessionID_) as SOrigParam_Buy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Buy = new TEvt_Buy(TEvt_Buy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买
		private function _onTimeOut_Buy(sessionID:uint):void
		{
			var retParam:SRetParam_Buy = new SRetParam_Buy();
			var event_:TEvt_Buy = new TEvt_Buy(TEvt_Buy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家领奖
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byBit:uint = bytes.readUnsignedByte(); //(无符号8位整数)奖励状态(其他忽略此参数）
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.byBit = byBit;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_TakePrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakePrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家领奖
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：三消中积分累计
		private function _doReturn_AddScore(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AddScore = new SRetParam_AddScore();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wNextPwd:uint = bytes.readUnsignedShort(); //(无符号16位整数)下一次密码
			var byTotalStep:uint = bytes.readUnsignedByte(); //(无符号8位整数)剩余步数
			var wTotalScore:uint = bytes.readUnsignedShort(); //(无符号16位整数)总积分
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.wNextPwd = wNextPwd;
			retParam_.byTotalStep = byTotalStep;
			retParam_.wTotalScore = wTotalScore;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_AddScore = _sessionMgr.getData(sessionID_) as SOrigParam_AddScore;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AddScore = new TEvt_AddScore(TEvt_AddScore.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：三消中积分累计
		private function _onTimeOut_AddScore(sessionID:uint):void
		{
			var retParam:SRetParam_AddScore = new SRetParam_AddScore();
			var event_:TEvt_AddScore = new TEvt_AddScore(TEvt_AddScore.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家完成或者放弃小游戏
		private function _doReturn_FinishTrapGrid(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FinishTrapGrid = new SRetParam_FinishTrapGrid();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EShengLingResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FinishTrapGrid = _sessionMgr.getData(sessionID_) as SOrigParam_FinishTrapGrid;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FinishTrapGrid = new TEvt_FinishTrapGrid(TEvt_FinishTrapGrid.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家完成或者放弃小游戏
		private function _onTimeOut_FinishTrapGrid(sessionID:uint):void
		{
			var retParam:SRetParam_FinishTrapGrid = new SRetParam_FinishTrapGrid();
			var event_:TEvt_FinishTrapGrid = new TEvt_FinishTrapGrid(TEvt_FinishTrapGrid.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ShengLingProt;

		public static function get instance():ShengLingProt
		{
			if(_instance == null)
				_instance = new ShengLingProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ShengLingProt()
		{
			_protID = 98;
			_recvFuncList = [
				_doRecv_Clearance, //FuncID: 1
				_doRecv_SyncData, //FuncID: 2
				_doRecv_PlayEffect, //FuncID: 3
				_doRecv_GetPrizeInfo //FuncID: 4
			];

			_retFuncList = [
				_doReturn_OnOpen, //FuncID: 1
				_doReturn_OnEnter, //FuncID: 2
				_doReturn_DrawDice, //FuncID: 3
				_doReturn_UseCard, //FuncID: 4
				_doReturn_Buy, //FuncID: 5
				_doReturn_TakePrize, //FuncID: 6
				_doReturn_AddScore, //FuncID: 7
				_doReturn_FinishTrapGrid, //FuncID: 8
			];

			_timeFuncList = [
				_onTimeOut_OnOpen, //FuncID: 1
				_onTimeOut_OnEnter, //FuncID: 2
				_onTimeOut_DrawDice, //FuncID: 3
				_onTimeOut_UseCard, //FuncID: 4
				_onTimeOut_Buy, //FuncID: 5
				_onTimeOut_TakePrize, //FuncID: 6
				_onTimeOut_AddScore, //FuncID: 7
				_onTimeOut_FinishTrapGrid, //FuncID: 8
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