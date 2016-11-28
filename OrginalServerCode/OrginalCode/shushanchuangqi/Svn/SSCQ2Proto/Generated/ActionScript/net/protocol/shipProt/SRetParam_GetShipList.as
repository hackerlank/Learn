/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetShipList.as
//  Purpose:      获取所有金船显示信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	/**
	 * 获取所有金船显示信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetShipList
	{
		public var vecShip:Vector.<PlayerShipForList>; //获取结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetShipList _name_={name_}/>;
			else
				topXml = <SRetParam_GetShipList/>;
			if(vecShip != null)
			{
				var vecShipXml:XML = <Vec_PlayerShipForList _name_="vecShip"/>;
				for each(var s1:PlayerShipForList in vecShip)
					vecShipXml.appendChild(s1.toXML());
				topXml.appendChild(vecShipXml);
			}
			return topXml;
		}
	}
}
