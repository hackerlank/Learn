/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MailPageIDAck.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:页邮件ID回答
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数MailPageIDAck[页邮件ID回答]的接收事件
	 */
	public final class REvt_MailPageIDAck extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_MailPageIDAck";
		public static const DATA_ERROR:String = "MailProt_MailPageIDAck_Error";

		public var vecMailIDList:Vector.<BigInteger>; //(无符号64位整数)页面ID列表
		public var uStartIndex:uint; //(无符号32位整数)当前请求索引
		public var uMailTotalNum:uint; //(无符号32位整数)邮件总数量
		public var eQueryType:uint; //(枚举类型：EMailQueryType)邮件类型

		public function REvt_MailPageIDAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MailPageIDAck uStartIndex={uStartIndex} uMailTotalNum={uMailTotalNum} eQueryType={eQueryType}/>;
			if(vecMailIDList != null)
			{
				var vecMailIDListXml:XML = <Vec_UINT64 _name_="vecMailIDList"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecMailIDList)
					text1 += "[" + value1 + "]";
				vecMailIDListXml.appendChild(text1);
				topXml.appendChild(vecMailIDListXml);
			}
			return topXml;
		}
	}
}
