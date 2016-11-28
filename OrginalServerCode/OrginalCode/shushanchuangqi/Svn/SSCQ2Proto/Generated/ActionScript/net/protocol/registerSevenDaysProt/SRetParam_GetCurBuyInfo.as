/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetCurBuyInfo.as
//  Purpose:      请求当天购买信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
{
	/**
	 * 请求当天购买信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetCurBuyInfo
	{
		public var dwDayID:uint; //(无符号32位整数)第几天
		public var eBuyStatus:uint; //(枚举类型：EBuyStatus)购买状态

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetCurBuyInfo _name_={name_} dwDayID={dwDayID} eBuyStatus={eBuyStatus}/>;
			else
				topXml = <SRetParam_GetCurBuyInfo dwDayID={dwDayID} eBuyStatus={eBuyStatus}/>;
			return topXml;
		}
	}
}
