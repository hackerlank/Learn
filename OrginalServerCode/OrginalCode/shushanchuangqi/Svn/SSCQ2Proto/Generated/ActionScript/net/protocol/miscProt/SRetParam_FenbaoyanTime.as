/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FenbaoyanTime.as
//  Purpose:      分宝岩购买活动时间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	/**
	 * 分宝岩购买活动时间的返回的参数组成的结构体
	 */
	public final class SRetParam_FenbaoyanTime
	{
		public var dwBegin:uint; //(无符号32位整数)开始时间
		public var dwEnd:uint; //(无符号32位整数)结束时间

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FenbaoyanTime _name_={name_} dwBegin={dwBegin} dwEnd={dwEnd}/>;
			else
				topXml = <SRetParam_FenbaoyanTime dwBegin={dwBegin} dwEnd={dwEnd}/>;
			return topXml;
		}
	}
}
