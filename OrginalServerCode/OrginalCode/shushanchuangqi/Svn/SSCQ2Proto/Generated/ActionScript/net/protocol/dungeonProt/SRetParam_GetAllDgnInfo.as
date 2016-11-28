/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllDgnInfo.as
//  Purpose:      查询副本星级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	/**
	 * 查询副本星级的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllDgnInfo
	{
		public var sLiXian:DgnLiXian; //历险副本信息
		public var vecStar:Vector.<DgnStar>; //副本星级

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllDgnInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetAllDgnInfo/>;
			if(sLiXian != null)
				topXml.appendChild(sLiXian.toXML("sLiXian"));
			if(vecStar != null)
			{
				var vecStarXml:XML = <Vec_DgnStar _name_="vecStar"/>;
				for each(var s2:DgnStar in vecStar)
					vecStarXml.appendChild(s2.toXML());
				topXml.appendChild(vecStarXml);
			}
			return topXml;
		}
	}
}
