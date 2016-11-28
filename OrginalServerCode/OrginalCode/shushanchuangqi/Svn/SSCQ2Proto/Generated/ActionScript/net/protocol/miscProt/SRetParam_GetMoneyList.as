/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetMoneyList.as
//  Purpose:      获取货币基础数值
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import net.protocol.protoCommon.SMoneyCount;

	/**
	 * 获取货币基础数值的返回的参数组成的结构体
	 */
	public final class SRetParam_GetMoneyList
	{
		public var vecMoneyCount:Vector.<SMoneyCount>; //货币列表（货币数量为0的不发送）

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetMoneyList _name_={name_}/>;
			else
				topXml = <SRetParam_GetMoneyList/>;
			if(vecMoneyCount != null)
			{
				var vecMoneyCountXml:XML = <Vec_SMoneyCount _name_="vecMoneyCount"/>;
				for each(var s1:SMoneyCount in vecMoneyCount)
					vecMoneyCountXml.appendChild(s1.toXML());
				topXml.appendChild(vecMoneyCountXml);
			}
			return topXml;
		}
	}
}
