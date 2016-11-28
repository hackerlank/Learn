/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTopList.as
//  Purpose:      获取镇守榜
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	/**
	 * 获取镇守榜的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTopList
	{
		public var oDemonFloorPage:SDemonFloorPage; //分页信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTopList _name_={name_}/>;
			else
				topXml = <SRetParam_GetTopList/>;
			if(oDemonFloorPage != null)
				topXml.appendChild(oDemonFloorPage.toXML("oDemonFloorPage"));
			return topXml;
		}
	}
}
