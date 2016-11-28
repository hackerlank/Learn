/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_THLogNotify.as
//  Purpose:      协议:寻宝协议, 函数:日志通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数THLogNotify[日志通知]的接收事件
	 */
	public final class REvt_THLogNotify extends Event
	{
		public static const DATA_RECEIVE:String = "TreasureHuntProt_THLogNotify";
		public static const DATA_ERROR:String = "TreasureHuntProt_THLogNotify_Error";

		public var eTHLogType:int; //(枚举类型：ETHLogType)寻宝日志类型
		public var dwParamA:uint; //(无符号32位整数)参数A
		public var dwParamB:uint; //(无符号32位整数)参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
		public var dwParamC:BigInteger; //(无符号64位整数)参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)

		public function REvt_THLogNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_THLogNotify eTHLogType={eTHLogType} dwParamA={dwParamA} dwParamB={dwParamB} dwParamC={dwParamC}/>;
			return topXml;
		}
	}
}
