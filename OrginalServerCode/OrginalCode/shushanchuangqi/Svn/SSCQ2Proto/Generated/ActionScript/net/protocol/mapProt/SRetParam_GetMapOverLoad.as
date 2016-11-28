/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetMapOverLoad.as
//  Purpose:      请求地图负载
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	/**
	 * 请求地图负载的返回的参数组成的结构体
	 */
	public final class SRetParam_GetMapOverLoad
	{
		public var wMapID:uint; //(无符号16位整数)地图ID
		public var vecLoad:Vector.<MapOverLoad>; //地图ID

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetMapOverLoad _name_={name_} wMapID={wMapID}/>;
			else
				topXml = <SRetParam_GetMapOverLoad wMapID={wMapID}/>;
			if(vecLoad != null)
			{
				var vecLoadXml:XML = <Vec_MapOverLoad _name_="vecLoad"/>;
				for each(var s1:MapOverLoad in vecLoad)
					vecLoadXml.appendChild(s1.toXML());
				topXml.appendChild(vecLoadXml);
			}
			return topXml;
		}
	}
}
