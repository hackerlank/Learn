/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_KeepAlive.as
//  Purpose:      心跳
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	/**
	 * 心跳的返回的参数组成的结构体
	 */
	public final class SRetParam_KeepAlive
	{
		public var dwServerTime:uint; //(无符号32位整数)服务器的当前时间(1970年1月1日0时开始的秒数)

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_KeepAlive _name_={name_} dwServerTime={dwServerTime}/>;
			else
				topXml = <SRetParam_KeepAlive dwServerTime={dwServerTime}/>;
			return topXml;
		}
	}
}
