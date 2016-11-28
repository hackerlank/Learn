/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BreakCitta.as
//  Purpose:      请求分解心法
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	/**
	 * 请求分解心法的返回的参数组成的结构体
	 */
	public final class SRetParam_BreakCitta
	{
		public var eResult:uint; //(枚举类型：ECittaResult)结果
		public var vecItemInfo:Vector.<SItemGenInfo>; //分解产生的道具

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BreakCitta _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_BreakCitta eResult={eResult}/>;
			if(vecItemInfo != null)
			{
				var vecItemInfoXml:XML = <Vec_SItemGenInfo _name_="vecItemInfo"/>;
				for each(var s1:SItemGenInfo in vecItemInfo)
					vecItemInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemInfoXml);
			}
			return topXml;
		}
	}
}
