/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PathCollideNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家路径碰撞结果通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数PathCollideNotify[玩家路径碰撞结果通知]的接收事件
	 */
	public final class REvt_PathCollideNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_PathCollideNotify";
		public static const DATA_ERROR:String = "LingShanProt_PathCollideNotify_Error";

		public var vecPathCollideInfo:Vector.<SPathCollideInfo>; //路径碰撞
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_PathCollideNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PathCollideNotify wRoomID={wRoomID}/>;
			if(vecPathCollideInfo != null)
			{
				var vecPathCollideInfoXml:XML = <Vec_SPathCollideInfo _name_="vecPathCollideInfo"/>;
				for each(var s1:SPathCollideInfo in vecPathCollideInfo)
					vecPathCollideInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecPathCollideInfoXml);
			}
			return topXml;
		}
	}
}
