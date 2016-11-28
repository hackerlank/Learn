/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_Sweeping.as
//  Purpose:      扫荡
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	/**
	 * 扫荡的原来的参数组成的结构体
	 */
	public final class SOrigParam_Sweeping
	{
		public var wDgnID:uint; //(无符号16位整数)副本ID
		public var wCount:uint; //(无符号16位整数)次数
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_Sweeping _name_={name_} wDgnID={wDgnID} wCount={wCount}/>;
			else
				topXml = <SOrigParam_Sweeping wDgnID={wDgnID} wCount={wCount}/>;
			return topXml;
		}
	}
}
