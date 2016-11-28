/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    Example.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：通信协议示例
	 */
	public class Example extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：C->S示例函数1
		 * @param byParam1 (有符号8位整数)8位有符号整数
		 * @param wParam2 (有符号16位整数)16位有符号整数
		 * @param dwParam3 (有符号32位整数)32位有符号整数
		 * @param qwParam4 (有符号64位整数)64位有符号整数
		 * @param byParam5 (无符号8位整数)8位无符号整数
		 * @param wParam6 (无符号16位整数)16位无符号整数
		 * @param dwParam7 (无符号32位整数)32位无符号整数
		 * @param qwParam8 (无符号64位整数)64位无符号整数
		 * @param bParam9 布尔值
		 * @param fParam10 (Float)单精度浮点数
		 * @param dParam11 (Double)双精度浮点数
		 * @param strParam12 字符串
		 * @param strParam13 AS字节数组
		 * @param eTest14 (枚举类型：EExTest)枚举值
		 * @param vecExDesc15 继承结构体列表
		 */
		public function send_SampleFunc1(byParam1:int, wParam2:int, dwParam3:int, qwParam4:BigInteger, byParam5:uint, 
			wParam6:uint, dwParam7:uint, qwParam8:BigInteger, bParam9:Boolean, fParam10:Number, 
			dParam11:Number, strParam12:String, strParam13:ByteArray, eTest14:int, vecExDesc15:Vector.<SExDescend4>):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeByte(byParam1);
			bytes_.writeShort(wParam2);
			bytes_.writeInt(dwParam3);
			BytesUtil.writeInt64(bytes_, qwParam4);
			bytes_.writeByte(byParam5);
			bytes_.writeShort(wParam6);
			bytes_.writeUnsignedInt(dwParam7);
			BytesUtil.writeUInt64(bytes_, qwParam8);
			bytes_.writeBoolean(bParam9);
			bytes_.writeFloat(fParam10);
			bytes_.writeDouble(dParam11);
			BytesUtil.writeString(bytes_, strParam12);
			BytesUtil.writeBytes(bytes_, strParam13);
			bytes_.writeShort(eTest14);
			SExDescend4.vectorToByteArray(vecExDesc15, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：C->S有返回值的示例函数
		 * @param byParam1 (无符号8位整数)参数1，不保存
		 * @param qwParam2 (无符号64位整数)参数2，保存
		 * @param loc_derived 结构体，本地保存
		 */
		public function send_SampleRetFunc2(byParam1:uint, qwParam2:BigInteger, loc_derived:SExDerived2, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_SampleRetFunc2 = new SOrigParam_SampleRetFunc2();
			origParam_.qwParam2 = qwParam2;
			origParam_.loc_derived = loc_derived;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byParam1);
			BytesUtil.writeUInt64(bytes_, qwParam2);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：S->C示例函数1
		private function _doRecv_SampleFuncAck1(bytes:ByteArray):void
		{
			var byParam1:int = bytes.readByte(); //(有符号8位整数)8位有符号整数
			var wParam2:int = bytes.readShort(); //(有符号16位整数)16位有符号整数
			var dwParam3:int = bytes.readInt(); //(有符号32位整数)32位有符号整数
			var qwParam4:BigInteger = BytesUtil.readInt64(bytes); //(有符号64位整数)64位有符号整数
			var byParam5:uint = bytes.readUnsignedByte(); //(无符号8位整数)8位无符号整数
			var wParam6:uint = bytes.readUnsignedShort(); //(无符号16位整数)16位无符号整数
			var dwParam7:uint = bytes.readUnsignedInt(); //(无符号32位整数)32位无符号整数
			var qwParam8:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)64位无符号整数
			var bParam9:Boolean = bytes.readBoolean(); //布尔值
			var fParam10:Number = bytes.readFloat(); //(Float)单精度浮点数
			var dParam11:Number = bytes.readDouble(); //(Double)双精度浮点数
			var strParam12:String = BytesUtil.readString(bytes); //字符串
			var strParam13:ByteArray = BytesUtil.readBytes(bytes); //AS字节数组
			var eTest14:int = bytes.readShort(); //(枚举类型：EExTest)枚举值
			var vecExDesc15:Vector.<SExDescend4> = SExDescend4.vectorFromByteArray(bytes); //继承结构体列表
			var event_:REvt_SampleFuncAck1 = new REvt_SampleFuncAck1(REvt_SampleFuncAck1.DATA_RECEIVE);
			event_.byParam1 = byParam1;
			event_.wParam2 = wParam2;
			event_.dwParam3 = dwParam3;
			event_.qwParam4 = qwParam4;
			event_.byParam5 = byParam5;
			event_.wParam6 = wParam6;
			event_.dwParam7 = dwParam7;
			event_.qwParam8 = qwParam8;
			event_.bParam9 = bParam9;
			event_.fParam10 = fParam10;
			event_.dParam11 = dParam11;
			event_.strParam12 = strParam12;
			event_.strParam13 = strParam13;
			event_.eTest14 = eTest14;
			event_.vecExDesc15 = vecExDesc15;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：C->S有返回值的示例函数
		private function _doReturn_SampleRetFunc2(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SampleRetFunc2 = new SRetParam_SampleRetFunc2();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecExDescend:Vector.<SExDescend3> = SExDescend3.vectorFromByteArray(bytes); //结构体列表，返回值
			var strRet:String = BytesUtil.readString(bytes); //字符串，返回值
			retParam_.vecExDescend = vecExDescend;
			retParam_.strRet = strRet;
			var origParam_:SOrigParam_SampleRetFunc2 = _sessionMgr.getData(sessionID_) as SOrigParam_SampleRetFunc2;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_SampleRetFunc2 = new TEvt_SampleRetFunc2(TEvt_SampleRetFunc2.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：C->S有返回值的示例函数
		private function _onTimeOut_SampleRetFunc2(sessionID:uint):void
		{
			var retParam:SRetParam_SampleRetFunc2 = new SRetParam_SampleRetFunc2();
			var origParam:SOrigParam_SampleRetFunc2 = _sessionMgr.getData(sessionID) as SOrigParam_SampleRetFunc2;
			var event_:TEvt_SampleRetFunc2 = new TEvt_SampleRetFunc2(TEvt_SampleRetFunc2.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:Example;

		public static function get instance():Example
		{
			if(_instance == null)
				_instance = new Example();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function Example()
		{
			_protID = 255;
			_recvFuncList = [
				_doRecv_SampleFuncAck1 //FuncID: 1
			];

			_retFuncList = [
				_doReturn_SampleRetFunc2 //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_SampleRetFunc2 //FuncID: 1
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