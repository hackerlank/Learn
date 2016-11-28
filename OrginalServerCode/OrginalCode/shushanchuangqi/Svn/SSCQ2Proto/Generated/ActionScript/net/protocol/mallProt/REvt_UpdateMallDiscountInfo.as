/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateMallDiscountInfo.as
//  Purpose:      协议:商城相关协议, 函数:通知玩家商城限购信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateMallDiscountInfo[通知玩家商城限购信息]的接收事件
	 */
	public final class REvt_UpdateMallDiscountInfo extends Event
	{
		public static const DATA_RECEIVE:String = "MallProt_UpdateMallDiscountInfo";
		public static const DATA_ERROR:String = "MallProt_UpdateMallDiscountInfo_Error";

		public var vecDiscount:Vector.<SDiscount>; //限购信息列表
		public var wCountPos1:uint; //(无符号32位整数)限购位置1购买道具数
		public var wCountPos2:uint; //(无符号32位整数)限购位置2购买道具数
		public var wCountPos3:uint; //(无符号32位整数)限购位置3购买道具数
		public var wRechargePos1:uint; //(无符号32位整数)位置1充值限购期间充值仙石数
		public var wRechargePos2:uint; //(无符号32位整数)位置2充值限购期间充值仙石数
		public var wRechargePos3:uint; //(无符号32位整数)位置3充值限购期间充值仙石数
		public var wConsumePos1:uint; //(无符号32位整数)位置1消费限购期间消费仙石数
		public var wConsumePos2:uint; //(无符号32位整数)位置2消费限购期间消费仙石数
		public var wConsumePos3:uint; //(无符号32位整数)位置3消费限购期间消费仙石数

		public function REvt_UpdateMallDiscountInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateMallDiscountInfo wCountPos1={wCountPos1} wCountPos2={wCountPos2} wCountPos3={wCountPos3} wRechargePos1={wRechargePos1}
				 wRechargePos2={wRechargePos2} wRechargePos3={wRechargePos3} wConsumePos1={wConsumePos1} wConsumePos2={wConsumePos2} wConsumePos3={wConsumePos3}/>;
			if(vecDiscount != null)
			{
				var vecDiscountXml:XML = <Vec_SDiscount _name_="vecDiscount"/>;
				for each(var s1:SDiscount in vecDiscount)
					vecDiscountXml.appendChild(s1.toXML());
				topXml.appendChild(vecDiscountXml);
			}
			return topXml;
		}
	}
}
