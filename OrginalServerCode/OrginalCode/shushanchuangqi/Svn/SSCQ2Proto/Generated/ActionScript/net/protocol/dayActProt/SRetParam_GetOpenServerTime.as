/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetOpenServerTime.as
//  Purpose:      获取开服时间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	/**
	 * 获取开服时间的返回的参数组成的结构体
	 */
	public final class SRetParam_GetOpenServerTime
	{
		public var dwTime:uint; //(无符号32位整数)时间

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetOpenServerTime _name_={name_} dwTime={dwTime}/>;
			else
				topXml = <SRetParam_GetOpenServerTime dwTime={dwTime}/>;
			return topXml;
		}
	}
}
