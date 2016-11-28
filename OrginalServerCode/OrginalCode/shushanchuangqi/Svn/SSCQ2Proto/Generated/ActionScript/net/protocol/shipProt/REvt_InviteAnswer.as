/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_InviteAnswer.as
//  Purpose:      协议:元江金船协议, 函数:邀请别人的回复
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数InviteAnswer[邀请别人的回复]的接收事件
	 */
	public final class REvt_InviteAnswer extends Event
	{
		public static const DATA_RECEIVE:String = "ShipProt_InviteAnswer";
		public static const DATA_ERROR:String = "ShipProt_InviteAnswer_Error";

		public var qwDefense:BigInteger; //(无符号64位整数)护卫者ID
		public var strName:String; //护卫者的名字
		public var byColor:uint; //(无符号8位整数)护卫者的颜色
		public var eResult:uint; //(枚举类型：EShipResult)操作结果

		public function REvt_InviteAnswer(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_InviteAnswer qwDefense={qwDefense} strName={strName} byColor={byColor} eResult={eResult}/>;
			return topXml;
		}
	}
}
