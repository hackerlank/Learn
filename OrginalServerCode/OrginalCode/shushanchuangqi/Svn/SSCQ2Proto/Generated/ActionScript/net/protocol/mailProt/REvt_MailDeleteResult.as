/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MailDeleteResult.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:邮件发送结果
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数MailDeleteResult[邮件发送结果]的接收事件
	 */
	public final class REvt_MailDeleteResult extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_MailDeleteResult";
		public static const DATA_ERROR:String = "MailProt_MailDeleteResult_Error";

		public var vecMailIDList:Vector.<BigInteger>; //(无符号64位整数)请求ID列表
		public var eErrorResult:uint; //(枚举类型：EMailErrorResult)返回结果

		public function REvt_MailDeleteResult(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MailDeleteResult eErrorResult={eErrorResult}/>;
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
