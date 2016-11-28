/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    MallProt.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：商城相关协议
	 */
	public class MallProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：预览商城信息
		 * @param eType (枚举类型：EMallType)商城类型
		 */
		public function send_MalGet(eType:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_MalGet = new SOrigParam_MalGet();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：商场购买
		 * @param eMark (枚举类型：EUseMoneyMark)使用钱币标志
		 * @param eType (枚举类型：EMallType)商城类型
		 * @param wInstID (无符号32位整数)实例ID
		 * @param wCount (无符号16位整数)物品个数
		 */
		public function send_MalBuy(eMark:int, eType:int, wInstID:uint, wCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_MalBuy = new SOrigParam_MalBuy();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eMark);
			bytes_.writeByte(eType);
			bytes_.writeUnsignedInt(wInstID);
			bytes_.writeShort(wCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：商场赠送
		 * @param eMark (枚举类型：EUseMoneyMark)使用钱币标志
		 * @param eType (枚举类型：EMallType)商城类型
		 * @param wInstID (无符号32位整数)物品ID
		 * @param wCount (无符号16位整数)物品个数
		 * @param strReceiveName 接受者姓名
		 * @param strTitle 邮件标题
		 * @param strMsg 邮件内容
		 */
		public function send_MallPresent(eMark:int, eType:int, wInstID:uint, wCount:uint, strReceiveName:String, 
			strTitle:String, strMsg:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_MallPresent = new SOrigParam_MallPresent();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eMark);
			bytes_.writeByte(eType);
			bytes_.writeUnsignedInt(wInstID);
			bytes_.writeShort(wCount);
			BytesUtil.writeString(bytes_, strReceiveName);
			BytesUtil.writeString(bytes_, strTitle);
			BytesUtil.writeString(bytes_, strMsg);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：预览商城限购信息
		 */
		public function send_GetMallDiscountInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买商场限购道具
		 * @param byPos (无符号8位整数)限购位置(0,1,2)
		 * @param wCount (无符号16位整数)购买个数
		 */
		public function send_BuyDiscountItem(byPos:uint, wCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_BuyDiscountItem = new SOrigParam_BuyDiscountItem();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byPos);
			bytes_.writeShort(wCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取物品购买数量列表
		 */
		public function send_GetBuyItemList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetBuyItemList = new SOrigParam_GetBuyItemList();
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
		 * 发送：获取玩家首次充值活动完成信息(在商城界面的奖励)
		 */
		public function send_GetChongZhiActInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：通知玩家商城限购信息
		private function _doRecv_UpdateMallDiscountInfo(bytes:ByteArray):void
		{
			var vecDiscount:Vector.<SDiscount> = SDiscount.vectorFromByteArray(bytes); //限购信息列表
			var wCountPos1:uint = bytes.readUnsignedInt(); //(无符号32位整数)限购位置1购买道具数
			var wCountPos2:uint = bytes.readUnsignedInt(); //(无符号32位整数)限购位置2购买道具数
			var wCountPos3:uint = bytes.readUnsignedInt(); //(无符号32位整数)限购位置3购买道具数
			var wRechargePos1:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置1充值限购期间充值仙石数
			var wRechargePos2:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置2充值限购期间充值仙石数
			var wRechargePos3:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置3充值限购期间充值仙石数
			var wConsumePos1:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置1消费限购期间消费仙石数
			var wConsumePos2:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置2消费限购期间消费仙石数
			var wConsumePos3:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置3消费限购期间消费仙石数
			var event_:REvt_UpdateMallDiscountInfo = new REvt_UpdateMallDiscountInfo(REvt_UpdateMallDiscountInfo.DATA_RECEIVE);
			event_.vecDiscount = vecDiscount;
			event_.wCountPos1 = wCountPos1;
			event_.wCountPos2 = wCountPos2;
			event_.wCountPos3 = wCountPos3;
			event_.wRechargePos1 = wRechargePos1;
			event_.wRechargePos2 = wRechargePos2;
			event_.wRechargePos3 = wRechargePos3;
			event_.wConsumePos1 = wConsumePos1;
			event_.wConsumePos2 = wConsumePos2;
			event_.wConsumePos3 = wConsumePos3;
			dispatchEvent(event_);
		}

		//接收处理：通过栏位通知玩家商城限购信息
		private function _doRecv_UpdateMallDiscountInfoByPos(bytes:ByteArray):void
		{
			var oDiscount:SDiscount = SDiscount.fromByteArray(bytes); //限购信息列表
			var event_:REvt_UpdateMallDiscountInfoByPos = new REvt_UpdateMallDiscountInfoByPos(REvt_UpdateMallDiscountInfoByPos.DATA_RECEIVE);
			event_.oDiscount = oDiscount;
			dispatchEvent(event_);
		}

		//接收处理：物品购买数量更新
		private function _doRecv_BuyItemNotify(bytes:ByteArray):void
		{
			var oBuyItemInfo:SBuyItemInfo = SBuyItemInfo.fromByteArray(bytes); //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
			var event_:REvt_BuyItemNotify = new REvt_BuyItemNotify(REvt_BuyItemNotify.DATA_RECEIVE);
			event_.oBuyItemInfo = oBuyItemInfo;
			dispatchEvent(event_);
		}

		//接收处理：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
		private function _doRecv_UpdateChongZhiActInfo(bytes:ByteArray):void
		{
			var byIdx:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前充值完成的第几个
			var dwCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前充值了几个仙石包
			var byInfo:uint = bytes.readUnsignedByte(); //(无符号8位整数)按位取(低6位,每位为1表明已完成)
			var event_:REvt_UpdateChongZhiActInfo = new REvt_UpdateChongZhiActInfo(REvt_UpdateChongZhiActInfo.DATA_RECEIVE);
			event_.byIdx = byIdx;
			event_.dwCount = dwCount;
			event_.byInfo = byInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：预览商城信息
		private function _doReturn_MalGet(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MalGet = new SRetParam_MalGet();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecMallInfo:Vector.<SMallInfo> = SMallInfo.vectorFromByteArray(bytes); //商场信息列表
			retParam_.vecMallInfo = vecMallInfo;
			var origParam_:SOrigParam_MalGet = _sessionMgr.getData(sessionID_) as SOrigParam_MalGet;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MalGet = new TEvt_MalGet(TEvt_MalGet.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：预览商城信息
		private function _onTimeOut_MalGet(sessionID:uint):void
		{
			var retParam:SRetParam_MalGet = new SRetParam_MalGet();
			var event_:TEvt_MalGet = new TEvt_MalGet(TEvt_MalGet.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：商场购买
		private function _doReturn_MalBuy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MalBuy = new SRetParam_MalBuy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:int = bytes.readByte(); //(枚举类型：EMallResult)购买结果返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MalBuy = _sessionMgr.getData(sessionID_) as SOrigParam_MalBuy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MalBuy = new TEvt_MalBuy(TEvt_MalBuy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：商场购买
		private function _onTimeOut_MalBuy(sessionID:uint):void
		{
			var retParam:SRetParam_MalBuy = new SRetParam_MalBuy();
			var event_:TEvt_MalBuy = new TEvt_MalBuy(TEvt_MalBuy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：商场赠送
		private function _doReturn_MallPresent(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MallPresent = new SRetParam_MallPresent();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:int = bytes.readByte(); //(枚举类型：EMallResult)赠送结果返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MallPresent = _sessionMgr.getData(sessionID_) as SOrigParam_MallPresent;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MallPresent = new TEvt_MallPresent(TEvt_MallPresent.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：商场赠送
		private function _onTimeOut_MallPresent(sessionID:uint):void
		{
			var retParam:SRetParam_MallPresent = new SRetParam_MallPresent();
			var event_:TEvt_MallPresent = new TEvt_MallPresent(TEvt_MallPresent.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买商场限购道具
		private function _doReturn_BuyDiscountItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyDiscountItem = new SRetParam_BuyDiscountItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:int = bytes.readByte(); //(枚举类型：EMallResult)购买结果返回
			var byPos:uint = bytes.readUnsignedByte(); //(无符号8位整数)限购位置(0,1,2)
			var wCount:uint = bytes.readUnsignedShort(); //(无符号16位整数)购买个数
			retParam_.eResult = eResult;
			retParam_.byPos = byPos;
			retParam_.wCount = wCount;
			var origParam_:SOrigParam_BuyDiscountItem = _sessionMgr.getData(sessionID_) as SOrigParam_BuyDiscountItem;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyDiscountItem = new TEvt_BuyDiscountItem(TEvt_BuyDiscountItem.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买商场限购道具
		private function _onTimeOut_BuyDiscountItem(sessionID:uint):void
		{
			var retParam:SRetParam_BuyDiscountItem = new SRetParam_BuyDiscountItem();
			var event_:TEvt_BuyDiscountItem = new TEvt_BuyDiscountItem(TEvt_BuyDiscountItem.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取物品购买数量列表
		private function _doReturn_GetBuyItemList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBuyItemList = new SRetParam_GetBuyItemList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecBuyItemInfo:Vector.<SBuyItemInfo> = SBuyItemInfo.vectorFromByteArray(bytes); //购买数量列表
			retParam_.vecBuyItemInfo = vecBuyItemInfo;
			var origParam_:SOrigParam_GetBuyItemList = _sessionMgr.getData(sessionID_) as SOrigParam_GetBuyItemList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBuyItemList = new TEvt_GetBuyItemList(TEvt_GetBuyItemList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取物品购买数量列表
		private function _onTimeOut_GetBuyItemList(sessionID:uint):void
		{
			var retParam:SRetParam_GetBuyItemList = new SRetParam_GetBuyItemList();
			var event_:TEvt_GetBuyItemList = new TEvt_GetBuyItemList(TEvt_GetBuyItemList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:MallProt;

		public static function get instance():MallProt
		{
			if(_instance == null)
				_instance = new MallProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function MallProt()
		{
			_protID = 27;
			_recvFuncList = [
				_doRecv_UpdateMallDiscountInfo, //FuncID: 1
				_doRecv_UpdateMallDiscountInfoByPos, //FuncID: 2
				_doRecv_BuyItemNotify, //FuncID: 3
				_doRecv_UpdateChongZhiActInfo //FuncID: 4
			];

			_retFuncList = [
				_doReturn_MalGet, //FuncID: 1
				_doReturn_MalBuy, //FuncID: 2
				_doReturn_MallPresent, //FuncID: 3
				_doReturn_BuyDiscountItem, //FuncID: 4
				_doReturn_GetBuyItemList, //FuncID: 5
			];

			_timeFuncList = [
				_onTimeOut_MalGet, //FuncID: 1
				_onTimeOut_MalBuy, //FuncID: 2
				_onTimeOut_MallPresent, //FuncID: 3
				_onTimeOut_BuyDiscountItem, //FuncID: 4
				_onTimeOut_GetBuyItemList, //FuncID: 5
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