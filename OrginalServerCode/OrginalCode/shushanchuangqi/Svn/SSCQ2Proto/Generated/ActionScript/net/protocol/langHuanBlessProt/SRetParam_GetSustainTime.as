/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSustainTime.as
//  Purpose:      获得游戏中持续时间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	/**
	 * 获得游戏中持续时间的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSustainTime
	{
		public var dwTime:uint; //(无符号32位整数)时间值

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSustainTime _name_={name_} dwTime={dwTime}/>;
			else
				topXml = <SRetParam_GetSustainTime dwTime={dwTime}/>;
			return topXml;
		}
	}
}
