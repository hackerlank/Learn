/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateDujieValue.as
//  Purpose:      协议:道具相关协议, 函数:更新散仙的渡劫数据
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数UpdateDujieValue[更新散仙的渡劫数据]的接收事件
	 */
	public final class REvt_UpdateDujieValue extends Event
	{
		public static const DATA_RECEIVE:String = "FighterProt_UpdateDujieValue";
		public static const DATA_ERROR:String = "FighterProt_UpdateDujieValue_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)将唯一ID
		public var byDujieLevel:uint; //(无符号8位整数)当前渡劫等级
		public var dwDujieExp:uint; //(无符号32位整数)当前渡劫经验
		public var dwSpiritPower:uint; //(无符号32位整数)元神力

		public function REvt_UpdateDujieValue(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateDujieValue qwInstID={qwInstID} byDujieLevel={byDujieLevel} dwDujieExp={dwDujieExp} dwSpiritPower={dwSpiritPower}/>;
			return topXml;
		}
	}
}
