/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_TakeoffCitta.as
//  Purpose:      请求卸下心法
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	/**
	 * 请求卸下心法的原来的参数组成的结构体
	 */
	public final class SOrigParam_TakeoffCitta
	{
		public var eSlotType:int; //(枚举类型：ECittaSlotType)装备位的类型
		public var wIndex:int; //(有符号16位整数)放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_TakeoffCitta _name_={name_} eSlotType={eSlotType} wIndex={wIndex}/>;
			else
				topXml = <SOrigParam_TakeoffCitta eSlotType={eSlotType} wIndex={wIndex}/>;
			return topXml;
		}
	}
}
