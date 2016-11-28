/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    PropInfo.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：属性相关协议
	 */
	public class PropInfo extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：货币兑换
		 * @param eSrcProp (枚举类型：EPropType)源货币
		 * @param eDestProp (枚举类型：EPropType)目标货币
		 * @param dwCount (无符号32位整数)数量
		 */
		public function send_MoneyExchange(eSrcProp:uint, eDestProp:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_MoneyExchange = new SOrigParam_MoneyExchange();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(eSrcProp);
			bytes_.writeShort(eDestProp);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：属性列表通知(改变后通知)
		private function _doRecv_PropListNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)变更对象ID
			var eClass:uint = bytes.readUnsignedByte(); //(枚举类型：EPropClass)变更对象类型
			var vecPropValue:Vector.<SPropValue> = SPropValue.vectorFromByteArray(bytes); //属性列表
			var event_:REvt_PropListNotify = new REvt_PropListNotify(REvt_PropListNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.eClass = eClass;
			event_.vecPropValue = vecPropValue;
			dispatchEvent(event_);
		}

		//接收处理：属性列表通知(改变后通知)
		private function _doRecv_PropNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)变更对象ID
			var eClass:uint = bytes.readUnsignedByte(); //(枚举类型：EPropClass)变更对象类型
			var vecPropValue:Vector.<SPropValue> = SPropValue.vectorFromByteArray(bytes); //属性列表
			var bType:Boolean = bytes.readBoolean(); //是否飘字
			var event_:REvt_PropNotify = new REvt_PropNotify(REvt_PropNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.eClass = eClass;
			event_.vecPropValue = vecPropValue;
			event_.bType = bType;
			dispatchEvent(event_);
		}

		//接收处理：扩展属性列表通知(改变后通知)
		private function _doRecv_PropExtListNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)变更对象ID
			var eClass:uint = bytes.readUnsignedByte(); //(枚举类型：EPropClass)变更对象类型
			var vecPropValExt:Vector.<SPropValExt> = SPropValExt.vectorFromByteArray(bytes); //扩展属性列表
			var event_:REvt_PropExtListNotify = new REvt_PropExtListNotify(REvt_PropExtListNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.eClass = eClass;
			event_.vecPropValExt = vecPropValExt;
			dispatchEvent(event_);
		}

		//接收处理：属性列表通知(改变后通知)
		private function _doRecv_PropQWListNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)变更对象ID
			var eClass:uint = bytes.readUnsignedByte(); //(枚举类型：EPropClass)变更对象类型
			var vecPropValue:Vector.<SPropQWValue> = SPropQWValue.vectorFromByteArray(bytes); //属性列表
			var event_:REvt_PropQWListNotify = new REvt_PropQWListNotify(REvt_PropQWListNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.eClass = eClass;
			event_.vecPropValue = vecPropValue;
			dispatchEvent(event_);
		}

		//接收处理：扩展属性列表通知(改变后通知)
		private function _doRecv_PropQWExtListNotify(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)变更对象ID
			var eClass:uint = bytes.readUnsignedByte(); //(枚举类型：EPropClass)变更对象类型
			var vecPropValExt:Vector.<SPropQWValExt> = SPropQWValExt.vectorFromByteArray(bytes); //扩展属性列表
			var event_:REvt_PropQWExtListNotify = new REvt_PropQWExtListNotify(REvt_PropQWExtListNotify.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.eClass = eClass;
			event_.vecPropValExt = vecPropValExt;
			dispatchEvent(event_);
		}

		//接收处理：Creature的名字改变通知
		private function _doRecv_NameChangeNotify(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var strName:String = BytesUtil.readString(bytes); //新名字
			var event_:REvt_NameChangeNotify = new REvt_NameChangeNotify(REvt_NameChangeNotify.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.strName = strName;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：货币兑换
		private function _doReturn_MoneyExchange(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MoneyExchange = new SRetParam_MoneyExchange();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EExchangeResult)兑换结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MoneyExchange = _sessionMgr.getData(sessionID_) as SOrigParam_MoneyExchange;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MoneyExchange = new TEvt_MoneyExchange(TEvt_MoneyExchange.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：货币兑换
		private function _onTimeOut_MoneyExchange(sessionID:uint):void
		{
			var retParam:SRetParam_MoneyExchange = new SRetParam_MoneyExchange();
			var event_:TEvt_MoneyExchange = new TEvt_MoneyExchange(TEvt_MoneyExchange.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:PropInfo;

		public static function get instance():PropInfo
		{
			if(_instance == null)
				_instance = new PropInfo();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function PropInfo()
		{
			_protID = 17;
			_recvFuncList = [
				_doRecv_PropListNotify, //FuncID: 1
				_doRecv_PropNotify, //FuncID: 2
				_doRecv_PropExtListNotify, //FuncID: 3
				_doRecv_PropQWListNotify, //FuncID: 4
				_doRecv_PropQWExtListNotify, //FuncID: 5
				_doRecv_NameChangeNotify //FuncID: 6
			];

			_retFuncList = [
				_doReturn_MoneyExchange //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_MoneyExchange //FuncID: 1
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