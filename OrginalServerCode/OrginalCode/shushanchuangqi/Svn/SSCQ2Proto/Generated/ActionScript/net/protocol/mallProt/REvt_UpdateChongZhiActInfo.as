/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateChongZhiActInfo.as
//  Purpose:      协议:商城相关协议, 函数:更新玩家'首次充值'活动完成信息(在商城界面的奖励)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateChongZhiActInfo[更新玩家'首次充值'活动完成信息(在商城界面的奖励)]的接收事件
	 */
	public final class REvt_UpdateChongZhiActInfo extends Event
	{
		public static const DATA_RECEIVE:String = "MallProt_UpdateChongZhiActInfo";
		public static const DATA_ERROR:String = "MallProt_UpdateChongZhiActInfo_Error";

		public var byIdx:uint; //(无符号8位整数)当前充值完成的第几个
		public var dwCount:uint; //(无符号32位整数)当前充值了几个仙石包
		public var byInfo:uint; //(无符号8位整数)按位取(低6位,每位为1表明已完成)

		public function REvt_UpdateChongZhiActInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateChongZhiActInfo byIdx={byIdx} dwCount={dwCount} byInfo={byInfo}/>;
			return topXml;
		}
	}
}
