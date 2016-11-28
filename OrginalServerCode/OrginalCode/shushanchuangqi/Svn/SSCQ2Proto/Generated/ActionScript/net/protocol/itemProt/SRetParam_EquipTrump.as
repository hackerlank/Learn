/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_EquipTrump.as
//  Purpose:      出战法宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	/**
	 * 出战法宝的返回的参数组成的结构体
	 */
	public final class SRetParam_EquipTrump
	{
		public var eResult:uint; //(枚举类型：ETrumpResult)结果
		public var vecTrump:Vector.<STrump>; //新法宝

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_EquipTrump _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_EquipTrump eResult={eResult}/>;
			if(vecTrump != null)
			{
				var vecTrumpXml:XML = <Vec_STrump _name_="vecTrump"/>;
				for each(var s1:STrump in vecTrump)
					vecTrumpXml.appendChild(s1.toXML());
				topXml.appendChild(vecTrumpXml);
			}
			return topXml;
		}
	}
}
