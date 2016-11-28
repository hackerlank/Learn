/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTripodData.as
//  Purpose:      取得其他玩家所有九疑鼎信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	/**
	 * 取得其他玩家所有九疑鼎信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTripodData
	{
		public var oTripodData:STripodData; //九疑鼎数据列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTripodData _name_={name_}/>;
			else
				topXml = <SRetParam_GetTripodData/>;
			if(oTripodData != null)
				topXml.appendChild(oTripodData.toXML("oTripodData"));
			return topXml;
		}
	}
}
