/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_SellItem.as
//  Purpose:      请求出售包裹中的道具-出售给系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;

	/**
	 * 请求出售包裹中的道具-出售给系统的原来的参数组成的结构体
	 */
	public final class SOrigParam_SellItem
	{
		public var vecInstID:Vector.<BigInteger>; //(无符号64位整数)出售的道具实例ID集合
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_SellItem _name_={name_}/>;
			else
				topXml = <SOrigParam_SellItem/>;
			if(vecInstID != null)
			{
				var vecInstIDXml:XML = <Vec_UINT64 _name_="vecInstID"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecInstID)
					text1 += "[" + value1 + "]";
				vecInstIDXml.appendChild(text1);
				topXml.appendChild(vecInstIDXml);
			}
			return topXml;
		}
	}
}
