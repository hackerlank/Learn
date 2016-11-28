/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_WearCitta.as
//  Purpose:      请求装备心法
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 请求装备心法的原来的参数组成的结构体
	 */
	public final class SOrigParam_WearCitta
	{
		public var qwInstID:BigInteger; //(无符号64位整数)装备的实例ID
		public var eSlotType:int; //(枚举类型：ECittaSlotType)装备位的类型
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_WearCitta _name_={name_} qwInstID={qwInstID} eSlotType={eSlotType}/>;
			else
				topXml = <SOrigParam_WearCitta qwInstID={qwInstID} eSlotType={eSlotType}/>;
			return topXml;
		}
	}
}
