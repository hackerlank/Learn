/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetShipInfo.as
//  Purpose:      获取某条船的信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	/**
	 * 获取某条船的信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetShipInfo
	{
		public var eResult:uint; //(枚举类型：EShipResult)获取结果
		public var stShipInfo:PlayerShipForClient; //金船信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetShipInfo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetShipInfo eResult={eResult}/>;
			if(stShipInfo != null)
				topXml.appendChild(stShipInfo.toXML("stShipInfo"));
			return topXml;
		}
	}
}
